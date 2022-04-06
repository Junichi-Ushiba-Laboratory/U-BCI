using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using FDTGloveUltraCSharpWrapper;

// CJS-2: API for Lab Streaming Layer (LSL) API
using LSL;
using LslStreaming;

namespace App_5DTDataGlove
{
    public partial class frmMain : Form
    {
        CfdGlove fdGlove;

        // CJS-2: Name of the program
        private string PROGRAM_NAME = "App-5DTDataGlove";

        // CJS-2: Version of the program
        private string PROGRAM_VERSION = "211126";
        // CJS-2: Object that sends the data by Lab Streaming Layer (LSL)
        private LslSender m_lslSender = null;

        // CJS-2: Base name of LSL
        const string LSL_BASE_NAME = "5DT Data Glove";

        // CJS-2: Length of buffering data for sending data by LSL
        const double BUFFERING_DURATION = 0.1;

        public frmMain()
        {
            InitializeComponent();
            fdGlove = new CfdGlove();

            // CJS-2: Set the title of the form
            this.Text = PROGRAM_NAME + "-" + PROGRAM_VERSION;
        }

        delegate void UpdateListDelegate(); // used by Update function to create delegate to update sensor list

        private void Update(object sender, EventArgs e)
        {
            // This function will probably run in a different thread from the windows controls
            //  because it is registered as a callback function in the Glove Driver
            //  (see function chkUseCallback_CheckedChanged)
            // We can't just change controls from a different thread so we first have to
            //  check if an invoke is required or not...
            if (lstSensors.InvokeRequired)
            {
                // It's on a different thread, so use Invoke.
                UpdateListDelegate d = new UpdateListDelegate(UpdateList);
                try
                {
                    this.Invoke(d, new object[] { });
                }
                catch
                {

                }
            }
            else
            {
                tmrUpdate_Tick(this, EventArgs.Empty);
            }

        }

        void UpdateList()
        {
            tmrUpdate_Tick(this, EventArgs.Empty); // update the list using the same way the timer would if it was active
        }

        // CJS-2: Sends the sensoring data by LSL
        private void tmrUpdate_Tick(object sender, EventArgs e)
        {
            if (fdGlove == null)
                return;

            lstSensors.Items.Clear();

            ushort[] arr = new ushort[20];
            float[] farr = new float[20];

            //fdGlove.GetSensor GetSensorRawAll(arr);
            fdGlove.GetSensorScaledAll(ref farr);
            fdGlove.GetSensorRawAll(ref arr);

            ushort[] upperVals = new ushort[10];
            ushort[] lowerVals = new ushort[10];

            ushort[] setupperVals = new ushort[15];
            ushort[] setlowerVals = new ushort[15];

            //setupperVals[0] = 444;
            //setlowerVals[0] = 555;
            //setupperVals[1] = 666;
            //setlowerVals[1] = 777;
            //fdGlove.SetCalibrationAll(setupperVals, setlowerVals);
            //upperVals[1] = fdGlove.getV();
            //fdGlove.GetCalibration(0, ref upperVals[0], ref lowerVals[0]);

            fdGlove.GetCalibrationAll(ref upperVals, ref lowerVals);

            // CJS-2: Generate the sensor data array for sending LSL
            float[] samples = new float[18];

            //for (int i = 0; i < fdGlove.GetNumSensors(); ++i)
            if (fdGlove.IsOpen())
            {
                for (int i = 0; i < 18; ++i)
                {
                    // Reading single values at a time - this is actually a bit faster than reading the whole array
                    // because more marshalling intensive operations need to be preformed when dealing with arrays. (driver is written in unmanaged code)
                    //ushort a = fdGlove.GetSensorRaw(i);

                    // Get the sensor data
                    float value = fdGlove.GetSensorScaled(i);
                    //lstSensors.Items.Add("Sensor " + i + " - Scaled: " + String.Format("{0:0.00}", f) + " ( Raw: " + a + ")");
                    //lstSensors.Items.Add("Sensor " + i + " - Scaled: " + String.Format("{0:0.00}", farr[i]) + " ( Raw: " + arr[i] + ") Cal:(" + lowerVals[i] + "," + upperVals[i] + ")");

                    // CJS-2: Store the sensor data for LSL sending
                    samples[i] = value;
                }

                // CJS-2: Push the sensor data to LSL sending object
                m_lslSender.Push(samples);

            }
            txtGesture.Text = fdGlove.GetGesture().ToString();
            txtPacketRate.Text = fdGlove.GetPacketRate().ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void lstSensors_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void chkUseCallback_CheckedChanged(object sender, EventArgs e)
        {
            if (chkUseCallback.Checked)
            {
                fdGlove.SetCallBack(new EventHandler(Update));
                tmrUpdate.Enabled = false;
            }
            else
            {
                fdGlove.RemoveCallBack(new EventHandler(Update));
                tmrUpdate.Enabled = true;
            }
        }

        private void btnQuit_Click(object sender, EventArgs e)
        {
            // CJS-2: Send when buffer is not empty
            m_lslSender.Flush();

            if (fdGlove != null)
                fdGlove.Close();
            Application.Exit();
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            chkUseCallback.Checked = false;
            fdGlove.Open(txtGloveLocation.Text);
            tmrUpdate.Enabled = true;

            switch (fdGlove.GetGloveType())
            {
                case (int)EGloveTypes.FD_GLOVE14UW: txtType.Text = "Data Glove 14 Ultra Wireless"; break;
                case (int)EGloveTypes.FD_GLOVE14U_USB: txtType.Text = "Data Glove 14 Ultra USB"; break;
                case (int)EGloveTypes.FD_GLOVE14U: txtType.Text = "Data Glove 14 Ultra"; break;
                case (int)EGloveTypes.FD_GLOVE16: txtType.Text = "Data Glove 16-sensor"; break;
                case (int)EGloveTypes.FD_GLOVE16W: txtType.Text = "Data Glove 16-sensor Wireless"; break;
                case (int)EGloveTypes.FD_GLOVE5U: txtType.Text = "Data Glove 5 Ultra"; break;
                case (int)EGloveTypes.FD_GLOVE5U_USB: txtType.Text = "Data Glove 5 Ultra USB"; break;
                case (int)EGloveTypes.FD_GLOVE5UW: txtType.Text = "Data Glove 5 Ultra Wireless"; break;
                case (int)EGloveTypes.FD_GLOVE7: txtType.Text = "Data Glove 7-sensor"; break;
                case (int)EGloveTypes.FD_GLOVE7W: txtType.Text = "Data Glove 7-sensor Wireless"; break;
                case (int)EGloveTypes.FD_GLOVENONE: txtType.Text = "No Glove"; break;
                default: txtType.Text = "Unknown"; break;
            }

            switch (fdGlove.GetGloveHand())
            {
                case (int)EGloveHand.FD_HAND_RIGHT: txtLR.Text = "Right"; break;
                case (int)EGloveHand.FD_HAND_LEFT: txtLR.Text = "Left"; break;
            }

            txtFirmWareVersion.Text = fdGlove.fdGetFWVersionMajor() + "." + fdGlove.fdGetFWVersionMinor();
            // ===== CJS-2: Add LSL =====
            // Destroy the object when LSL sending object exists
            if (m_lslSender != null) m_lslSender.Dispose();

            // Get the unique name of LSL
            string lslName = GetUniqueLslName(LSL_BASE_NAME);

            // Generate the LSL sending object for sending the sensor data
            m_lslSender = new LslSender(lslName, "Motion", 18, 100, channel_format_t.cf_float32, BUFFERING_DURATION, "");

            // Display the name of LSL
            _lslNameLabel.Text = "LSL Name: " + lslName;

            // =============================
        }

        // CJS-2: Get the unique name of LSL
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
        private void button1_Click(object sender, EventArgs e)
        {
            fdGlove.SetCalibration(0, 4000, 3000);

            //fdGlove.SetCalibrationAll
            //fdGlove.GetCalibration
            //fdGlove.GetCalibrationAll
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

    }
}
