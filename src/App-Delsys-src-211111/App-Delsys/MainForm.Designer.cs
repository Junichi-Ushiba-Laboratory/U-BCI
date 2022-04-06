namespace TrignoSDKExample
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.label1 = new System.Windows.Forms.Label();
            this.serverURL = new System.Windows.Forms.TextBox();
            this.connectButton = new System.Windows.Forms.Button();
            this.commandLine = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.responseLine = new System.Windows.Forms.TextBox();
            this.quitButton = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.setStopTriggerButton = new System.Windows.Forms.Button();
            this.setStartTriggerButton = new System.Windows.Forms.Button();
            this.getTriggers = new System.Windows.Forms.Button();
            this.stopTrigger = new System.Windows.Forms.CheckBox();
            this.startTrigger = new System.Windows.Forms.CheckBox();
            this.startButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.emgDataDisplay = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.sensorNumber = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.accXDisplay = new System.Windows.Forms.TextBox();
            this.accYDisplay = new System.Windows.Forms.TextBox();
            this.accZDisplay = new System.Windows.Forms.TextBox();
            this.gxDisplay = new System.Windows.Forms.TextBox();
            this.gyDisplay = new System.Windows.Forms.TextBox();
            this.gzDisplay = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.mzDisplay = new System.Windows.Forms.TextBox();
            this.myDisplay = new System.Windows.Forms.TextBox();
            this.mxDisplay = new System.Windows.Forms.TextBox();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.tb_FilePath = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this._lslNameLabel = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.sensorNumber)).BeginInit();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            //
            // label1
            //
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Server URL:";
            //
            // serverURL
            //
            this.serverURL.Location = new System.Drawing.Point(85, 11);
            this.serverURL.Name = "serverURL";
            this.serverURL.Size = new System.Drawing.Size(122, 19);
            this.serverURL.TabIndex = 1;
            this.serverURL.Text = "localhost";
            //
            // connectButton
            //
            this.connectButton.Location = new System.Drawing.Point(229, 10);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(75, 21);
            this.connectButton.TabIndex = 2;
            this.connectButton.Text = "Connect (&C)";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            //
            // commandLine
            //
            this.commandLine.Location = new System.Drawing.Point(85, 466);
            this.commandLine.Name = "commandLine";
            this.commandLine.ReadOnly = true;
            this.commandLine.Size = new System.Drawing.Size(309, 19);
            this.commandLine.TabIndex = 3;
            //
            // label2
            //
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(16, 470);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(57, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "Command:";
            //
            // label3
            //
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(16, 497);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 12);
            this.label3.TabIndex = 5;
            this.label3.Text = "Response:";
            //
            // responseLine
            //
            this.responseLine.Location = new System.Drawing.Point(85, 493);
            this.responseLine.Name = "responseLine";
            this.responseLine.ReadOnly = true;
            this.responseLine.Size = new System.Drawing.Size(309, 19);
            this.responseLine.TabIndex = 6;
            //
            // quitButton
            //
            this.quitButton.Enabled = false;
            this.quitButton.Location = new System.Drawing.Point(331, 10);
            this.quitButton.Name = "quitButton";
            this.quitButton.Size = new System.Drawing.Size(75, 21);
            this.quitButton.TabIndex = 7;
            this.quitButton.Text = "Quit (&Q)";
            this.quitButton.UseVisualStyleBackColor = true;
            this.quitButton.Click += new System.EventHandler(this.quitButton_Click);
            //
            // groupBox1
            //
            this.groupBox1.Controls.Add(this.setStopTriggerButton);
            this.groupBox1.Controls.Add(this.setStartTriggerButton);
            this.groupBox1.Controls.Add(this.getTriggers);
            this.groupBox1.Controls.Add(this.stopTrigger);
            this.groupBox1.Controls.Add(this.startTrigger);
            this.groupBox1.Location = new System.Drawing.Point(19, 87);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(313, 86);
            this.groupBox1.TabIndex = 8;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Triggers";
            //
            // setStopTriggerButton
            //
            this.setStopTriggerButton.Location = new System.Drawing.Point(210, 56);
            this.setStopTriggerButton.Name = "setStopTriggerButton";
            this.setStopTriggerButton.Size = new System.Drawing.Size(75, 21);
            this.setStopTriggerButton.TabIndex = 2;
            this.setStopTriggerButton.Text = "Set";
            this.setStopTriggerButton.UseVisualStyleBackColor = true;
            this.setStopTriggerButton.Click += new System.EventHandler(this.setStopTriggerButton_Click);
            //
            // setStartTriggerButton
            //
            this.setStartTriggerButton.Location = new System.Drawing.Point(210, 25);
            this.setStartTriggerButton.Name = "setStartTriggerButton";
            this.setStartTriggerButton.Size = new System.Drawing.Size(75, 21);
            this.setStartTriggerButton.TabIndex = 2;
            this.setStartTriggerButton.Text = "Set";
            this.setStartTriggerButton.UseVisualStyleBackColor = true;
            this.setStartTriggerButton.Click += new System.EventHandler(this.setStartTriggerButton_Click);
            //
            // getTriggers
            //
            this.getTriggers.Location = new System.Drawing.Point(111, 25);
            this.getTriggers.Name = "getTriggers";
            this.getTriggers.Size = new System.Drawing.Size(77, 21);
            this.getTriggers.TabIndex = 1;
            this.getTriggers.Text = "Get Triggers";
            this.getTriggers.UseVisualStyleBackColor = true;
            this.getTriggers.Click += new System.EventHandler(this.getTriggers_Click);
            //
            // stopTrigger
            //
            this.stopTrigger.AutoSize = true;
            this.stopTrigger.Location = new System.Drawing.Point(21, 59);
            this.stopTrigger.Name = "stopTrigger";
            this.stopTrigger.Size = new System.Drawing.Size(87, 16);
            this.stopTrigger.TabIndex = 0;
            this.stopTrigger.Text = "Stop Trigger";
            this.stopTrigger.UseVisualStyleBackColor = true;
            //
            // startTrigger
            //
            this.startTrigger.AutoSize = true;
            this.startTrigger.Location = new System.Drawing.Point(21, 28);
            this.startTrigger.Name = "startTrigger";
            this.startTrigger.Size = new System.Drawing.Size(89, 16);
            this.startTrigger.TabIndex = 0;
            this.startTrigger.Text = "Start Trigger";
            this.startTrigger.UseVisualStyleBackColor = true;
            //
            // startButton
            //
            this.startButton.Location = new System.Drawing.Point(19, 179);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(75, 21);
            this.startButton.TabIndex = 9;
            this.startButton.Text = "Start (&S)";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            //
            // stopButton
            //
            this.stopButton.Enabled = false;
            this.stopButton.Location = new System.Drawing.Point(117, 179);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(75, 21);
            this.stopButton.TabIndex = 10;
            this.stopButton.Text = "Stop (&T)";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            //
            // emgDataDisplay
            //
            this.emgDataDisplay.Location = new System.Drawing.Point(62, 3);
            this.emgDataDisplay.Name = "emgDataDisplay";
            this.emgDataDisplay.ReadOnly = true;
            this.emgDataDisplay.Size = new System.Drawing.Size(164, 19);
            this.emgDataDisplay.TabIndex = 11;
            //
            // timer1
            //
            this.timer1.Interval = 8;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            //
            // sensorNumber
            //
            this.sensorNumber.Location = new System.Drawing.Point(315, 184);
            this.sensorNumber.Maximum = new decimal(new int[] {
            16,
            0,
            0,
            0});
            this.sensorNumber.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.sensorNumber.Name = "sensorNumber";
            this.sensorNumber.Size = new System.Drawing.Size(47, 19);
            this.sensorNumber.TabIndex = 12;
            this.sensorNumber.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            //
            // label4
            //
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(229, 188);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(83, 12);
            this.label4.TabIndex = 13;
            this.label4.Text = "Sensor Number";
            //
            // label5
            //
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 6);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(31, 12);
            this.label5.TabIndex = 14;
            this.label5.Text = "EMG:";
            //
            // label6
            //
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 31);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(42, 12);
            this.label6.TabIndex = 15;
            this.label6.Text = "ACC X:";
            //
            // label7
            //
            this.label7.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 56);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(42, 12);
            this.label7.TabIndex = 15;
            this.label7.Text = "ACC Y:";
            //
            // label8
            //
            this.label8.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 81);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 12);
            this.label8.TabIndex = 15;
            this.label8.Text = "ACC Z:";
            //
            // accXDisplay
            //
            this.accXDisplay.Location = new System.Drawing.Point(62, 28);
            this.accXDisplay.Name = "accXDisplay";
            this.accXDisplay.ReadOnly = true;
            this.accXDisplay.Size = new System.Drawing.Size(164, 19);
            this.accXDisplay.TabIndex = 11;
            //
            // accYDisplay
            //
            this.accYDisplay.Location = new System.Drawing.Point(62, 53);
            this.accYDisplay.Name = "accYDisplay";
            this.accYDisplay.ReadOnly = true;
            this.accYDisplay.Size = new System.Drawing.Size(164, 19);
            this.accYDisplay.TabIndex = 11;
            //
            // accZDisplay
            //
            this.accZDisplay.Location = new System.Drawing.Point(62, 78);
            this.accZDisplay.Name = "accZDisplay";
            this.accZDisplay.ReadOnly = true;
            this.accZDisplay.Size = new System.Drawing.Size(164, 19);
            this.accZDisplay.TabIndex = 11;
            //
            // gxDisplay
            //
            this.gxDisplay.Location = new System.Drawing.Point(62, 103);
            this.gxDisplay.Name = "gxDisplay";
            this.gxDisplay.ReadOnly = true;
            this.gxDisplay.Size = new System.Drawing.Size(164, 19);
            this.gxDisplay.TabIndex = 16;
            //
            // gyDisplay
            //
            this.gyDisplay.Location = new System.Drawing.Point(62, 128);
            this.gyDisplay.Name = "gyDisplay";
            this.gyDisplay.ReadOnly = true;
            this.gyDisplay.Size = new System.Drawing.Size(164, 19);
            this.gyDisplay.TabIndex = 17;
            //
            // gzDisplay
            //
            this.gzDisplay.Location = new System.Drawing.Point(62, 153);
            this.gzDisplay.Name = "gzDisplay";
            this.gzDisplay.ReadOnly = true;
            this.gzDisplay.Size = new System.Drawing.Size(164, 19);
            this.gzDisplay.TabIndex = 18;
            //
            // label9
            //
            this.label9.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(5, 106);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(49, 12);
            this.label9.TabIndex = 22;
            this.label9.Text = "GYRO X:";
            //
            // label10
            //
            this.label10.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(5, 131);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(49, 12);
            this.label10.TabIndex = 23;
            this.label10.Text = "GYRO Y:";
            //
            // label11
            //
            this.label11.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(5, 156);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(49, 12);
            this.label11.TabIndex = 24;
            this.label11.Text = "GYRO Z:";
            //
            // label12
            //
            this.label12.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(8, 233);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(43, 12);
            this.label12.TabIndex = 30;
            this.label12.Text = "MAG Z:";
            //
            // label13
            //
            this.label13.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(8, 206);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(43, 12);
            this.label13.TabIndex = 29;
            this.label13.Text = "MAG Y:";
            //
            // label14
            //
            this.label14.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(8, 181);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(43, 12);
            this.label14.TabIndex = 28;
            this.label14.Text = "MAG X:";
            //
            // mzDisplay
            //
            this.mzDisplay.Location = new System.Drawing.Point(62, 228);
            this.mzDisplay.Name = "mzDisplay";
            this.mzDisplay.ReadOnly = true;
            this.mzDisplay.Size = new System.Drawing.Size(164, 19);
            this.mzDisplay.TabIndex = 27;
            //
            // myDisplay
            //
            this.myDisplay.Location = new System.Drawing.Point(62, 203);
            this.myDisplay.Name = "myDisplay";
            this.myDisplay.ReadOnly = true;
            this.myDisplay.Size = new System.Drawing.Size(164, 19);
            this.myDisplay.TabIndex = 26;
            //
            // mxDisplay
            //
            this.mxDisplay.Location = new System.Drawing.Point(62, 178);
            this.mxDisplay.Name = "mxDisplay";
            this.mxDisplay.ReadOnly = true;
            this.mxDisplay.Size = new System.Drawing.Size(164, 19);
            this.mxDisplay.TabIndex = 25;
            //
            // tableLayoutPanel1
            //
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 75F));
            this.tableLayoutPanel1.Controls.Add(this.label5, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.mzDisplay, 1, 9);
            this.tableLayoutPanel1.Controls.Add(this.label12, 0, 9);
            this.tableLayoutPanel1.Controls.Add(this.myDisplay, 1, 8);
            this.tableLayoutPanel1.Controls.Add(this.label6, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.mxDisplay, 1, 7);
            this.tableLayoutPanel1.Controls.Add(this.label13, 0, 8);
            this.tableLayoutPanel1.Controls.Add(this.label7, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.label14, 0, 7);
            this.tableLayoutPanel1.Controls.Add(this.label8, 0, 3);
            this.tableLayoutPanel1.Controls.Add(this.gzDisplay, 1, 6);
            this.tableLayoutPanel1.Controls.Add(this.label9, 0, 4);
            this.tableLayoutPanel1.Controls.Add(this.gyDisplay, 1, 5);
            this.tableLayoutPanel1.Controls.Add(this.label10, 0, 5);
            this.tableLayoutPanel1.Controls.Add(this.gxDisplay, 1, 4);
            this.tableLayoutPanel1.Controls.Add(this.label11, 0, 6);
            this.tableLayoutPanel1.Controls.Add(this.emgDataDisplay, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.accXDisplay, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.accZDisplay, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.accYDisplay, 1, 2);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(19, 205);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 10;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 10F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(236, 253);
            this.tableLayoutPanel1.TabIndex = 31;
            //
            // tb_FilePath
            //
            this.tb_FilePath.Location = new System.Drawing.Point(85, 38);
            this.tb_FilePath.Name = "tb_FilePath";
            this.tb_FilePath.Size = new System.Drawing.Size(321, 19);
            this.tb_FilePath.TabIndex = 32;
            //
            // label15
            //
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(49, 42);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(30, 12);
            this.label15.TabIndex = 33;
            this.label15.Text = "Path:";
            //
            // _lslNameLabel
            //
            this._lslNameLabel.AutoSize = true;
            this._lslNameLabel.Location = new System.Drawing.Point(20, 66);
            this._lslNameLabel.Name = "_lslNameLabel";
            this._lslNameLabel.Size = new System.Drawing.Size(59, 12);
            this._lslNameLabel.TabIndex = 35;
            this._lslNameLabel.Text = "LSL Name:";
            //
            // MainForm
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(432, 519);
            this.Controls.Add(this._lslNameLabel);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.tb_FilePath);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.sensorNumber);
            this.Controls.Add(this.stopButton);
            this.Controls.Add(this.startButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.quitButton);
            this.Controls.Add(this.responseLine);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.commandLine);
            this.Controls.Add(this.connectButton);
            this.Controls.Add(this.serverURL);
            this.Controls.Add(this.label1);
            this.Name = "MainForm";
            this.Text = "App-Delsys";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.sensorNumber)).EndInit();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox serverURL;
        private System.Windows.Forms.Button connectButton;
        private System.Windows.Forms.TextBox commandLine;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox responseLine;
        private System.Windows.Forms.Button quitButton;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button getTriggers;
        private System.Windows.Forms.CheckBox startTrigger;
        private System.Windows.Forms.Button setStartTriggerButton;
        private System.Windows.Forms.Button setStopTriggerButton;
        private System.Windows.Forms.CheckBox stopTrigger;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.TextBox emgDataDisplay;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.NumericUpDown sensorNumber;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox accXDisplay;
        private System.Windows.Forms.TextBox accYDisplay;
        private System.Windows.Forms.TextBox accZDisplay;
        private System.Windows.Forms.TextBox gxDisplay;
        private System.Windows.Forms.TextBox gyDisplay;
        private System.Windows.Forms.TextBox gzDisplay;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox mzDisplay;
        private System.Windows.Forms.TextBox myDisplay;
        private System.Windows.Forms.TextBox mxDisplay;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.TextBox tb_FilePath;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label _lslNameLabel;
    }
}

