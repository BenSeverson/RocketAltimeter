using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace Table_Controller
{
    public partial class TableColorPicker : UserControl
    {
        private Rectangle[] colors = new Rectangle[4096];
        public TableColorPicker()
        {
            InitializeComponent();
        }

        private void TableColorPicker_Paint(object sender, PaintEventArgs e)
        {
            //for(int row=0;row<128;row++)
            //    for (int col = 0; col < 32; col++)
            //    {
            //        colors[row*32+col] = drawColorBox(e.Graphics,22*col,22*row,
            //    }
        }
        //private Rectangle drawColorBox(Graphics g, int x, int y, Color c)
        //{
        //}
    }
}
