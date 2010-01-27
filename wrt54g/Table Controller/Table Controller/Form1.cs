using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Table_Controller
{
    public partial class Form1 : Form
    {
        private Panel[,] virtualDisp = new Panel[3,3];
        public Form1()
        {
            InitializeComponent();
            virtualDisp[0, 0] = panel1;
            virtualDisp[0, 1] = panel2;
            virtualDisp[0, 2] = panel3;
            virtualDisp[1, 0] = panel4;
            virtualDisp[1, 1] = panel5;
            virtualDisp[1, 2] = panel6;
            virtualDisp[2, 0] = panel7;
            virtualDisp[2, 1] = panel8;
            virtualDisp[2, 2] = panel9;
        }

        private void panel10_Paint(object sender, PaintEventArgs e)
        {
            fgSampleColor.BackColor = Color.FromArgb(redSlider.Value * 255 / 15, greenSlider.Value * 255 / 15, blueSlider.Value * 255 / 15);
        }

        private void Slider_ValueChanged(object sender, EventArgs e)
        {
            fgSampleColor.BackColor = Color.FromArgb(redSlider.Value, greenSlider.Value, blueSlider.Value);
        }

        private void panel_Click(object sender, EventArgs e)
        {
            if(sender.Equals(panel1))
                panel1.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel2))
                panel2.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel3))
                panel3.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel4))
                panel4.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel5))
                panel5.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel6))
                panel6.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel7))
                panel7.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel8))
                panel8.BackColor = fgSampleColor.BackColor;
            else if(sender.Equals(panel9))
                panel9.BackColor = fgSampleColor.BackColor;
        }

        private void btnAddFrame_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                int red = colorDialog1.Color.R / 255 * 15;
                int green = colorDialog1.Color.G / 255 * 15;
                int blue = colorDialog1.Color.B / 255 * 15;
                redSlider.Value = red;
                greenSlider.Value = green;
                blueSlider.Value = blue;

                //fgSampleColor.BackColor = Color.FromArgb(red / 15 * 255, green / 15 * 255, blue / 15 * 255);
                fgSampleColor.BackColor = colorDialog1.Color;
            }
        }
    }
}