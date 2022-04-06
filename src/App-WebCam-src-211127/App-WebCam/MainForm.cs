using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Windows.Forms;

// API of Lab Streaming Layer (LSL)
using LslStreaming;

// Library of video recording
using OpenCvSharp;

namespace App_WebCam
{
    /// <summary>
    /// Main window
    /// </summary>
    public partial class MainForm : Form
    {
        ////////////////////////////////////////
        //// Member constants

        // Name of the program
        private string PROGRAM_NAME = "App-WebCam";

        // Version of the program
        private string PROGRAM_VERSION = "211127";

        // Frame size of video
        private const int WIDTH = 640;
        private const int HEIGHT = 480;

        // Framerate (fps) of video recording
        private const int FRAME_RATE = 30;

        // Frame number and the location information to calculate the UNIX time
        private readonly OpenCvSharp.Point[] POSITION_LIST = {
            new OpenCvSharp.Point(0, 0),
            new OpenCvSharp.Point(90, 20),
            new OpenCvSharp.Point(0, 15),
            new OpenCvSharp.Point(440, 0),
            new OpenCvSharp.Point(640, 20),
            new OpenCvSharp.Point(460, 15)
        };

        // Base name of LSL。
        private const string LSL_BASE_NAME = "WebCamera";

        // Length of buffering data for sending data by LSL (sec)
        const int BUFFERING_DURATION = 1;

        ////////////////////////////////////////
        //// Member variables

        // Path of directory that stores video file
        private string m_videoFolderPath =
            Environment.GetFolderPath(Environment.SpecialFolder.DesktopDirectory);

        // Path of directory that stores video file
        private VideoWriter m_videoWriter = null;

        // Flag whether the video recording is activated.
        private bool m_isRecording = false;

        // Frame number of the video
        private int m_frameNum = 0;

        // Object that sends the frame number by Lab Streaming Layer (LSL)
        private LslSender m_lslSender = null;

        ////////////////////////////////////////
        //// Constructors

        public MainForm()
        {
            // Create Form
            InitializeComponent();

            // Set the title of the form
            this.Text = PROGRAM_NAME + "-" + PROGRAM_VERSION;

            // Get the unique name of LSL
            string lslName = GetUniqueLslName(LSL_BASE_NAME);

            // Create sending object of LSL
            m_lslSender = new LslSender(lslName, FRAME_RATE, BUFFERING_DURATION);

            // Display the name of LSL
            _lslNameLabel.Text = "LSL name: " + lslName;
        }

        // Get the unique name of LSL
        private string GetUniqueLslName(string lslBaseName)
        {
            // Get the registered name list of LSL
            LSL.StreamInfo[] streamInfoList = LSL.LSL.resolve_streams(1.0);
            List<string> streamNameList = new List<string>();
            for (int i = 0; i < streamInfoList.Length; i++)
            {
                LSL.StreamInlet inlet = new LSL.StreamInlet(streamInfoList[i]);
                streamNameList.Add(inlet.info().name());
            }

            // Create the unique name of LSL
            // If the lslBaseName exists, it appends an integer index at the end
            string lslName = lslBaseName;
            int num = 1;
            while (true)
            {
                if (streamNameList.Contains(lslName))
                {
                    lslName = lslBaseName + (++num).ToString();
                }
                else break;
            }

            return lslName;
        }


        ////////////////////////////////////////
        //// Method

        // Set the file that saves the video by file selection dialog
        // The video format is AVI-format (*.avi)
        private void _selectVideFileBtn_Click(object sender, EventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            dialog.InitialDirectory = m_videoFolderPath;
            dialog.FileName = "";
            dialog.AddExtension = true;
            dialog.OverwritePrompt = true;
            dialog.CheckPathExists = true;
            dialog.Title = "Set Video File (*.avi)";
            dialog.Filter = "Video files (*.avi)|*.avi| All files (*.*)|*.*";

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                // Show the file path
                _videoFilePathBox.Text = dialog.FileName;

                // Record the folder that stores the video file
                m_videoFolderPath = Path.GetDirectoryName(dialog.FileName);
            }
        }

        // Start video record streaming
        // This doesn't record nor send by LSL
        private void _viewBtn_Click(object sender, EventArgs e)
        {
            // Modify the form control
            SetFormControls(true);

            // Start the recording by woker thread
            m_isRecording = false;
            _backgroundWorker.RunWorkerAsync();
        }

        //  Start video capturing
        private void _recBtn_Click(object sender, EventArgs e)
        {
            // Get the path of video file
            string videoFilePath = _videoFilePathBox.Text;

            try
            {
                // Confirm whether the video file path is valid
                if (String.IsNullOrEmpty(videoFilePath) ||
                    !Directory.Exists(Path.GetDirectoryName(videoFilePath)))
                    throw new Exception("The video file path is not valid.");
                else if (Path.GetExtension(videoFilePath) != ".avi")
                    throw new Exception("A video file must be an AVI format (*.avi).");

                // Generate the video file
                m_videoWriter = new VideoWriter(videoFilePath, FourCC.MJPG, FRAME_RATE,
                    new OpenCvSharp.Size(WIDTH, HEIGHT));
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            // Modify the form control
            SetFormControls(true);

            // Start the video capture by worker thread and send by LSL
            m_isRecording = true;
            _backgroundWorker.RunWorkerAsync();
        }

        // Modify the form control when video capturing
        private void SetFormControls(bool isRecording)
        {
            _recBtn.Enabled = !isRecording;
            _viewBtn.Enabled = !isRecording;
            _stopBtn.Enabled = isRecording;
            _videoFilePathBox.Enabled = !isRecording;
            _setVideFileBtn.Enabled = !isRecording;
        }

        // Start video capturing
        private void _backgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            try
            {
                // Use the default connected camera
                using (VideoCapture capture = new VideoCapture(0))
                {
                    if (!capture.IsOpened())
                        throw new OpenCVException("A camera cannot be found.");

                    // Display the preparation message
                    showPreparingMessage();

                    // Set the video capture settings
                    capture.FrameWidth = WIDTH;
                    capture.FrameHeight = HEIGHT;
                    capture.Fps = FRAME_RATE;
                    m_frameNum = 0;

                    // Generate the object that stores the image
                    Mat image = new Mat(HEIGHT, WIDTH, MatType.CV_8UC3);

                    // Get the image
                    while (true)
                    {
                        // Confirm the stopping request
                        if (_backgroundWorker.CancellationPending)
                        {
                            // Cancel the process
                            e.Cancel = true;
                            return;
                        }

                        // Get the image
                        capture.Read(image);

                        // Show image, save file, send the frame number by LSL
                        _backgroundWorker.ReportProgress(0, image);
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                FinalizeVideoCapture();
                return;
            }
        }

        // Display the preparation message
        private void showPreparingMessage()
        {
            Bitmap canvas = new Bitmap(_framePictBox.Width, _framePictBox.Height);
            Graphics graphics = Graphics.FromImage(canvas);
            Font font = new Font("Arial", 16);

            // Draw message
            graphics.DrawString("Prepareing video capture...", font, Brushes.Black,
                WIDTH / 2 - 140, HEIGHT / 2 - 50);

            // Show message
            _framePictBox.Image = canvas;

            font.Dispose();
            graphics.Dispose();
        }
        // Show image, save file, send the frame number by LSL
        private void _backgroundWorker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            try
            {
                // Get the image
                Mat image = (Mat)e.UserState;

                // When the video is capturing
                if (m_isRecording)
                {
                    // Write the frame number and UNIX time to image
                    image.Rectangle(POSITION_LIST[0], POSITION_LIST[1], Scalar.White, -1);
                    image.PutText(m_frameNum.ToString(), POSITION_LIST[2], HersheyFonts.HersheySimplex,
                        0.5, Scalar.Black);
                    image.Rectangle(POSITION_LIST[3], POSITION_LIST[4], Scalar.White, -1);
                    image.PutText(DateTime.Now.ToString(), POSITION_LIST[5], HersheyFonts.HersheySimplex,
                        0.5, Scalar.Black);

                    // Save the image file
                    m_videoWriter.Write(image);

                    // Push the frame number to LSL sending object
                    m_lslSender.Push(m_frameNum);

                    // Update the frame number
                    m_frameNum++;
                }

                // Show the image
                _framePictBox.Image = new Bitmap(image.Cols, image.Rows, (int)image.Step(),
                    PixelFormat.Format24bppRgb, image.Data);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                _backgroundWorker.CancelAsync();
            }
        }

        // Finish the video capturing
        private void _stopBtn_Click(object sender, EventArgs e)
        {
            // Request of cancel to worker thread
            _backgroundWorker.CancelAsync();
        }

        // Process the finishing process when the video capturing have been completed
        private void _backgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            FinalizeVideoCapture();
        }

        // Process the finish process of video capturing
        private void FinalizeVideoCapture()
        {
            // Close the file when the video recording is on progress
            if (m_videoWriter != null)
            {
                // Send data when the buffer is not empty
                m_lslSender.Flush();

                // Close video file
                m_videoWriter.Dispose();
                m_videoWriter = null;
            }

            m_isRecording = false;

            // Revert the modification of form control
            SetFormControls(false);
        }

        // Finishes the video capture when the state is capturing although the program is finished
        private void MainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            // Request to the worker thread to cancel
            _backgroundWorker.CancelAsync();
        }
    }
}
