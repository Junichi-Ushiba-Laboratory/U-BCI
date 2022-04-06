using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LslLeapMotion.LeapMotion
{
    /// <summary>
    /// Control LeapMotion and acquire data
    /// </summary>
    class Device
    {
        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// Sampling rate of data
        /// NOTE: Provides the value determined from real value because the it cannot modify during LSL connection.
        /// </summary>
        public const int FrameRate = 110;

        /// <summary>
        /// Connection handler of LeapMotion in C++
        /// </summary>
        private IntPtr m_connection;


        /////////////////////////////////////////////////////////////////////
        // Member variables (Thread management)

        /// <summary>
        /// Control flag of acquiring thread
        /// </summary>
        private bool m_threadContinue = false;

        /// <summary>
        /// Acquiring thread
        /// </summary>
        private Thread m_thread = null;


        /////////////////////////////////////////////////////////////////////
        // Member variables (Event handler)

        private EventHandler<EventArgs> m_onTracking = null;
        private EventHandler<EventArgs> m_onLostConnection = null;


        /////////////////////////////////////////////////////////////////////
        // Getter and setter

        /// <summary>
        /// Return the results
        /// </summary>
        public bool IsRunning
        {
            get { return m_thread != null; }
        }

        /// <summary>
        /// Register the event handler when the tracking data is acquired
        /// </summary>
        public EventHandler<EventArgs> OnTracking
        {
            set { m_onTracking = value; }
        }

        /// <summary>
        /// Register the event handler when the connection lost
        /// </summary>
        public EventHandler<EventArgs> OnLoadConnection
        {
            set { m_onLostConnection = value; }
        }


        /////////////////////////////////////////////////////////////////////
        // Start and finish

        /// <summary>
        /// Open the connection with LeapMotion and start the data acquisition.
        /// </summary>
        /// <returns>Return 0 when success</returns>
        public int Open()
        {
            lock (this)
            {
                if (m_thread != null) return -1;

                m_connection = CreateInterface();
                if (m_connection == null) return 1;

                m_thread = new Thread(new ThreadStart(work));
                m_threadContinue = true;
                m_thread.Start();

                return 0;
            }
        }

        /// <summary>
        /// Stop the reading thread and finish the connection with LeapMotion
        /// </summary>
        public void Close()
        {
            lock (this)
            {
                if (m_thread == null) return;

                m_threadContinue = false;
                m_thread.Join();

                DisposeInterface(m_connection);
                m_thread = null;
            }
        }


        /////////////////////////////////////////////////////////////////////
        // Data acquisition part

        /// <summary>
        /// Main part of data acquisition thread
        /// </summary>
        private void work()
        {
            // NOTE: Acquire data by polling and check the status changes

            // Secure the memory acquired from C++
            var pst = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(PollingEvent)));

            // Polling group
            while (m_threadContinue)
            {
                // Acquire the data
                int result = ReadLeapMotion(m_connection, pst);

                // Copy the memory to the structure
                PollingEvent evt = Marshal.PtrToStructure<PollingEvent>(pst);

                // Process will be split by each event
                switch ((LeapEventType)evt.Type)
                {
                    case LeapEventType.Connection:
                        Console.WriteLine("connect");
                        break;
                    case LeapEventType.ConnectionLost:
                        Console.WriteLine("lost");
                        onLostConnection((LeapEventType)evt.Type);
                        break;
                    case LeapEventType.Device:
                        Console.WriteLine("device");
                        break;
                    case LeapEventType.eLeapEventType_DeviceLost:
                        Console.WriteLine("dev lost");
                        onLostConnection((LeapEventType)evt.Type);
                        break;
                    case LeapEventType.eLeapEventType_LogEvents:
                        Console.WriteLine("log");
                        break;
                    case LeapEventType.Tracking:
                        onTracking(evt);
                        break;
                }
            }

            // Release the memory secured for reading
            Marshal.FreeHGlobal(pst);
        }

        /// <summary>
        /// Event handler when the device or connection are lost
        /// </summary>
        /// <param name="type"></param>
        private void onLostConnection(LeapEventType type)
        {
            if (m_onLostConnection != null)
            {
                string message = type == LeapEventType.ConnectionLost ?
                    "Connection have been finished" : "Device became undetectable.";
                m_onLostConnection(this, new LostConnectionEventArg(message));
            }
        }

        /// <summary>
        /// Handler for data acquisition
        /// </summary>
        /// <param name="evt"></param>
        private void onTracking(PollingEvent evt)
        {
            /*Console.WriteLine("------------------------------");
            //Console.WriteLine(evt.FrameId + ", " + evt.TimeStamp + ", " + evt.TrackingFrameId);
            Console.WriteLine(evt.HandCount + ", " + evt.LeftExist + ", " + evt.RightExist);
            Console.WriteLine(evt.HandCount + ", " + evt.LThumbX + ", " + evt.RThumbX);*/

            if (m_onTracking != null)
            {
                m_onTracking(this, new TrackEventArg(evt));
            }
        }


        /////////////////////////////////////////////////////////////////////
        // Function import from DLL

        [DllImport("LeapMotionMiniLib.dll")]
        private static extern IntPtr CreateInterface();

        [DllImport("LeapMotionMiniLib.dll")]
        private static extern void DisposeInterface(IntPtr connection);

        [DllImport("LeapMotionMiniLib.dll")]
        private static extern Int32 ReadLeapMotion(IntPtr connection, IntPtr evt);
    }
}
