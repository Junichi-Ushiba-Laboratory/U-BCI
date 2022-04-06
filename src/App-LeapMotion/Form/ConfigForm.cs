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
    public partial class ConfigForm : Form
    {
        /// <summary>
        /// Reference to the settings class that the main form holds
        /// </summary>
        private ConfigManager m_config = null;


        public ConfigForm(ConfigManager config)
        {
            InitializeComponent();
            m_config = config;
        }

        private void ConfigForm_Load(object sender, EventArgs e)
        {
            _lslSendRateNumeric.Value = m_config.SendInterval;
        }

        // OK button
        private void _okButton_Click(object sender, EventArgs e)
        {
            m_config.SendInterval = (int)_lslSendRateNumeric.Value;
            this.Close();
        }

        // Cancel button
        private void _cancelButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
