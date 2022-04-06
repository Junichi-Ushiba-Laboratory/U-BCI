using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace App_TobiiSpec
{
    /// <summary>
    /// Setting form
    /// </summary>
    partial class SettingForm : Form
    {
        /// <summary>
        /// Reference to the settings class that the main form holds
        /// </summary>
        private ConfigManager m_config = null;

        /// <summary>
        /// Reference to the Tobii management class which main form holds
        /// </summary>
        private Record.TobiiManager m_tobiiManager = null;


        /// <summary>
        /// Constructors
        /// </summary>
        /// <param name="config"></param>
        /// <param name="tobiiManager"></param>
        public SettingForm(ConfigManager config, Record.TobiiManager tobiiManager)
        {
            InitializeComponent();
            m_config = config;
            m_tobiiManager = tobiiManager;
        }

        // OK button
        private void _okButton_Click(object sender, EventArgs e)
        {
            m_config.TobiiSampleingRate = int.Parse(_tobiiSamplingRateCombobox.SelectedItem.ToString());
            m_config.SendInterval = (int)_lslSendRateNumeric.Value;
            this.Close();
        }

        // Cancel button
        private void _cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        // Process when the form is loaded
        private void SettingForm_Load(object sender, EventArgs e)
        {
            // Get the sampling rate the the device is corresponded
            try
            {
                List<float> tobiiSRate = m_tobiiManager.EnumSaplingRateList();
                for (int i = 0; i < tobiiSRate.Count; i++)
                {
                    _tobiiSamplingRateCombobox.Items.Add(tobiiSRate[i]);
                }
            }
            // NOTE: Only exception is defined.
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.Close();
                return;
            }

            // Show the settings
            _tobiiSamplingRateCombobox.SelectedItem = m_config.TobiiSampleingRate;
            _lslSendRateNumeric.Value = m_config.SendInterval;
        }

        private void _lslGroupbox_Enter(object sender, EventArgs e)
        {

        }
    }
}
