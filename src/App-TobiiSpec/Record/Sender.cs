using LSL;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Tobii.Research;

namespace App_TobiiSpec.Record
{
    /// <summary>
    /// Class that sends data to LSL's master unit.
    /// NOTE: When the instance has been deleted, the remained queue will be destroyed.
    /// </summary>
    class Sender : IDisposable
    {
        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// Sending channel number (time, coordinates of both eyes and pupil diameters)
        /// </summary>
        private const int CH_COUNT = 7;

        /// <summary>
        /// Settings of LSL stream
        /// </summary>
        private StreamInfo m_info = null;

        /// <summary>
        /// LSL outlet stream
        /// </summary>
        private StreamOutlet m_outlet = null;

        /// <summary>
        /// Counter to decide the transmission interval. When the value reaches m_samplePerPacket, the sending process will start.
        /// </summary>
        private int m_callSendCount = 0;

        /// <summary>
        /// Data number per one send. Missing data will be counted too.
        /// </summary>
        private int m_samplePerPacket = 0;

        /// <summary>
        /// Queue of waiting gaze data
        /// </summary>
        private List<GazeDataEventArgs> m_gazeList = new List<GazeDataEventArgs>();


        /////////////////////////////////////////////////////////////////////
        // Initialization and destroy

        /// <summary>
        /// Constructors
        /// </summary>
        /// <param name="streamName">Sending Stream Name</param>
        /// <param name="samplingRate">Sampling Rate of Input Data</param>
        /// <param name="intervalMs">Transmission Interval (ms)</param>
        public Sender(string streamName, float samplingRate, int intervalMs)
        {
            m_samplePerPacket = (int)(samplingRate * 0.001 * intervalMs);

            m_info = new StreamInfo(streamName, "gaze", CH_COUNT, samplingRate, channel_format_t.cf_double64);
            LSL.XMLElement channels = m_info.desc().append_child("channels");
            channels.append_child("channel").append_child_value("label", "Timestamp").append_child_value("unit", "ms").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Left X").append_child_value("unit", "tt").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Left Y").append_child_value("unit", "tt").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Left pupil").append_child_value("unit", "tt").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Right X").append_child_value("unit", "tt").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Right Y").append_child_value("unit", "tt").append_child_value("type", "EEG");
            channels.append_child("channel").append_child_value("label", "Right pupil").append_child_value("unit", "tt").append_child_value("type", "EEG");
            m_outlet = new StreamOutlet(m_info);
        }

        /// <summary>
        /// Destroy the object
        /// </summary>
        public void Dispose()
        {
            m_outlet.Dispose();
            m_info.Dispose();
        }


        /////////////////////////////////////////////////////////////////////
        // Method

        /// <summary>
        /// Register the sending data. The sending timing will be determined automatically.
        /// </summary>
        /// <param name="gazeData">Gaze Data</param>
        public void Send(GazeDataEventArgs gazeData)
        {
            // Do nothing when the consumer does not exists
            if (!m_outlet.have_consumers())
            {
                m_callSendCount = 0;
                m_gazeList.Clear();
                return;
            }

            // Count the calling numbers of time for deciding the send timing
            m_callSendCount++;

            // Register to the queue, when the gaze data is available
            if (!float.IsNaN(gazeData.LeftEye.GazePoint.PositionOnDisplayArea.X))
            {
                m_gazeList.Add(gazeData);
            }

            // Send the data by taking out from queue, when the send timing comes
            if (m_callSendCount >= m_samplePerPacket)
            {
                if (m_gazeList.Count > 0)
                {
                    // NOTE: There are possibilities to not work in worker thread
                    GC.Collect();

                    // Create the sending buffer
                    double[,] buffer = new double[m_gazeList.Count, CH_COUNT];

                    // Write the data into the buffer
                    for (int i = 0; i < m_gazeList.Count; i++)
                    {
                        buffer[i, 0] = m_gazeList[i].DeviceTimeStamp;
                        buffer[i, 1] = m_gazeList[i].LeftEye.GazePoint.PositionOnDisplayArea.X;
                        buffer[i, 2] = m_gazeList[i].LeftEye.GazePoint.PositionOnDisplayArea.Y;
                        buffer[i, 3] = m_gazeList[i].LeftEye.Pupil.PupilDiameter;
                        buffer[i, 4] = m_gazeList[i].RightEye.GazePoint.PositionOnDisplayArea.X;
                        buffer[i, 5] = m_gazeList[i].RightEye.GazePoint.PositionOnDisplayArea.Y;
                        buffer[i, 6] = m_gazeList[i].RightEye.Pupil.PupilDiameter;
                    }

                    // Send data
                    m_outlet.push_chunk(buffer);

                    // Reset the queue
                    m_gazeList.Clear();
                }

                // Reset the counter
                m_callSendCount = 0;
            }
        }
    }
}
