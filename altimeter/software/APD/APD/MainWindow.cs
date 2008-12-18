using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ZedGraph;

namespace APD
{
    
    public partial class MainWindow : Form
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void buttonConnect_Click(object sender, EventArgs e)
        {
            statusLabelConnected.Text = "Connecting to Altimeter...";
            //connectProgressBar.Value = 0;
            //connectProgressBar.Visible = true;

            Constants.AltBoardUSB status = AltUSB.DetectPICkit2Device(0);
            //connectProgressBar.Value = 50;
            if (status == Constants.AltBoardUSB.found)
            {
                //string[] newLines = new String[textStatus.Lines.Length+2];
                textStatus.Text += "Found Altimeter..." + Environment.NewLine;
                //connectProgressBar.Value = 75;
                textStatus.Text += "Firmware version: " + AltUSB.FirmwareVersion + Environment.NewLine;
                //connectProgressBar.Value = 100;
                statusLabelConnected.Text = "Altimeter Connected";
            }
            else
            {
                textStatus.Text += "Error connecting to Altimeter" + Environment.NewLine;
                textStatus.Text += "Error: " + status.ToString() + Environment.NewLine;
                statusLabelConnected.Text = "Error Connecting";
            }
            //connectProgressBar.Visible = false;
            //AltUSB.DisconnectPICkit2Unit();            
        }

        private void MainWindow_Load(object sender, EventArgs e)
        {
            CreateGraph(altitudeGraph);
        }

        private void buttonReadByte_Click(object sender, EventArgs e)
        {
            byte eeprom = AltUSB.ReadEEByte(ushort.Parse(textEEAddress.Text), byte.Parse(textEEBlock.Text));
            textStatus.Text += "EEPROM: " + Convert.ToString((int)eeprom, 16).ToUpper() + Environment.NewLine;
        }

        private void buttonDumpEE_Click(object sender, EventArgs e)
        {
            byte[] result;
            result = AltUSB.ReadEE(ushort.Parse(textEEAddress.Text), byte.Parse(textEEBlock.Text), byte.Parse(textEELength.Text));
            textStatus.Text += "EEPROM Block: ";
            foreach(byte byteVal in result)
                textStatus.Text += Convert.ToString((int)byteVal, 16).ToUpper() + " ";
            textStatus.Text += Environment.NewLine;
        }

        private void textStatus_TextChanged(object sender, EventArgs e)
        {
            textStatus.SelectionStart = textStatus.Text.Length;
            textStatus.ScrollToCaret();
        }

        private void checkBoxBuzzer_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxBuzzer.Checked)
                AltUSB.ControlBuzzer(true);
            else
                AltUSB.ControlBuzzer(false);
        }

        private void MainWindow_Resize(object sender, EventArgs e)
        {
            SetSize();
        }

        private void SetSize()
        {
            
        }

        private void CreateGraph(ZedGraphControl zgc)
        {
            // get a reference to the GraphPane

            GraphPane myPane = zgc.GraphPane;

            // Set the Titles

            myPane.Title.Text = "Altitude";
            myPane.XAxis.Title.Text = "Time (s)";
            myPane.YAxis.Title.Text = "Altitude (ft)";
            myPane.Chart.Fill = new Fill(Color.White, Color.LightGray, 45.0f);

            // Make up some data arrays based on the Sine function

            double x, y1, y2;
            PointPairList list1 = new PointPairList();
            PointPairList list2 = new PointPairList();
            for (int i = 0; i < 36; i++)
            {
                x = (double)i + 5;
                y1 = 1.5 + Math.Sin((double)i * 0.2);
                y2 = 3.0 * (1.5 + Math.Sin((double)i * 0.2));
                list1.Add(x, y1);
                list2.Add(x, y2);
            }

            // Generate a red curve with diamond

            // symbols, and "Porsche" in the legend

            LineItem myCurve = myPane.AddCurve("Porsche",
                  list1, Color.Red, SymbolType.Diamond);

            // Generate a blue curve with circle

            // symbols, and "Piper" in the legend

            LineItem myCurve2 = myPane.AddCurve("Piper",
                  list2, Color.Blue, SymbolType.Circle);

            // Tell ZedGraph to refigure the

            // axes since the data have changed

            zgc.AxisChange();
        }

        private void buttonDownload_Click(object sender, EventArgs e)
        {

        }

        private void downloadEEPROM()
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            EEPROM x = new EEPROM();
            byte[] b = new byte[1024 * 2 + 10];

            b[0] = 1;
            
            b[1] = Convert.ToByte('A');
            b[2] = Convert.ToByte('P');
            b[3] = Convert.ToByte('D');
            
            b[4] = 20;
            b[5] = 0;

            b[6] = 0;
            b[7] = 4;

            for (UInt16 i = 0; i < 1024; i++)
            {
                b[i * 2 + 8] = BitConverter.GetBytes(i)[0];
                b[i * 2 + 8 + 1] = BitConverter.GetBytes(i)[1];
            }

            x.parseEEPROM(b);
            richTextBox1.Text = x.testContents();
        }

    }
}
