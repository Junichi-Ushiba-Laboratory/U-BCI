using LSL;
using LslLeapMotion.LeapMotion;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LslLeapMotion.Record
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
        private const int CH_COUNT = 6 * 2 * 3 + 1;

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
        /// Data queue waiting for sending
        /// </summary>
        private List<PollingEvent> m_handList = new List<PollingEvent>();


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
            channels.append_child("channel").append_child_value("label", "Timestamp").append_child_value("unit", "-").append_child_value("type", "EEG");

            channels.append_child("channel").append_child_value("label", "Left Thumb X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Thumb Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Thumb Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Index X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Index Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Index Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Middle X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Middle Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Middle Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Ring X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Ring Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Ring Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Pinky X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Pinky Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Pinky Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Wrist X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Wrist Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Left Wrist Z").append_child_value("unit", "-").append_child_value("type", "Position");

            channels.append_child("channel").append_child_value("label", "Right Thumb X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Thumb Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Thumb Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Index X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Index Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Index Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Middle X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Middle Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Middle Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Ring X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Ring Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Ring Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Pinky X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Pinky Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Pinky Z").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Wrist X").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Wrist Y").append_child_value("unit", "-").append_child_value("type", "Position");
            channels.append_child("channel").append_child_value("label", "Right Wrist Z").append_child_value("unit", "-").append_child_value("type", "Position");

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
        /// <param name="handData">Adding Data</param>
        public void Send(PollingEvent handData)
        {
            // Do nothing when the consumer does not exists
            if (!m_outlet.have_consumers())
            {
                m_callSendCount = 0;
                m_handList.Clear();
                return;
            }

            // Count the calling numbers of time for deciding the send timing
            m_callSendCount++;

            // Register to the queue when the data is available
            if (handData.LeftExist > 0 || handData.RightExist > 0)
            {
                m_handList.Add(handData);
            }

            // Send the data by taking out from queue, when the send timing comes
            if (m_callSendCount >= m_samplePerPacket)
            {
                if (m_handList.Count > 0)
                {
                    // NOTE: There are possibilities to not work in worker thread
                    GC.Collect();

                    // Create the sending buffer
                    double[,] buffer = new double[m_handList.Count, CH_COUNT];

                    // Write the data into the buffer
                    for (int i = 0; i < m_handList.Count; i++)
                    {
                        buffer[i, 0] = m_handList[i].TimeStamp;
                        buffer[i, 1] = m_handList[i].LThumbX;
                        buffer[i, 2] = m_handList[i].LThumbY;
                        buffer[i, 3] = m_handList[i].LThumbZ;
                        buffer[i, 4] = m_handList[i].LIndexX;
                        buffer[i, 5] = m_handList[i].LIndexY;
                        buffer[i, 6] = m_handList[i].LIndexZ;
                        buffer[i, 7] = m_handList[i].LMiddleX;
                        buffer[i, 8] = m_handList[i].LMiddleY;
                        buffer[i, 9] = m_handList[i].LMiddleZ;
                        buffer[i, 10] = m_handList[i].LRingX;
                        buffer[i, 11] = m_handList[i].LRingY;
                        buffer[i, 12] = m_handList[i].LRingZ;
                        buffer[i, 13] = m_handList[i].LPinkyX;
                        buffer[i, 14] = m_handList[i].LPinkyY;
                        buffer[i, 15] = m_handList[i].LPinkyZ;
                        buffer[i, 16] = m_handList[i].LWristX;
                        buffer[i, 17] = m_handList[i].LWristY;
                        buffer[i, 18] = m_handList[i].LWristZ;

                        buffer[i, 19] = m_handList[i].RThumbX;
                        buffer[i, 20] = m_handList[i].RThumbY;
                        buffer[i, 21] = m_handList[i].RThumbZ;
                        buffer[i, 22] = m_handList[i].RIndexX;
                        buffer[i, 23] = m_handList[i].RIndexY;
                        buffer[i, 24] = m_handList[i].RIndexZ;
                        buffer[i, 25] = m_handList[i].RMiddleX;
                        buffer[i, 26] = m_handList[i].RMiddleY;
                        buffer[i, 27] = m_handList[i].RMiddleZ;
                        buffer[i, 28] = m_handList[i].RRingX;
                        buffer[i, 29] = m_handList[i].RRingY;
                        buffer[i, 30] = m_handList[i].RRingZ;
                        buffer[i, 31] = m_handList[i].RPinkyX;
                        buffer[i, 32] = m_handList[i].RPinkyY;
                        buffer[i, 33] = m_handList[i].RPinkyZ;
                        buffer[i, 34] = m_handList[i].RWristX;
                        buffer[i, 35] = m_handList[i].RWristY;
                        buffer[i, 36] = m_handList[i].RWristZ;
                    }

                    // Send data
                    m_outlet.push_chunk(buffer);

                    // Reset the queue
                    m_handList.Clear();
                }

                // Reset the counter
                m_callSendCount = 0;
            }
        }
    }
}
