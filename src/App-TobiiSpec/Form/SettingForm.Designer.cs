namespace App_TobiiSpec
{
    partial class SettingForm
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
            this._tobiiGroupbox = new System.Windows.Forms.GroupBox();
            this._tobiiSamplingRateCombobox = new System.Windows.Forms.ComboBox();
            this._tobiiSamplingRateLabel = new System.Windows.Forms.Label();
            this._lslGroupbox = new System.Windows.Forms.GroupBox();
            this._lslSnedRateLabel = new System.Windows.Forms.Label();
            this._lslSnedRateUnitLabel = new System.Windows.Forms.Label();
            this._lslSendRateNumeric = new System.Windows.Forms.NumericUpDown();
            this._okButton = new System.Windows.Forms.Button();
            this._cancelButton = new System.Windows.Forms.Button();
            this._tobiiGroupbox.SuspendLayout();
            this._lslGroupbox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._lslSendRateNumeric)).BeginInit();
            this.SuspendLayout();
            //
            // _tobiiGroupbox
            //
            this._tobiiGroupbox.Controls.Add(this._tobiiSamplingRateCombobox);
            this._tobiiGroupbox.Controls.Add(this._tobiiSamplingRateLabel);
            this._tobiiGroupbox.Location = new System.Drawing.Point(12, 12);
            this._tobiiGroupbox.Name = "_tobiiGroupbox";
            this._tobiiGroupbox.Size = new System.Drawing.Size(271, 54);
            this._tobiiGroupbox.TabIndex = 0;
            this._tobiiGroupbox.TabStop = false;
            this._tobiiGroupbox.Text = "Tobii Settings";
            //
            // _tobiiSamplingRateCombobox
            //
            this._tobiiSamplingRateCombobox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this._tobiiSamplingRateCombobox.FormattingEnabled = true;
            this._tobiiSamplingRateCombobox.Location = new System.Drawing.Point(132, 18);
            this._tobiiSamplingRateCombobox.Name = "_tobiiSamplingRateCombobox";
            this._tobiiSamplingRateCombobox.Size = new System.Drawing.Size(121, 20);
            this._tobiiSamplingRateCombobox.TabIndex = 1;
            //
            // _tobiiSamplingRateLabel
            //
            this._tobiiSamplingRateLabel.AutoSize = true;
            this._tobiiSamplingRateLabel.Location = new System.Drawing.Point(18, 23);
            this._tobiiSamplingRateLabel.Name = "_tobiiSamplingRateLabel";
            this._tobiiSamplingRateLabel.Size = new System.Drawing.Size(108, 12);
            this._tobiiSamplingRateLabel.TabIndex = 0;
            this._tobiiSamplingRateLabel.Text = "Sampling Rate (&S)";
            //
            // _lslGroupbox
            //
            this._lslGroupbox.Controls.Add(this._lslSnedRateLabel);
            this._lslGroupbox.Controls.Add(this._lslSnedRateUnitLabel);
            this._lslGroupbox.Controls.Add(this._lslSendRateNumeric);
            this._lslGroupbox.Location = new System.Drawing.Point(12, 72);
            this._lslGroupbox.Name = "_lslGroupbox";
            this._lslGroupbox.Size = new System.Drawing.Size(271, 54);
            this._lslGroupbox.TabIndex = 1;
            this._lslGroupbox.TabStop = false;
            this._lslGroupbox.Text = "LSL";
            this._lslGroupbox.Enter += new System.EventHandler(this._lslGroupbox_Enter);
            //
            // _lslSnedRateLabel
            //
            this._lslSnedRateLabel.AutoSize = true;
            this._lslSnedRateLabel.Location = new System.Drawing.Point(18, 21);
            this._lslSnedRateLabel.Name = "_lslSnedRateLabel";
            this._lslSnedRateLabel.Size = new System.Drawing.Size(68, 12);
            this._lslSnedRateLabel.TabIndex = 2;
            this._lslSnedRateLabel.Text = "Transmission Interval (&I)";
            //
            // _lslSnedRateUnitLabel
            //
            this._lslSnedRateUnitLabel.AutoSize = true;
            this._lslSnedRateUnitLabel.Location = new System.Drawing.Point(233, 21);
            this._lslSnedRateUnitLabel.Name = "_lslSnedRateUnitLabel";
            this._lslSnedRateUnitLabel.Size = new System.Drawing.Size(20, 12);
            this._lslSnedRateUnitLabel.TabIndex = 1;
            this._lslSnedRateUnitLabel.Text = "ms";
            //
            // _lslSendRateNumeric
            //
            this._lslSendRateNumeric.Location = new System.Drawing.Point(132, 19);
            this._lslSendRateNumeric.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this._lslSendRateNumeric.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this._lslSendRateNumeric.Name = "_lslSendRateNumeric";
            this._lslSendRateNumeric.Size = new System.Drawing.Size(95, 19);
            this._lslSendRateNumeric.TabIndex = 0;
            this._lslSendRateNumeric.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            //
            // _okButton
            //
            this._okButton.Location = new System.Drawing.Point(109, 132);
            this._okButton.Name = "_okButton";
            this._okButton.Size = new System.Drawing.Size(75, 23);
            this._okButton.TabIndex = 2;
            this._okButton.Text = "OK";
            this._okButton.UseVisualStyleBackColor = true;
            this._okButton.Click += new System.EventHandler(this._okButton_Click);
            //
            // _cancelButton
            //
            this._cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this._cancelButton.Location = new System.Drawing.Point(190, 132);
            this._cancelButton.Name = "_cancelButton";
            this._cancelButton.Size = new System.Drawing.Size(75, 23);
            this._cancelButton.TabIndex = 3;
            this._cancelButton.Text = "Cancel";
            this._cancelButton.UseVisualStyleBackColor = true;
            this._cancelButton.Click += new System.EventHandler(this._cancelButton_Click);
            //
            // SettingForm
            //
            this.AcceptButton = this._okButton;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this._cancelButton;
            this.ClientSize = new System.Drawing.Size(297, 172);
            this.Controls.Add(this._cancelButton);
            this.Controls.Add(this._okButton);
            this.Controls.Add(this._lslGroupbox);
            this.Controls.Add(this._tobiiGroupbox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingForm";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Settings";
            this.Load += new System.EventHandler(this.SettingForm_Load);
            this._tobiiGroupbox.ResumeLayout(false);
            this._tobiiGroupbox.PerformLayout();
            this._lslGroupbox.ResumeLayout(false);
            this._lslGroupbox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._lslSendRateNumeric)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox _tobiiGroupbox;
        private System.Windows.Forms.ComboBox _tobiiSamplingRateCombobox;
        private System.Windows.Forms.Label _tobiiSamplingRateLabel;
        private System.Windows.Forms.GroupBox _lslGroupbox;
        private System.Windows.Forms.Label _lslSnedRateUnitLabel;
        private System.Windows.Forms.NumericUpDown _lslSendRateNumeric;
        private System.Windows.Forms.Label _lslSnedRateLabel;
        private System.Windows.Forms.Button _okButton;
        private System.Windows.Forms.Button _cancelButton;
    }
}
