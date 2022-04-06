namespace App_TobiiSpec
{
    partial class CalibrationForm
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
            this._mainPicturebox = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this._mainPicturebox)).BeginInit();
            this.SuspendLayout();
            //
            // _mainPicturebox
            //
            this._mainPicturebox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
            | System.Windows.Forms.AnchorStyles.Left)
            | System.Windows.Forms.AnchorStyles.Right)));
            this._mainPicturebox.Location = new System.Drawing.Point(0, 0);
            this._mainPicturebox.Name = "_mainPicturebox";
            this._mainPicturebox.Size = new System.Drawing.Size(800, 451);
            this._mainPicturebox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this._mainPicturebox.TabIndex = 0;
            this._mainPicturebox.TabStop = false;
            //
            // CalibrationForm
            //
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this._mainPicturebox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "CalibrationForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "CalibrationForm";
            this.Load += new System.EventHandler(this.CalibrationForm_Load);
            this.Shown += new System.EventHandler(this.CalibrationForm_Shown);
            ((System.ComponentModel.ISupportInitialize)(this._mainPicturebox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox _mainPicturebox;
    }
}
