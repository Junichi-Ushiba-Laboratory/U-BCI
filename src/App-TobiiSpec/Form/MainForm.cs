using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tobii.Research;

namespace App_TobiiSpec
{
    /// <summary>
    /// Main form
    /// </summary>
    public partial class MainForm : Form
    {
        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// Configuration data class
        /// </summary>
        private ConfigManager m_config = new ConfigManager();

        /// <summary>
        /// Tobii management class
        /// </summary>
        private Record.TobiiManager m_tobiiManager = new Record.TobiiManager();

        /// <summary>
        /// Sending class
        /// </summary>
        private Record.Sender m_lslSender = null;

        /// <summary>
        /// Path to save the calibration data.
        /// The same directory of execution binary will be configured.
        /// </summary>
        private string m_calibrationPath = "";

        /// <summary>
        /// Path to save the gaze data locally.
        /// The same directory of execution binary will be configured.
        /// </summary>
        private StreamWriter m_gazeDst = null;


        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// Constructors
        /// </summary>
        public MainForm()
        {
            InitializeComponent();

            // Determine the path of calibration data
            m_calibrationPath = Path.Combine(Path.GetDirectoryName(Application.ExecutablePath), "calibration.xml");
        }


        /////////////////////////////////////////////////////////////////////
        // Event handler

        // Quitting menu
        private void _fileExitMenu_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        // Start menu, stop menu (button)
        private void _controlStartMenu_Click(object sender, EventArgs e)
        {
            // Update the GUI to finish when acquiring data
            if (m_tobiiManager.Working)
            {
                // Stop the data acquisition
                m_tobiiManager.StopRecord();

                // Destroy the sending class
                m_lslSender.Dispose();
                m_lslSender = null;

                _startButton.Text = "Start (&S)";
                SetEnable(true);

                if (m_gazeDst != null)
                {
                    m_gazeDst.Dispose();
                    m_gazeDst = null;
                }
            }
            // Start the data acquisition, if it is not on going.
            else
            {
                if (m_lslSender != null) m_lslSender.Dispose();

                try
                {
                    // Prepare for the send
                    m_lslSender = new Record.Sender(m_config.LslStreamName, m_config.TobiiSampleingRate, m_config.SendInterval);
                    // Restore calibration if exists
                    m_tobiiManager.LoadCalibration(m_calibrationPath);
                    // Start data acquisition
                    m_tobiiManager.GetGazeData(m_config.TobiiSampleingRate, OnReceiveGaze, null);
                    _startButton.Text = "Stop (&S)";
                    SetEnable(false);
                }
                // NOTE: Only exception is defined.
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);

                    // Revert the status
                    _startButton.Text = "Start (&S)";
                    SetEnable(true);
                    if (m_lslSender != null)
                    {
                        m_lslSender.Dispose();
                        m_lslSender = null;
                    }

                    return;
                }

#if DEBUG
                try
                {
                    // Prepare for the local store.
                    if (m_gazeDst != null) m_gazeDst.Dispose();
                    m_gazeDst = new StreamWriter("gaze.csv");
                }
                // Ignore the export error
                catch (IOException) { }
#endif
            }
        }

        // Callback that will be called when the gaze data are received
        private void OnReceiveGaze(object sender, GazeDataEventArgs e)
        {
            if (m_lslSender == null) return;

#if DEBUG
            try
            {
                // Export the gaze data to file
                string line = "";
                line += e.LeftEye.GazePoint.PositionOnDisplayArea.X + ", " + e.LeftEye.GazePoint.PositionOnDisplayArea.Y + ",,";
                line += e.LeftEye.GazeOrigin.PositionInTrackBoxCoordinates.X + ", " + e.LeftEye.GazeOrigin.PositionInTrackBoxCoordinates.Y + ", " + e.LeftEye.GazeOrigin.PositionInTrackBoxCoordinates.Z + ",,";
                line += e.LeftEye.Pupil.PupilDiameter;
                m_gazeDst.WriteLine(line);
            }
            // Ignore the export error
            catch (IOException) { }
#endif

            try
            {
                // Register the gaze data to sending class
                m_lslSender.Send(e);
            }
            // NOTE: Only exception is defined.
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }
        }

        /// <summary>
        /// Switch the "Enabled" of control
        /// </summary>
        /// <param name="enable"></param>
        private void SetEnable(bool enable)
        {
            _mainMenu.Enabled = enable;
            _tobiiSelectGroupbox.Enabled = enable;
        }

        // Searching menu of Tobii device (button)
        private void _toolFindMenu_Click(object sender, EventArgs e)
        {
            int preIndex = _tobiiSelectCombobox.SelectedIndex;

            try
            {
                m_tobiiManager.Find();
            }
            // NOTE: Only exception is defined.
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                return;
            }

            _tobiiSelectCombobox.Items.Clear();

            for (int i = 0; i < m_tobiiManager.Count; i++)
            {
                _tobiiSelectCombobox.Items.Add(m_tobiiManager.Name(i));
            }

            try
            {
                _tobiiSelectCombobox.SelectedIndex = preIndex;
            }
            // Unset if invalid index has been specified
            catch (ArgumentOutOfRangeException)
            {
                _tobiiSelectCombobox.SelectedIndex = -1;
            }
        }

        // Calibration menu
        private void _toolCalibrationMenu_Click(object sender, EventArgs e)
        {
            CalibrationForm form = new CalibrationForm(m_tobiiManager);
            form.ShowDialog();
        }

        // Configuration menu
        private void _toolConfigMenu_Click(object sender, EventArgs e)
        {
            SettingForm settingForm = new SettingForm(m_config, m_tobiiManager);
            settingForm.ShowDialog();
        }

        // Selection of the Tobii device
        private void _tobiiSelectCombobox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_tobiiManager.SelectedIndex = _tobiiSelectCombobox.SelectedIndex;
        }

        // Process when the form closed
        private void MainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                // Save the status of calibration
                m_tobiiManager.SaveCalibration(m_calibrationPath);

                // Stop if the acquisition is on going.
                if (m_tobiiManager.Working) m_tobiiManager.StopRecord();
                // Destroy the sending class if exists
                if (m_lslSender != null) m_lslSender.Dispose();
                // Destroy if the file is saving.
                if (m_gazeDst != null) m_gazeDst.Dispose();
            }
            // Does not do nothing
            catch (Exception)
            {
                System.Diagnostics.Debug.WriteLine("Error occurred when finishing the program.");
            }
        }
    }
}
