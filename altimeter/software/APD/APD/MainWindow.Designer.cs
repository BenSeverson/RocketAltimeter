namespace APD
{
    partial class MainWindow
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
            this.buttonConnect = new System.Windows.Forms.Button();
            this.textStatus = new System.Windows.Forms.TextBox();
            this.buttonReadByte = new System.Windows.Forms.Button();
            this.buttonDumpEE = new System.Windows.Forms.Button();
            this.textEEBlock = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.textEEAddress = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.textEELength = new System.Windows.Forms.TextBox();
            this.checkBoxBuzzer = new System.Windows.Forms.CheckBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.DataTab = new System.Windows.Forms.TabPage();
            this.buttonDownload = new System.Windows.Forms.Button();
            this.altitudeGraph = new ZedGraph.ZedGraphControl();
            this.FlightTab = new System.Windows.Forms.TabPage();
            this.DiagTab = new System.Windows.Forms.TabPage();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.connectProgressBar = new System.Windows.Forms.ToolStripProgressBar();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.statusLabelConnected = new System.Windows.Forms.ToolStripStatusLabel();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.tabControl1.SuspendLayout();
            this.DataTab.SuspendLayout();
            this.DiagTab.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonConnect
            // 
            this.buttonConnect.Location = new System.Drawing.Point(389, 32);
            this.buttonConnect.Name = "buttonConnect";
            this.buttonConnect.Size = new System.Drawing.Size(105, 23);
            this.buttonConnect.TabIndex = 0;
            this.buttonConnect.Text = "Connect";
            this.buttonConnect.UseVisualStyleBackColor = true;
            this.buttonConnect.Click += new System.EventHandler(this.buttonConnect_Click);
            // 
            // textStatus
            // 
            this.textStatus.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.textStatus.Location = new System.Drawing.Point(6, 32);
            this.textStatus.Multiline = true;
            this.textStatus.Name = "textStatus";
            this.textStatus.ReadOnly = true;
            this.textStatus.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textStatus.Size = new System.Drawing.Size(375, 172);
            this.textStatus.TabIndex = 1;
            this.textStatus.TextChanged += new System.EventHandler(this.textStatus_TextChanged);
            // 
            // buttonReadByte
            // 
            this.buttonReadByte.Location = new System.Drawing.Point(389, 61);
            this.buttonReadByte.Name = "buttonReadByte";
            this.buttonReadByte.Size = new System.Drawing.Size(105, 23);
            this.buttonReadByte.TabIndex = 2;
            this.buttonReadByte.Text = "Read Byte";
            this.buttonReadByte.UseVisualStyleBackColor = true;
            this.buttonReadByte.Click += new System.EventHandler(this.buttonReadByte_Click);
            // 
            // buttonDumpEE
            // 
            this.buttonDumpEE.Location = new System.Drawing.Point(389, 90);
            this.buttonDumpEE.Name = "buttonDumpEE";
            this.buttonDumpEE.Size = new System.Drawing.Size(105, 23);
            this.buttonDumpEE.TabIndex = 3;
            this.buttonDumpEE.Text = "Dump EEPROM";
            this.buttonDumpEE.UseVisualStyleBackColor = true;
            this.buttonDumpEE.Click += new System.EventHandler(this.buttonDumpEE_Click);
            // 
            // textEEBlock
            // 
            this.textEEBlock.Location = new System.Drawing.Point(49, 6);
            this.textEEBlock.MaxLength = 1;
            this.textEEBlock.Name = "textEEBlock";
            this.textEEBlock.Size = new System.Drawing.Size(24, 20);
            this.textEEBlock.TabIndex = 4;
            this.textEEBlock.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 13);
            this.label1.TabIndex = 5;
            this.label1.Text = "Block";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(79, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(45, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "Address";
            // 
            // textEEAddress
            // 
            this.textEEAddress.Location = new System.Drawing.Point(130, 6);
            this.textEEAddress.Name = "textEEAddress";
            this.textEEAddress.Size = new System.Drawing.Size(66, 20);
            this.textEEAddress.TabIndex = 7;
            this.textEEAddress.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(202, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Length";
            // 
            // textEELength
            // 
            this.textEELength.Location = new System.Drawing.Point(248, 6);
            this.textEELength.Name = "textEELength";
            this.textEELength.Size = new System.Drawing.Size(37, 20);
            this.textEELength.TabIndex = 9;
            this.textEELength.Text = "1";
            // 
            // checkBoxBuzzer
            // 
            this.checkBoxBuzzer.AutoSize = true;
            this.checkBoxBuzzer.Location = new System.Drawing.Point(389, 187);
            this.checkBoxBuzzer.Name = "checkBoxBuzzer";
            this.checkBoxBuzzer.Size = new System.Drawing.Size(75, 17);
            this.checkBoxBuzzer.TabIndex = 10;
            this.checkBoxBuzzer.Text = "Buzzer On";
            this.checkBoxBuzzer.UseVisualStyleBackColor = true;
            this.checkBoxBuzzer.CheckedChanged += new System.EventHandler(this.checkBoxBuzzer_CheckedChanged);
            // 
            // tabControl1
            // 
            this.tabControl1.Appearance = System.Windows.Forms.TabAppearance.FlatButtons;
            this.tabControl1.Controls.Add(this.DataTab);
            this.tabControl1.Controls.Add(this.FlightTab);
            this.tabControl1.Controls.Add(this.DiagTab);
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Top;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(684, 502);
            this.tabControl1.TabIndex = 11;
            // 
            // DataTab
            // 
            this.DataTab.Controls.Add(this.buttonDownload);
            this.DataTab.Controls.Add(this.altitudeGraph);
            this.DataTab.Location = new System.Drawing.Point(4, 25);
            this.DataTab.Name = "DataTab";
            this.DataTab.Padding = new System.Windows.Forms.Padding(3);
            this.DataTab.Size = new System.Drawing.Size(676, 473);
            this.DataTab.TabIndex = 1;
            this.DataTab.Text = "Data";
            this.DataTab.UseVisualStyleBackColor = true;
            // 
            // buttonDownload
            // 
            this.buttonDownload.Location = new System.Drawing.Point(530, 6);
            this.buttonDownload.Name = "buttonDownload";
            this.buttonDownload.Size = new System.Drawing.Size(140, 23);
            this.buttonDownload.TabIndex = 1;
            this.buttonDownload.Text = "Download Flight Data";
            this.buttonDownload.UseVisualStyleBackColor = true;
            this.buttonDownload.Click += new System.EventHandler(this.buttonDownload_Click);
            // 
            // altitudeGraph
            // 
            this.altitudeGraph.EditButtons = System.Windows.Forms.MouseButtons.None;
            this.altitudeGraph.EditModifierKeys = System.Windows.Forms.Keys.None;
            this.altitudeGraph.IsShowCopyMessage = false;
            this.altitudeGraph.Location = new System.Drawing.Point(6, 6);
            this.altitudeGraph.Name = "altitudeGraph";
            this.altitudeGraph.ScrollGrace = 0;
            this.altitudeGraph.ScrollMaxX = 0;
            this.altitudeGraph.ScrollMaxY = 0;
            this.altitudeGraph.ScrollMaxY2 = 0;
            this.altitudeGraph.ScrollMinX = 0;
            this.altitudeGraph.ScrollMinY = 0;
            this.altitudeGraph.ScrollMinY2 = 0;
            this.altitudeGraph.Size = new System.Drawing.Size(518, 461);
            this.altitudeGraph.TabIndex = 0;
            // 
            // FlightTab
            // 
            this.FlightTab.Location = new System.Drawing.Point(4, 25);
            this.FlightTab.Name = "FlightTab";
            this.FlightTab.Padding = new System.Windows.Forms.Padding(3);
            this.FlightTab.Size = new System.Drawing.Size(676, 473);
            this.FlightTab.TabIndex = 2;
            this.FlightTab.Text = "Flight Settings";
            this.FlightTab.UseVisualStyleBackColor = true;
            // 
            // DiagTab
            // 
            this.DiagTab.Controls.Add(this.textStatus);
            this.DiagTab.Controls.Add(this.checkBoxBuzzer);
            this.DiagTab.Controls.Add(this.label1);
            this.DiagTab.Controls.Add(this.buttonDumpEE);
            this.DiagTab.Controls.Add(this.textEELength);
            this.DiagTab.Controls.Add(this.buttonReadByte);
            this.DiagTab.Controls.Add(this.textEEBlock);
            this.DiagTab.Controls.Add(this.buttonConnect);
            this.DiagTab.Controls.Add(this.label3);
            this.DiagTab.Controls.Add(this.label2);
            this.DiagTab.Controls.Add(this.textEEAddress);
            this.DiagTab.Location = new System.Drawing.Point(4, 25);
            this.DiagTab.Name = "DiagTab";
            this.DiagTab.Padding = new System.Windows.Forms.Padding(3);
            this.DiagTab.Size = new System.Drawing.Size(676, 473);
            this.DiagTab.TabIndex = 0;
            this.DiagTab.Text = "Diagnostics";
            this.DiagTab.UseVisualStyleBackColor = true;
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.connectProgressBar,
            this.toolStripStatusLabel3,
            this.statusLabelConnected});
            this.statusStrip1.Location = new System.Drawing.Point(0, 505);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(684, 22);
            this.statusStrip1.TabIndex = 12;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(109, 17);
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // connectProgressBar
            // 
            this.connectProgressBar.Name = "connectProgressBar";
            this.connectProgressBar.Size = new System.Drawing.Size(100, 16);
            this.connectProgressBar.Visible = false;
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(481, 17);
            this.toolStripStatusLabel3.Spring = true;
            // 
            // statusLabelConnected
            // 
            this.statusLabelConnected.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.statusLabelConnected.Name = "statusLabelConnected";
            this.statusLabelConnected.Size = new System.Drawing.Size(79, 17);
            this.statusLabelConnected.Text = "Not Connected";
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.richTextBox1);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(676, 473);
            this.tabPage1.TabIndex = 3;
            this.tabPage1.Text = "tabPage1";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(0, 0);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(543, 467);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = "";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(564, 18);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 1;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 527);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "MainWindow";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "APD - Altimeter Programmer & Downloader";
            this.Load += new System.EventHandler(this.MainWindow_Load);
            this.Resize += new System.EventHandler(this.MainWindow_Resize);
            this.tabControl1.ResumeLayout(false);
            this.DataTab.ResumeLayout(false);
            this.DiagTab.ResumeLayout(false);
            this.DiagTab.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.tabPage1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonConnect;
        private System.Windows.Forms.TextBox textStatus;
        private System.Windows.Forms.Button buttonReadByte;
        private System.Windows.Forms.Button buttonDumpEE;
        private System.Windows.Forms.TextBox textEEBlock;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textEEAddress;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textEELength;
        private System.Windows.Forms.CheckBox checkBoxBuzzer;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage DiagTab;
        private System.Windows.Forms.TabPage DataTab;
        private System.Windows.Forms.TabPage FlightTab;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripProgressBar connectProgressBar;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripStatusLabel statusLabelConnected;
        private ZedGraph.ZedGraphControl altitudeGraph;
        private System.Windows.Forms.Button buttonDownload;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Button button1;
    }
}

