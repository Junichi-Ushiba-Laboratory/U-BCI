using LslLeapMotion.LeapMotion;
using LslLeapMotion.Record;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LslLeapMotion
{
    public partial class MainForm : Form
    {
        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// Setting management class
        /// </summary>
        private ConfigManager m_config = new ConfigManager();

        /// <summary>
        /// LeapMotion control class
        /// </summary>
        private LeapMotion.Device m_lm = new Device();

        /// <summary>
        /// LSL Sending class
        /// </summary>
        private Sender m_sender = null;


        /////////////////////////////////////////////////////////////////////
        // Initialization, finishing process etc.


        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = m_lm.IsRunning;
        }


        /////////////////////////////////////////////////////////////////////
        // Event handler of menu

        private void _fileExitMenu_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void _toolSettingMenu_Click(object sender, EventArgs e)
        {
            ConfigForm configForm = new ConfigForm(m_config);
            configForm.ShowDialog();
        }


        /////////////////////////////////////////////////////////////////////
        // Start, stop button

        private void _startButton_Click(object sender, EventArgs e)
        {
            if (!m_lm.IsRunning)
            {
                // Start each process and change the GUI when the process is not running
                m_lm.OnTracking = OnTrack;
                m_lm.OnLoadConnection = OnLost;
                if (m_lm.Open() != 0)
                {
                    MessageBox.Show("Failed to start-up. Confirm whether the Leap Motion is connected.", "Leap Motion");
                }
                m_sender = new Sender(m_config.LslStreamName, Device.FrameRate, m_config.SendInterval);

                SetControlEnable(false);
            }
            else
            {
                // Stop each process and initialize to the GUI state when the process is running.
                m_lm.Close();
                m_sender.Dispose();
                m_sender = null;

                SetControlEnable(true);
            }
        }

        /// <summary>
        /// Set the control display
        /// </summary>
        /// <param name="enable"></param>
        private void SetControlEnable(bool enable)
        {
            _startButton.Text = enable ? "Start (&S)" : "Stop (&S)";
            _mainMenu.Enabled = enable;
        }


        /////////////////////////////////////////////////////////////////////
        // Event handler for leap motion

        /// <summary>
        /// Event handler that has to be called when receiving data
        /// </summary>
        /// <param name="Sender"></param>
        /// <param name="args"></param>
        private void OnTrack(object Sender, EventArgs args)
        {
            // Send data to sending module of LSL.
            // Send timing will be determined by the module.
            TrackEventArg evt = (TrackEventArg)args;
            if (m_sender != null) m_sender.Send(evt.Data);
        }

        private void OnLost(object Sender, EventArgs args)
        {
            // NOTE: Add process optionally when the connection is lost.
        }

    }
}
