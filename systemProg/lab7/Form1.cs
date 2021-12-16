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
        private int img_num = 0, i = 0, j = 18, w = 660, h = 440;
        private Bitmap map1 = new Bitmap("china1.bmp");
        private Bitmap map2 = new Bitmap("china2.bmp");
        private Bitmap map3 = new Bitmap("china3.bmp");
        private string str = "China wall";
        Graphics pic;

        public Form1()
        {
            InitializeComponent();
            FormLoad();
            button1_Click(null, null);
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            ShowImage();
        }

        public void FormLoad()
        {
            pic = pictureBox1.CreateGraphics();
            ShowImage();
        }

        private void ShowImage()
        {
            Bitmap map;
            bool txt = false;
            switch (img_num)
            {
                case 1:
                    map = map2;
                    txt = false;
                    break;
                case 2:
                    map = map3;
                    txt = false;
                    break;
                default:
                    map = map1;
                    txt = true;
                    break;
            }
            pic.DrawImage(map, j , 0, i, h);
            if (txt && i == w)
            {
                Font aFont = new Font("Cambira", 15, FontStyle.Bold);
                pic.DrawString(str, aFont, Brushes.White, 5, 400);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            j = 0;
            for (i = 0; i <= w; i += 30)
            {
                ShowImage();
            }
            img_num++;
            img_num = img_num % 3;
            i = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
                for (i = 0; i <= w; i += 30)
                {
                    j = 660-i;
                    ShowImage();
                }
                img_num--;
                img_num = img_num < 0 ? 2 : img_num;
                i = 0;
        }
    }
}
