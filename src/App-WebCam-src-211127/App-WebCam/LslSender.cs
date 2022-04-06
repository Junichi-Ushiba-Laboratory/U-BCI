using System;

using LSL;

namespace LslStreaming
{
    /// <summary>
    /// Sends the frame number of the video clip by Lab Streaming Layer (LSL)
    /// </summary>
    class LslSender : IDisposable
    {
        ////////////////////////////////////////
        //// Member constants

        // Data type of stream
        const string STREAM_TYPE = "Frame number";

        ////////////////////////////////////////
        //// Member variables

        // Information fo LSL stream
        StreamInfo m_stremInfo = null;

        // Outlet of LSL stream
        private StreamOutlet m_outlet = null;

        // Buffer size to store data
        private int m_bufferSize = 1;

        // Buffer to store data
        private int[,] m_buffer = null;

        // Data number which is stored in the buffer now
        private int m_bufferCount = 0;

        ////////////////////////////////////////
        //// Constructors

        /// <summary>
        /// Generate the sending stream of LSL
        /// </summary>
        /// <param name="streamName">Name of the stream</param>
        /// <param name="samplingRate">Framerate (fps)</param>
        /// <param name="bufferingDuration">Buffer length (sec)</param>
        /// <param name="sourceId">Data ID</param>
        public LslSender(string streamName, double samplingRate, double bufferingDuration = 1,
            string sourceId = "")
        {
            // Generate the data buffer
            m_bufferSize = (int)(samplingRate * bufferingDuration);
            m_buffer = new int[1, m_bufferSize];

            // Create the LSL stream information
            m_stremInfo = new StreamInfo(streamName, STREAM_TYPE, 1, samplingRate, channel_format_t.cf_int32, sourceId);

            // Add the channel information to the LSL stream information
            AddChannelInfo(m_stremInfo);

            // Generate the sending stream of LSL
            m_outlet = new StreamOutlet(m_stremInfo);
        }

        // Add the channel information to the LSL stream information
        private void AddChannelInfo(StreamInfo stremInfo)
        {
            LSL.XMLElement channelDescription = stremInfo.desc().append_child("channels");
            channelDescription.append_child("channel").append_child_value("label", "Frame number").
                append_child_value("unit", "").append_child_value("type", "Frame");
        }

        ////////////////////////////////////////
        //// destructor

        /// <summary>
        /// Destroy the object
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
        public void Push(int data)
        {
            // Return when there is no consumer
            if (!m_outlet.have_consumers())
                return;

            // Add data to buffer
            m_buffer[0, m_bufferCount] = data;
            m_bufferCount++;

            // Functions when the buffer is full
            if (m_bufferCount >= m_bufferSize)
            {
                // Send data
                m_outlet.push_chunk(m_buffer);

                // Reset the counter
                m_bufferCount = 0;
            }
        }

        /// <summary>
        /// Send the data in the current buffer
        /// </summary>
        public void Flush()
        {
            if (!m_outlet.have_consumers() || m_bufferCount == 0) return;

            int[,] buffer = new int[1, m_bufferCount];
            for (int i = 0; i < m_bufferCount; i++)
            {
                buffer[0, i] = m_buffer[0, i];
            }
            m_outlet.push_chunk(buffer);

            // Reset the counter of buffer
            m_bufferCount = 0;
        }
    }
}
