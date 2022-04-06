using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace App_TobiiSpec
{
    /// <summary>
    /// Data class to hold the settings data
    /// </summary>
    class ConfigManager
    {
        /// <summary>
        /// Stream name of LSL
        /// </summary>
        private string m_lslStreamName = "Tobii Pro Spectrum";

        /// <summary>
        /// Sampling rate of gaze data (sec)
        /// </summary>
        private float m_tobiiSampleingRate = 1200;

        /// <summary>
        /// Transmission interval of LSL (ms)
        /// It depends to the sampling rate and does not guarantee the time interval
        /// </summary>
        private int m_sendInterval = 1;

        /// <summary>
        /// Stream name of LSL
        /// </summary>
        public string LslStreamName
        {
            get { return m_lslStreamName; }
            set { m_lslStreamName = value; }
        }

        /// <summary>
        /// Sampling rate of gaze data (sec)
        /// </summary>
        public float TobiiSampleingRate
        {
            get { return m_tobiiSampleingRate; }
            set { m_tobiiSampleingRate = value; }
        }

        /// <summary>
        /// Transmission interval of LSL (ms)
        /// It depends to the sampling rate and does not guarantee the time interval
        /// </summary>
        public int SendInterval
        {
            get { return m_sendInterval; }
            set { m_sendInterval = value; }
        }
    }
}
