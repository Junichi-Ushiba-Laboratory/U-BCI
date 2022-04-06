using System;
using System.Collections.Generic;

using LSL;

namespace LslStreaming
{
    class LslSender : IDisposable
    {
        ////////////////////////////////////////
        //// Member variables

        // Number of channel data
        int m_channelCount = 0;

        // LSL stream information
        StreamInfo m_stremInfo = null;

        // LSL outlet stream
        private StreamOutlet m_outlet = null;

        // Buffer size
        private int m_bufferSize = 0;

        // Buffering data array
        private List<float[]> m_buffer = null;

        ////////////////////////////////////////
        //// Constructor

        /// <summary>
        /// Generate LSL Sending Stream
        /// </summary>
        /// <param name="streamName">Name of Stream</param>
        /// <param name="streamType">Data Type of Stream (EEG etc.)</param>
        /// <param name="channelCount">Channel Number</param>
        /// <param name="samplingRate">Sampling Rate (Hz)</param>
        /// <param name="dataType">Data Type of Sending Data defined in channel_format_t</param>
        /// <param name="bufferingDuration">Buffer Length (sec)</param>
        /// <param name="sourceId">Data ID</param>
        public LslSender(string streamName, string streamType, int channelCount, double samplingRate,
            channel_format_t dataType, double bufferingDuration = 0.2, string sourceId = "")
        {
            // Records the data's channel number
            m_channelCount = channelCount;

            // Generates the data buffer
            m_bufferSize = (int)(samplingRate * bufferingDuration);
            m_buffer = new List<float[]>();

            // Create the LSL stream information
            m_stremInfo = new StreamInfo(streamName, streamType, channelCount, samplingRate,
                dataType, sourceId);

            // Add channel information to LSL stream
            AddChannelInfo(m_stremInfo, channelCount);

            // Generate outlet stream of LSL
            m_outlet = new StreamOutlet(m_stremInfo);
        }

        // Add channel information to LSL stream (Function)
        // Channel name is defined as "Ch<number>"
        private void AddChannelInfo(StreamInfo stremInfo, int channelCount)
        {
            LSL.XMLElement channelDescription = stremInfo.desc().append_child("channels");
            for (int i = 0; i < channelCount; i++)
            {
                SetSingleChannelInfo(channelDescription, "Ch" + i.ToString(), "", "TimeSeries");
            }
        }

        // Set a single channel information
        private void SetSingleChannelInfo(LSL.XMLElement channelDescription, string labelName,
            string unitName, string dataTypeName)
        {
            channelDescription.append_child("channel").append_child_value("label", labelName).
                append_child_value("unit", unitName).append_child_value("type", dataTypeName);
        }

        ////////////////////////////////////////
        //// Destructor

        /// <summary>
        /// Delete the Object
        /// </summary>
        public void Dispose()
        {
            m_outlet.Dispose();
            m_stremInfo.Dispose();
        }

        ////////////////////////////////////////
        //// Method

        /// <summary>
        /// Add data to buffer and send the data when the buffer is full.
        /// </summary>
        public void Push(float[] data)
        {
            // Return when there is no consumer
            if (!m_outlet.have_consumers())
                return;

            // Add data to buffer
            m_buffer.Add(data);

            // Functions when the buffer is full
            if (m_buffer.Count >= m_bufferSize)
            {
                // NOTE: There are possibility of error in worker thread
                GC.Collect();

                // Generate sending buffer
                float[,] buffer = new float[m_buffer.Count, m_channelCount];

                // Move the data to sending buffer
                for (int i = 0; i < m_buffer.Count; i++)
                {
                    for (int ch = 0; ch < m_channelCount; ch++)
                    {
                        buffer[i, ch] = m_buffer[i][ch];
                    }
                }

                // Send data
                m_outlet.push_chunk(buffer);

                // Empty the buffer
                m_buffer.Clear();
            }
        }

        /// <summary>
        /// Sends the data in the current buffer
        /// </summary>
        public void Flush()
        {
            if (!m_outlet.have_consumers() || m_buffer.Count == 0) return;

            // Generate the sending buffer
            float[,] buffer = new float[m_buffer.Count, m_channelCount];

            // Move the data to the sending buffer
            for (int i = 0; i < m_buffer.Count; i++)
            {
                for (int ch = 0; ch < m_channelCount; ch++)
                {
                    buffer[i, ch] = m_buffer[i][ch];
                }
            }

            // Send data
            m_outlet.push_chunk(buffer);

            // Clear the buffer
            m_buffer.Clear();
        }
    }
}
