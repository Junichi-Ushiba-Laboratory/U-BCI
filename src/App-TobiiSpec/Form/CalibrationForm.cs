using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace App_TobiiSpec
{
    /// <summary>
    /// Calibration Form
    /// </summary>
    partial class CalibrationForm : Form
    {
        /// <summary>
        /// Reference to the Tobii management class which main form holds
        /// </summary>
        private Record.TobiiManager m_tobiiManager = null;


        /// <summary>
        /// Constructors
        /// </summary>
        /// <param name="tobiiManager"></param>
        public CalibrationForm(Record.TobiiManager tobiiManager)
        {
            InitializeComponent();

            m_tobiiManager = tobiiManager;

            // Connect the Bitmap instance to the picture box.
            _mainPicturebox.Image = new Bitmap(1000, 1000, PixelFormat.Format32bppArgb);
        }

        // Maximize the form
        private void CalibrationForm_Load(object sender, EventArgs e)
        {
            this.WindowState = FormWindowState.Maximized;
        }

        // Process when the calibration finishes. Form will be closed.
        private void OnFinish(object sender, EventArgs e)
        {
            // Destroy the Bitmap configured in the picture box
            Bitmap temp = (Bitmap)_mainPicturebox.Image;
            _mainPicturebox.Image = null;
            temp.Dispose();

            this.Close();
        }

        // Process when the form is showed. Calibration process will start.
        private void CalibrationForm_Shown(object sender, EventArgs e)
        {
            try
            {
                if (!m_tobiiManager.Calibrate(_mainPicturebox, OnFinish))
                {
                    MessageBox.Show("Failed in calibration", "App-Tobii", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            // NOTE: Only exception is defined.
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Close();
                return;
            }
        }
    }
}
