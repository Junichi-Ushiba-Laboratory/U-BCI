/* Trigno SDK Windows Example.  Copyright (C) 2011 Delsys, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, and distribute the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
*/

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows.Forms;
using System.Text;
using System.IO;
using System.Net.Sockets;
using System.Threading;

// CJS-2: API for Lab Streaming Layer (LSL) API
using LSL;
using LslStreaming;

namespace TrignoSDKExample
{
    public partial class MainForm : Form
    {
        // CJS-2: Name of the program
        private string PROGRAM_NAME = "App-Delsys";

        // CJS-2: Version of the program
        private string PROGRAM_VERSION = "211111";

        private byte[] ReadAllBytes(BinaryReader reader)
        {
            const int bufferSize = 4096;
            using (var ms = new MemoryStream())
            {
                byte[] buffer = new byte[bufferSize];
                int count;
                while ((count = reader.Read(buffer, 0, buffer.Length)) != 0)
                    ms.Write(buffer, 0, count);
                return ms.ToArray();
            }
        }
        private float[] ConvertByteToFloat(byte[] array)
        {
            float[] floatArr = new float[array.Length / 4];
            for (int i = 0; i < floatArr.Length; i++)
            {
                if (BitConverter.IsLittleEndian)
                {
                    Array.Reverse(array, i * 4, 4);
                }
                floatArr[i] = BitConverter.ToSingle(array, i * 4);
            }
            return floatArr;
        }
        //example of creating a list of sensor types to keep track of various TCP streams...
        enum SensorTypes { SensorTrigno, SensorTrignoImu, SensorTrignoMiniHead, NoSensor, SensorQuattro };

        private List<SensorTypes> _sensors = new List<SensorTypes>();

        private Dictionary<string, SensorTypes> sensorList = new Dictionary<string, SensorTypes>();

        //The following are used for TCP/IP connections
        private TcpClient commandSocket;
        private TcpClient emgSocket;
        private TcpClient accSocket;
        private TcpClient imuEmgSocket;
        private TcpClient imuAuxSocket;


        private const int commandPort = 50040;  //server command port
        private const int emgPort = 50041;  //port for EMG data
        private const int accPort = 50042;  //port for acc data
        private const int ImuEmgDataPort = 50043;
        private const int ImuAuxDataPort = 50044;

        //The following are streams and readers/writers for communication
        private NetworkStream commandStream;
        private NetworkStream emgStream;
        private NetworkStream accStream;
        private NetworkStream imuEmgStream;
        private NetworkStream imuAuxStream;
        private StreamReader commandReader;
        private StreamWriter commandWriter;

        private List<float>[] emgDataList = new List<float>[16];
        private List<float>[] accXDataList = new List<float>[16];
        private List<float>[] accYDataList = new List<float>[16];
        private List<float>[] accZDataList = new List<float>[16];

        private List<float>[] imuEmgDataList = new List<float>[16];
        private List<float>[] imuAxDataList = new List<float>[16];
        private List<float>[] imuAyDataList = new List<float>[16];
        private List<float>[] imuAzDataList = new List<float>[16];
        private List<float>[] imuGxDataList = new List<float>[16];
        private List<float>[] imuGyDataList = new List<float>[16];
        private List<float>[] imuGzDataList = new List<float>[16];
        private List<float>[] imuMxDataList = new List<float>[16];
        private List<float>[] imuMyDataList = new List<float>[16];
        private List<float>[] imuMzDataList = new List<float>[16];

        public StringBuilder emg_data_string = new StringBuilder();

        public StringBuilder accx_data_string = new StringBuilder();
        public StringBuilder accy_data_string = new StringBuilder();
        public StringBuilder accz_data_string = new StringBuilder();

        public StringBuilder im_emg_data_string = new StringBuilder();

        public StringBuilder im_accx_data_string = new StringBuilder();
        public StringBuilder im_accy_data_string = new StringBuilder();
        public StringBuilder im_accz_data_string = new StringBuilder();

        public StringBuilder im_gyrx_data_string = new StringBuilder();
        public StringBuilder im_gyry_data_string = new StringBuilder();
        public StringBuilder im_gyrz_data_string = new StringBuilder();

        public StringBuilder im_magx_data_string = new StringBuilder();
        public StringBuilder im_magy_data_string = new StringBuilder();
        public StringBuilder im_magz_data_string = new StringBuilder();


        //The following are storage for acquired data
        private float[] emgData = new float[16];
        private float[] imuEmgData = new float[16];

        private float[] accXData = new float[16];
        private float[] accYData = new float[16];
        private float[] accZData = new float[16];

        private float[] imuAccXData = new float[16];
        private float[] imuAccYData = new float[16];
        private float[] imuAccZData = new float[16];

        private float[] gyroXData = new float[16];
        private float[] gyroYData = new float[16];
        private float[] gyroZData = new float[16];

        private float[] magXData = new float[16];
        private float[] magYData = new float[16];
        private float[] magZData = new float[16];

        private bool connected = false; //true if connected to server
        private bool running = false;   //true when acquiring data

        //Server commands
        private const string COMMAND_QUIT = "QUIT";
        private const string COMMAND_GETTRIGGERS = "TRIGGER?";
        private const string COMMAND_SETSTARTTRIGGER = "TRIGGER START";
        private const string COMMAND_SETSTOPTRIGGER = "TRIGGER STOP";
        private const string COMMAND_START = "START";
        private const string COMMAND_STOP = "STOP";
        private const string COMMAND_SENSOR_TYPE = "TYPE?";

        //Threads for acquiring emg and acc data
        private Thread emgThread;
        private Thread accThread;
        private Thread imuEmgThread;
        private Thread imuAuxThread;

        // CJS-2: Object that sends the data by Lab Streaming Layer (LSL)
        private LslSender m_lslSenderForEmg = null;     // For EMG sensor
        private LslSender m_lslSenderForAcc = null;     // For accelaration sensor

        // CJS-2: Base name of LSL
        const string LSL_BASE_NAME = "Delsys";

        //before your loop
        StringBuilder csvStandardSensors = new StringBuilder();
        StringBuilder csvIMSensors = new StringBuilder();

        //The constructor for our form
        public MainForm()
        {
            InitializeComponent();
            sensorList.Add("A", SensorTypes.SensorTrigno);
            sensorList.Add("D", SensorTypes.SensorTrigno);
            sensorList.Add("L", SensorTypes.SensorTrignoImu);
            sensorList.Add("J", SensorTypes.SensorTrignoMiniHead);
            sensorList.Add("Q", SensorTypes.SensorQuattro);

            tb_FilePath.Text = Environment.GetFolderPath(Environment.SpecialFolder.MyDocuments);

            // CJS-2: Set the form title
            this.Text = PROGRAM_NAME + "-" + PROGRAM_VERSION;
        }

        //Connect button handler
        private void connectButton_Click(object sender, EventArgs e)
        {
            try
            {
                //Establish TCP/IP connection to server using URL entered
                commandSocket = new TcpClient(serverURL.Text, commandPort);

                //Set up communication streams
                commandStream = commandSocket.GetStream();
                commandReader = new StreamReader(commandStream, Encoding.ASCII);
                commandWriter = new StreamWriter(commandStream, Encoding.ASCII);

                //Get initial response from server and display
                responseLine.Text = commandReader.ReadLine();
                commandReader.ReadLine();   //get extra line terminator
                connected = true;   //indicate that we are connected
                connectButton.Enabled = false;  //disable connect button
                quitButton.Enabled = true;  //enable quit button

                // ===== CJS-2: Add LSL =====

                // Dispose when LSL sending object exists
                if (m_lslSenderForEmg != null) m_lslSenderForEmg.Dispose();
                if (m_lslSenderForAcc != null) m_lslSenderForAcc.Dispose();

                // Get the unique name of LSL
                string lslNameForEmg = GetUniqueLslName(LSL_BASE_NAME + "-EMG");
                string lslNameForAcc = GetUniqueLslName(LSL_BASE_NAME + "-ACC");

                // Generates the sending LSL object that sends the EMG sensor and acceleration sensor
                // The name follows the rule of "<LSL base_name>-EMG" and "<LSL base_name>-ACC"
                m_lslSenderForEmg = new LslSender(lslNameForEmg, "EMG", 16, 1926,
                       channel_format_t.cf_float32, 32, "");
                m_lslSenderForAcc = new LslSender(lslNameForAcc, "ACC", 48, 1926,
                       channel_format_t.cf_float32, 32, "");

                // Displays the name of LSL
                _lslNameLabel.Text = "LSL Name: " + lslNameForEmg + ", " + lslNameForAcc;

                // =============================
            }
            catch (Exception connectException)
            {
                //connection failed, display error message
                MessageBox.Show("Could not connect.\n" + connectException.Message);
            }

            //build a list of connected sensor types
            _sensors = new List<SensorTypes>();
            for (int i = 1; i <= 16; i++)
            {
                string query = "SENSOR " + i + " " + COMMAND_SENSOR_TYPE;
                string response = SendCommand(query);
                _sensors.Add(response.Contains("INVALID") ? SensorTypes.NoSensor : sensorList[response]);
            }

            SendCommand("UPSAMPLE OFF");
            commandLine.Text = "";
            responseLine.Text = "";
        }

        // CJS-2: Get unique name of LSL
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

        //Quit button handler
        private void quitButton_Click(object sender, EventArgs e)
        {
            //Check if running and display error message if not
            if (running)
            {
                MessageBox.Show("Can't quit while acquiring data!");
                return;
            }

            //send QUIT command
            SendCommand(COMMAND_QUIT);

            connected = false;  //no longer connected
            connectButton.Enabled = true;   //enable connect button
            quitButton.Enabled = false; //disable quit button

            //Close all streams and connections
            commandReader.Close();
            commandWriter.Close();
            commandStream.Close();
            commandSocket.Close();
            emgStream.Close();
            emgSocket.Close();

            accStream.Close();
            accSocket.Close();

            imuEmgStream.Close();
            imuEmgSocket.Close();

            imuAuxStream.Close();
            imuAuxSocket.Close();
        }

        //Send a command to the server and get the response
        private string SendCommand(string command)
        {
            string response = "";

            //Check if connected
            if (connected)
            {
                //Send the command
                commandLine.Text = command;
                commandWriter.WriteLine(command);
                commandWriter.WriteLine();  //terminate command
                commandWriter.Flush();  //make sure command is sent immediately

                //Read the response line and display
                response = commandReader.ReadLine();
                commandReader.ReadLine();   //get extra line terminator
                responseLine.Text = response;
            }
            else
                MessageBox.Show("Not connected.");
            return response;    //return the response we got
        }

        //Set start trigger button handler
        private void setStartTriggerButton_Click(object sender, EventArgs e)
        {
            //Get the state of the check box and send command
            string state;
            if (startTrigger.Checked)
                state = " ON";
            else
                state = " OFF";
            string response = SendCommand(COMMAND_SETSTARTTRIGGER + state);
        }

        //Set stop trigger button handler
        private void setStopTriggerButton_Click(object sender, EventArgs e)
        {
            //Get the state of the check box and send command
            string state;
            if (stopTrigger.Checked)
                state = " ON";
            else
                state = " OFF";
            string response = SendCommand(COMMAND_SETSTOPTRIGGER + state);
        }

        //Get triggers button handler
        private void getTriggers_Click(object sender, EventArgs e)
        {
            //Send command to get current trigger states
            string response = SendCommand(COMMAND_GETTRIGGERS);
            if (response == "")
                return;

            //Parse the response if not blank and set the state of the check boxes
            string[] words = response.Split(new char[] { ' ' });
            if (words[1] == "ON")
                startTrigger.Checked = true;
            else
                startTrigger.Checked = false;
            if (words[3] == "ON")
                stopTrigger.Checked = true;
            else
                stopTrigger.Checked = false;
        }

        //Start button handler
        private void startButton_Click(object sender, EventArgs e)
        {
            if (!connected)
            {
                MessageBox.Show("Not connected.");
                return;
            }

            //write data to csv
            csvStandardSensors = new StringBuilder();
            csvIMSensors = new StringBuilder();

            for (int i = 0; i < _sensors.Count; i++)
            {
                //Get First Data
                SensorTypes sensor = _sensors[i];
                switch (sensor)
                {
                    case SensorTypes.SensorTrignoImu:
                        csvIMSensors.Append(sensor + "EMG" + ",");
                        csvIMSensors.Append(sensor + "ACCX" + ",");
                        csvIMSensors.Append(sensor + "ACCY" + ",");
                        csvIMSensors.Append(sensor + "ACCZ" + ",");
                        csvIMSensors.Append(sensor + "GYROX" + ",");
                        csvIMSensors.Append(sensor + "GYROY" + ",");
                        csvIMSensors.Append(sensor + "GYROZ" + ",");
                        csvIMSensors.Append(sensor + "MAGX" + ",");
                        csvIMSensors.Append(sensor + "MAGY" + ",");
                        csvIMSensors.Append(sensor + "MAGZ" + ",");
                        break;
                    case SensorTypes.NoSensor:
                        //append nothing
                        break;
                    default:
                        csvStandardSensors.Append(sensor + "EMG" + ",");
                        csvStandardSensors.Append(sensor + "ACCX" + ",");
                        csvStandardSensors.Append(sensor + "ACCY" + ",");
                        csvStandardSensors.Append(sensor + "ACCZ" + ",");
                        break;
                }

            }
            if (csvStandardSensors.Length > 1)
                csvStandardSensors.Remove(csvStandardSensors.Length - 1, 1);
            if (csvIMSensors.Length > 1)
                csvIMSensors.Remove(csvIMSensors.Length - 1, 1);
            csvStandardSensors.Append(Environment.NewLine);
            csvIMSensors.Append(Environment.NewLine);
            for (int i = 0; i < 16; i++)
            {
                imuEmgDataList[i] = new List<float>();

                imuAxDataList[i] = new List<float>();
                imuAyDataList[i] = new List<float>();
                imuAzDataList[i] = new List<float>();

                imuGxDataList[i] = new List<float>();
                imuGyDataList[i] = new List<float>();
                imuGzDataList[i] = new List<float>();

                imuMxDataList[i] = new List<float>();
                imuMyDataList[i] = new List<float>();
                imuMzDataList[i] = new List<float>();

                emgDataList[i] = new List<float>();

                accXDataList[i] = new List<float>();
                accYDataList[i] = new List<float>();
                accZDataList[i] = new List<float>();
            }
            //Clear stale data
            emgData = new float[16];
            imuEmgData = new float[16];

            accXData = new float[16];
            accYData = new float[16];
            accZData = new float[16];

            imuAccXData = new float[16];
            imuAccYData = new float[16];
            imuAccZData = new float[16];

            gyroXData = new float[16];
            gyroYData = new float[16];
            gyroZData = new float[16];

            magXData = new float[16];
            magYData = new float[16];
            magZData = new float[16];

            //Establish data connections and create streams
            emgSocket = new TcpClient(serverURL.Text, emgPort);
            accSocket = new TcpClient(serverURL.Text, accPort);
            imuEmgSocket = new TcpClient(serverURL.Text, ImuEmgDataPort);
            imuAuxSocket = new TcpClient(serverURL.Text, ImuAuxDataPort);

            emgStream = emgSocket.GetStream();
            accStream = accSocket.GetStream();
            imuEmgStream = imuEmgSocket.GetStream();
            imuAuxStream = imuAuxSocket.GetStream();

            //Create data acquisition threads
            emgThread = new Thread(EmgWorker);
            emgThread.IsBackground = true;
            accThread = new Thread(AccWorker);
            accThread.IsBackground = true;
            imuEmgThread = new Thread(ImuEmgWorker);
            imuEmgThread.IsBackground = true;
            imuAuxThread = new Thread(ImuAuxWorker);
            imuAuxThread.IsBackground = true;

            //Indicate we are running and start up the acquisition threads
            running = true;
            emgThread.Start();
            accThread.Start();
            imuEmgThread.Start();
            imuAuxThread.Start();

            //set emg sample rate to 1926 Hz
            string a = SendCommand("RATE?");

            //Send start command to server to stream data
            string response = SendCommand(COMMAND_START);

            //check response
            if (response.StartsWith("OK"))
            {
                //Enable stop button and disable start button
                startButton.Enabled = false;
                stopButton.Enabled = true;

                //Start the UI update timer
                timer1.Start();
            }
            else
                running = false;    //stop threads
        }

        //Stop button handler
        private void stopButton_Click(object sender, EventArgs e)
        {
            // CJS-2: Send data if the buffer is not empty
            m_lslSenderForEmg.Flush();
            m_lslSenderForAcc.Flush();

            running = false;    //no longer running
                                //Wait for threads to terminate
            emgThread.Join();
            accThread.Join();

            //Send stop command to server
            string response = SendCommand(COMMAND_STOP);
            if (!response.StartsWith("OK"))
                MessageBox.Show("Server failed to stop. Further actions may fail.");

            //Enable start button and disable stop button
            startButton.Enabled = true;
            stopButton.Enabled = false;
            timer1.Stop();  //stop the UI update timer

            //big parse function
            int emgIndex = 0;
            int auxIndex = 0;
            int imEmgIndex = 0;
            int imAuxIndex = 0;
            while (imEmgIndex < imuEmgDataList[0].Count - 16)
            {
                for (int i = 0; i < 16; i++) //emgDataList will contain the most samples
                {
                    if (_sensors[i] == SensorTypes.SensorTrignoImu)
                    {
                        csvIMSensors.Append(imuEmgDataList[i][imEmgIndex] + ",");
                        csvIMSensors.Append(imuAxDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuAyDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuAzDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuGxDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuGyDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuGzDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuMxDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuMyDataList[i][imAuxIndex] + ",");
                        csvIMSensors.Append(imuMzDataList[i][imAuxIndex] + ",");

                    }
                }
                if (imEmgIndex % 15 == 0)
                    imAuxIndex++;
                imEmgIndex++;
                csvIMSensors.Remove(csvIMSensors.Length - 1, 1);
                csvIMSensors.Append(Environment.NewLine);
            }


            while (emgIndex < emgDataList[0].Count - 16)
            {
                for (int i = 0; i < 16; i++) //emgDataList will contain the most samples
                {
                    if (_sensors[i] == SensorTypes.SensorTrigno)
                    {
                        csvStandardSensors.Append(emgDataList[i][emgIndex] + ",");
                        csvStandardSensors.Append(accXDataList[i][auxIndex] + ",");
                        csvStandardSensors.Append(accYDataList[i][auxIndex] + ",");
                        csvStandardSensors.Append(accZDataList[i][auxIndex] + ",");
                    }
                }
                if (emgIndex % 27 == 0)
                    auxIndex++;
                emgIndex++;
                csvStandardSensors.Remove(csvStandardSensors.Length - 1, 1);
                csvStandardSensors.Append(Environment.NewLine);
            }

            File.WriteAllText(tb_FilePath.Text + "\\IM_Data.csv", csvIMSensors.ToString());
            File.WriteAllText(tb_FilePath.Text + "\\Stan_Data.csv", csvStandardSensors.ToString());

        }
        /// <summary>
        /// Thread for emg data acquisition
        /// CJS-2: Sending the EMG data by LSL
        /// </summary>
        private void EmgWorker()
        {
            emgStream.ReadTimeout = 1000;    //set timeout

            //Create a binary reader to read the data
            BinaryReader reader = new BinaryReader(emgStream);

            while (running)
            {
                try
                {
                    // CJS-2: Generate the sensor data array for sending LSL
                    float[] samples = new float[16];

                    // Demultiplex the data and save for UI display
                    for (int sn = 0; sn < 16; ++sn)
                    {
                        // Get the EMG data
                        float sample = reader.ReadSingle();

                        // CJS-2: Store the EMG data to LSL sending object
                        samples[sn] = sample;

                        emgDataList[sn].Add(sample);
                        //emgDataList[sn].Add(reader.ReadSingle());
                    }

                    // CJS-2: Push the data to LSL sending object
                    m_lslSenderForEmg.Push(samples);
                }
                catch (IOException ee)
                {
                    //Trace.WriteLine("Error in emg found");
                }
            }

            reader.Close(); //close the reader. This also disconnects
        }


        /// <summary>
        /// Thread for acc data acquisition
        /// CJS-2: Sending the Acceleration data by LSL
        /// </summary>
        private void AccWorker()
        {
            accStream.ReadTimeout = 1000;    //set timeout

            //Create a binary reader to read the data
            BinaryReader reader = new BinaryReader(accStream);

            while (running)
            {
                try
                {
                    // CJS-2: Generate the sensor data array for sending LSL
                    float[] samples = new float[48];

                    //Demultiplex the data and save for UI display
                    for (int sn = 0; sn < 16; ++sn)
                    {
                        // Get the accelaration data
                        float x = reader.ReadSingle();
                        float y = reader.ReadSingle();
                        float z = reader.ReadSingle();

                        // CJS-2: Store the accelaration data to LSL sending array
                        samples[sn * 3] = x;
                        samples[sn * 3 + 1] = y;
                        samples[sn * 3 + 2] = z;

                        accXDataList[sn].Add(x);
                        accYDataList[sn].Add(y);
                        accZDataList[sn].Add(z);
                        //accXDataList[sn].Add(reader.ReadSingle());
                        //accYDataList[sn].Add(reader.ReadSingle());
                        //accZDataList[sn].Add(reader.ReadSingle());
                    }

                    // CJS-2: Push the data to LSL sending object
                    m_lslSenderForAcc.Push(samples);
                }
                catch (IOException e)
                {
                    //catch errors
                }
            }

            reader.Close(); //close the reader. This also disconnects
        }

        /// <summary>
        /// Thread for imu emg acquisition
        /// </summary>
        private void ImuEmgWorker()
        {
            imuEmgStream.ReadTimeout = 1000;    //set timeout

            BinaryReader reader = new BinaryReader(imuEmgStream);
            while (running)
            {
                try
                {
                    for (int sn = 0; sn < 16; ++sn)
                        imuEmgDataList[sn].Add(reader.ReadSingle());
                }
                catch (IOException e)
                {

                }
            }

        }

        /// <summary>
        /// Thread for imu acc/gyro/mag acquisition
        /// </summary>
        private void ImuAuxWorker()
        {
            imuAuxStream.ReadTimeout = 1000;    //set timeout

            //Create a binary reader to read the data
            BinaryReader reader = new BinaryReader(imuAuxStream);

            while (running)
            {
                try
                {
                    //Demultiplexes the data and save for UI display
                    for (int sn = 0; sn < 16; ++sn)
                    {
                        imuAxDataList[sn].Add(reader.ReadSingle());
                        imuAyDataList[sn].Add(reader.ReadSingle());
                        imuAzDataList[sn].Add(reader.ReadSingle());
                        imuGxDataList[sn].Add(reader.ReadSingle());
                        imuGyDataList[sn].Add(reader.ReadSingle());
                        imuGzDataList[sn].Add(reader.ReadSingle());
                        imuMxDataList[sn].Add(reader.ReadSingle());
                        imuMyDataList[sn].Add(reader.ReadSingle());
                        imuMzDataList[sn].Add(reader.ReadSingle());
                    }
                }
                catch (IOException)
                {
                    //Trace.WriteLine("Error in acc found");
                }
            }

            reader.Close(); //close the reader. This also disconnects
        }

        //UI update timer handler
        private void timer1_Tick(object sender, EventArgs e)
        {
            //Here we display the last values saved by the acquisition threads.
            //It should be noted that it is possible that the three acc samples may not
            //correspond to the same point in time since no locking between threads is employed.
            //This should be considered in a real application.

            //for (int i = 0; i < sensorList.Count; i++)
            //{

            //    //Get First Data
            //    SensorTypes sensor = _sensors[i];
            //    switch (sensor)
            //    {
            //        case SensorTypes.SensorTrignoImu:

            //                csv.Append(imuEmgData[i] + ",");
            //                csv.Append(imuAccXData[i] + ",");
            //                csv.Append(imuAccYData[i] + ",");
            //                csv.Append(imuAccZData[i] + ",");
            //                csv.Append(gyroXData[i] + ",");
            //                csv.Append(gyroYData[i] + ",");
            //                csv.Append(gyroZData[i] + ",");
            //                csv.Append(magXData[i] + ",");
            //                csv.Append(magYData[i] + ",");
            //                csv.Append(magZData[i] + ",");

            //            break;
            //        case SensorTypes.NoSensor:
            //            //append nothing
            //            break;
            //        default:
            //            csv.Append(emgData[i] + ",");
            //            csv.Append(accXData[i] + ",");
            //            csv.Append(accYData[i] + ",");
            //            csv.Append(accZData[i] + ",");
            //            break;
            //    }
            //}
            //csv.Append(Environment.NewLine);

            //Display data based on sensor type
            SensorTypes currentSensorType = _sensors[(int)sensorNumber.Value - 1];

            switch (currentSensorType)
            {
                case SensorTypes.SensorTrignoImu:
                    if (imuEmgDataList[(int)(sensorNumber.Value - 1)].Count > 0)
                    {
                        emgDataDisplay.Text = imuEmgDataList[(int)(sensorNumber.Value - 1)][imuEmgDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accXDisplay.Text = imuAxDataList[(int)(sensorNumber.Value - 1)][imuAxDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accYDisplay.Text = imuAyDataList[(int)(sensorNumber.Value - 1)][imuAyDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accZDisplay.Text = imuAzDataList[(int)(sensorNumber.Value - 1)][imuAzDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        gxDisplay.Text = imuGxDataList[(int)(sensorNumber.Value - 1)][imuGxDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        gyDisplay.Text = imuGyDataList[(int)(sensorNumber.Value - 1)][imuGyDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        gzDisplay.Text = imuGzDataList[(int)(sensorNumber.Value - 1)][imuGzDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        mxDisplay.Text = imuMxDataList[(int)(sensorNumber.Value - 1)][imuMxDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        myDisplay.Text = imuMyDataList[(int)(sensorNumber.Value - 1)][imuMyDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        mzDisplay.Text = imuMzDataList[(int)(sensorNumber.Value - 1)][imuMzDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                    }
                    break;
                case SensorTypes.NoSensor:
                    emgDataDisplay.Text = "N/A";
                    accXDisplay.Text = "N/A";
                    accYDisplay.Text = "N/A";
                    accZDisplay.Text = "N/A";
                    gxDisplay.Text = "N/A";
                    gyDisplay.Text = "N/A";
                    gzDisplay.Text = "N/A";
                    mxDisplay.Text = "N/A";
                    myDisplay.Text = "N/A";
                    mzDisplay.Text = "N/A";
                    break;
                default:
                    if (emgDataList[(int)(sensorNumber.Value - 1)].Count > 0)
                    {
                        emgDataDisplay.Text = emgDataList[(int)(sensorNumber.Value - 1)][emgDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accXDisplay.Text = accXDataList[(int)(sensorNumber.Value - 1)][accXDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accYDisplay.Text = accYDataList[(int)(sensorNumber.Value - 1)][accYDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        accZDisplay.Text = accZDataList[(int)(sensorNumber.Value - 1)][accZDataList[(int)(sensorNumber.Value - 1)].Count - 1].ToString();
                        gxDisplay.Text = "N/A";
                        gyDisplay.Text = "N/A";
                        gzDisplay.Text = "N/A";
                        mxDisplay.Text = "N/A";
                        myDisplay.Text = "N/A";
                        mzDisplay.Text = "N/A";
                    }
                    break;
            }

            //look for STOP from server
            if (commandStream.DataAvailable)
            {
                if ((responseLine.Text = commandReader.ReadLine()).StartsWith("STOPPED"))
                {
                    //A stop was received from te server.
                    commandReader.ReadLine();   //read extra line terminator

                    //Stop threads and wait for termination
                    running = false;
                    emgThread.Join();
                    accThread.Join();
                    imuEmgThread.Join();
                    imuAuxThread.Join();

                    //Enable start button and disable stop button
                    startButton.Enabled = true;
                    stopButton.Enabled = false;
                    commandLine.Text = "";  //clear command line display
                    timer1.Stop();  //stop the UI display update timer
                }
            }
        }
    }

}

