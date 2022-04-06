using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Tobii.Research;

namespace App_TobiiSpec.Record
{
    /// <summary>
    /// Class that manages the API class of Tobii and other processes
    /// </summary>
    class TobiiManager
    {
        /////////////////////////////////////////////////////////////////////
        // Member variables

        /// <summary>
        /// List of class instance that corresponds to Tobii device
        /// </summary>
        private EyeTrackerCollection m_trackerList = null;

        /// <summary>
        /// Index of selected instance (-1 when unselected)
        /// </summary>
        private int m_selectedIndex = -1;

        /// <summary>
        /// Thread of acquiring gaze information
        /// </summary>
        private Thread m_thread = null;

        /// <summary>
        /// Event handler that executes when receiving the gazing data from Tobii
        /// </summary>
        private EventHandler<GazeDataEventArgs> m_gazeEventHandler = null;

        /// <summary>
        /// Event handler when finishing the thread of gaze acquisition (unnecessary)
        /// </summary>
        private EventHandler<EventArgs> m_finishCallback = null;

        /// <summary>
        /// Control flag that determines the end or continuation of the thread of gaze acquisition
        /// </summary>
        private bool m_continue = false;


        /////////////////////////////////////////////////////////////////////
        // Getter and setter

        /// <summary>
        /// Get the device number of tobii device
        /// </summary>
        public int Count
        {
            get { return m_trackerList.Count; }
        }

        /// <summary>
        /// Get and set the index of selected Tobii device
        /// </summary>
        public int SelectedIndex
        {
            get { return m_selectedIndex; }
            set
            {
                m_selectedIndex = value;
                if (m_selectedIndex >= m_trackerList.Count) m_selectedIndex = -1;
            }
        }

        /// <summary>
        /// Get the status of data acquisition
        /// </summary>
        public bool Working
        {
            get { return m_thread != null; }
        }

        /// <summary>
        /// Get the device name by index
        /// </summary>
        /// <param name="index">Index of the device. Exception will appear when the value is unacceptance.</param>
        /// <returns>Name of the device</returns>
        public string Name(int index)
        {
            return m_trackerList[index].DeviceName + " : " + m_trackerList[index].SerialNumber;
        }


        /////////////////////////////////////////////////////////////////////
        // Acquisition of the device information

        /// <summary>
        /// Detect the Tobii inside the network. The results will be saved in the member variables.
        /// The detected instance of Tobii will be destroyed once. This is a synchronous function.
        /// </summary>
        public void Find()
        {
            if (m_trackerList != null)
            {
                foreach (var tracker in m_trackerList) tracker.Dispose();
            }

            m_trackerList = EyeTrackingOperations.FindAllEyeTrackers();
        }

        /// <summary>
        /// Get the list of sampling rate that corresponds to the selected Tobii device
        /// </summary>
        /// <returns></returns>
        public List<float> EnumSaplingRateList()
        {
            if (m_selectedIndex < 0)
            {
                throw new InvalidOperationException("Please select the appropriate tracker");
            }

            List<float> dst = new List<float>();

            var allGazeOutputFrequencies = m_trackerList[m_selectedIndex].GetAllGazeOutputFrequencies();
            foreach (float gazeOutputFrequency in allGazeOutputFrequencies)
            {
                dst.Add(gazeOutputFrequency);
            }

            return dst;
        }


        /////////////////////////////////////////////////////////////////////
        // Calibration group

        /// <summary>
        /// Executes the calibration. This is a synchronous function.
        /// </summary>
        /// <param name="pictureBox">Picture box that displays the attention point. The screen size must be full.</param>
        /// <param name="finishCallback">Callback function that executes when the process is completed</param>
        /// <returns>Returns true when success.</returns>
        public bool Calibrate(PictureBox pictureBox, EventHandler<EventArgs> finishCallback)
        {
            const int MAX_RETRY = 12;

            if (m_selectedIndex < 0)
            {
                throw new InvalidOperationException("Please select the appropriate tracker");
            }

            // Generate the calibration object
            var calibration = new ScreenBasedCalibration(m_trackerList[m_selectedIndex]);

            calibration.EnterCalibrationMode();

            // Prepare the coordinates of attention point
            var pointsToCalibrate = new NormalizedPoint2D[] {
                new NormalizedPoint2D(0.5f, 0.5f),
                new NormalizedPoint2D(0.1f, 0.1f),
                new NormalizedPoint2D(0.1f, 0.9f),
                new NormalizedPoint2D(0.9f, 0.1f),
                new NormalizedPoint2D(0.9f, 0.9f),
            };

            int repeatCount = 0;

            // Collect the calibration data in each attention point
            for (int pointIndex = 0; pointIndex < pointsToCalibrate.Length; pointIndex++)
            {
                repeatCount++;
                if (repeatCount >= MAX_RETRY) break;

                // Show image in screen
                DrawPointImage((Bitmap)pictureBox.Image, pointsToCalibrate[pointIndex].X, pointsToCalibrate[pointIndex].Y);
                pictureBox.Invalidate();
                Application.DoEvents();

                // Wait for 1000 ms as time for moving the gaze
                System.Threading.Thread.Sleep(1000);

                // Get the gaze. It will try again in the next loop when failure.
                CalibrationStatus status = calibration.CollectData(pointsToCalibrate[pointIndex]);
                if (status != CalibrationStatus.Success) pointIndex--;
            }

            // Execute the calibration by collected data
            CalibrationResult calibrationResult = calibration.ComputeAndApply();
            Console.WriteLine("Compute and apply returned {0} and collected at {1} points.",
                calibrationResult.Status, calibrationResult.CalibrationPoints.Count);

            calibration.LeaveCalibrationMode();

            // Executes the callback prepared for completion if it is registered
            if (finishCallback != null) finishCallback(this, null);

            // Returns the result
            return repeatCount < MAX_RETRY;
        }

        /// <summary>
        /// Save the calibration of selected Tobii instance for the next start-up.
        /// NOTE: There are possibility of error when the next device has no compatibility.
        /// </summary>
        /// <param name="path"></param>
        public void SaveCalibration(string path)
        {
            if (m_selectedIndex < 0) return;

            using (System.IO.FileStream fileStream = System.IO.File.Create(path))
            {
                var dataContractSerializer = new System.Runtime.Serialization.DataContractSerializer(typeof(CalibrationData));
                CalibrationData calibrationData = m_trackerList[m_selectedIndex].RetrieveCalibrationData();
                dataContractSerializer.WriteObject(fileStream, calibrationData);
            }
        }

        /// <summary>
        /// Read the calibration data to selected Tobii instance.
        /// NOTE: There are possibility of error when the device has no compatibility.
        /// </summary>
        /// <param name="path"></param>
        public void LoadCalibration(string path)
        {
            if (m_selectedIndex < 0)
            {
                throw new InvalidOperationException("Please select the appropriate tracker");
            }

            if (!File.Exists(path)) return;

            // Reopen the file and read the calibration data back.
            using (System.IO.FileStream fileStream = System.IO.File.OpenRead(path))
            {
                var dataContractSerializer = new System.Runtime.Serialization.DataContractSerializer(typeof(CalibrationData));
                CalibrationData calibrationData = dataContractSerializer.ReadObject(fileStream) as CalibrationData;
                if (calibrationData.Data.Length != 0)
                {
                    m_trackerList[m_selectedIndex].ApplyCalibrationData(calibrationData);
                }
            }
        }

        /// <summary>
        /// Illustrates the attention point for calibration
        /// </summary>
        /// <param name="target">Picture box for illustration. It has to be set to "Bitmap" mode.</param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        private void DrawPointImage(Bitmap target, float x, float y)
        {
            float cx = target.Width * x;
            float cy = target.Height * y;
            float size = 20;

            Graphics gdc = Graphics.FromImage(target);
            gdc.Clear(Color.White);
            gdc.DrawEllipse(Pens.Blue, cx - size / 2, cy - size / 2, size, size);
            gdc.Dispose();
        }


        /////////////////////////////////////////////////////////////////////
        // Gaze data acquisition

        /// <summary>
        /// Start gaze data acquisition
        /// </summary>
        /// <param name="samplingRate">Sampling rate</param>
        /// <param name="gazeEventHandler">Callback for receiving gaze data</param>
        /// <param name="finishCallback">Callback for ending process (optional).</param>
        public void GetGazeData(
            float samplingRate,
            EventHandler<GazeDataEventArgs> gazeEventHandler,
            EventHandler<EventArgs> finishCallback)
        {
            if (m_selectedIndex < 0)
            {
                throw new InvalidOperationException("Please select the appropriate tracker");
            }

            // Return when the thread is null
            if (m_thread != null) return;

            // Set the sampling rate and target animal
            m_trackerList[m_selectedIndex].SetGazeOutputFrequency(samplingRate);
            m_trackerList[m_selectedIndex].SetEyeTrackingMode("human");

            // Register the callback
            m_gazeEventHandler = gazeEventHandler;
            m_finishCallback = finishCallback;

            // Start the thread of gaze acquisition
            m_continue = true;
            m_thread = new Thread(new ThreadStart(Record));
            m_thread.Start();
        }

        /// <summary>
        /// Thread of gaze acquisition (Main)
        /// </summary>
        private void Record()
        {
            // Register the callback and start the gaze acquisition
            m_trackerList[m_selectedIndex].GazeDataReceived += m_gazeEventHandler;
            // Wait until the end flag is set.
            // NOTE: Process of Tobii will be executed inside the internal API thread
            // NOTE: This should use the signal rather than polling because this doesn't process anything
            while (m_continue) Thread.Sleep(200);
            // Finish the gaze acquisition and deactivate the callback
            m_trackerList[m_selectedIndex].GazeDataReceived -= m_gazeEventHandler;

            // Process the finish process
            if (m_finishCallback != null) m_finishCallback(this, null);
            m_continue = false;
            m_thread = null;
        }

        /// <summary>
        /// Stop the gaze acquisition process
        /// </summary>
        public void StopRecord()
        {
            m_continue = false;
            if (m_thread != null) m_thread.Join();
        }
    }
}
