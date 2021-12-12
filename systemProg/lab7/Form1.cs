using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab7
{
    public partial class Form1 : Form
    {
        private int num = 0, i = 0, j = 18;
        private bool show = false, showText = false;
        private Bitmap[] btms = new Bitmap[4];
        private string[] strs = new string[4];
        Graphics pic;
        public Form1()
        {
            InitializeComponent();
    }

        private void button3_Click(object sender, EventArgs e)
        {
            pic = pictureBox1.CreateGraphics();
            btms[0] = new Bitmap("IMG_0615.bmp");
            btms[1] = new Bitmap("IMG_0667.bmp");
            btms[2] = new Bitmap("IMG_0741.bmp");
            btms[3] = new Bitmap("IMG_0777.bmp");
            strs[0] = "The Devil";
            strs[1] = "Nasty darkness";
            strs[2] = "Perovo at night";
            strs[3] = "Fitness";
            show = true;
            showText = true;
            button3.Enabled = false;
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (show)
                ShowImage();
            if (showText)
                ShowText();
        }

        private void ShowImage()
        {
            pic.DrawImage(btms[num-1 < 0 ? 3 : num-1], -660 + i, 0, 660, 440);
            pic.DrawImage(btms[num], 0 + i, 0, 660, 440);
            pic.DrawImage(btms[(num+1) % 4], 660 + i, 0, 660, 440);
        }

        private void ShowText()
        {
            Font aFont = new Font("Cambira", j + 1, FontStyle.Bold);
            pic.DrawString(strs[num], aFont, Brushes.White, 5, 400);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (show)
            {
                showText = false;
                for (i = 0; i >= -660; i -= 30)
                {
                    ShowImage();
                }
                num++;
                num = num % 4;
                i = 0;
                ShowImage();
                showText = true;
                for (j = 0; j <= 17; j+=2)
                {
                    ShowImage();
                    ShowText();
                    System.Threading.Thread.Sleep(30);
                }
                ShowImage(); 
                ShowText();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (show)
            {
                showText = false;
                for (i = 0; i <= 660; i += 30)
                {
                    ShowImage();
                }
                num--;
                num = num < 0 ? 3 : num;
                i = 0;
                ShowImage();
                showText = true;
                for (j = 0; j <= 17; j++)
                {
                    ShowText();
                    System.Threading.Thread.Sleep(15);
                }
                ShowImage();
                ShowText();
            }
        }
    }
}
