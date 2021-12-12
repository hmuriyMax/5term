using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab7_CSharp
{
    public partial class Form1 : Form
    {
        private bool startButtonPushed = false;
        private bool showStart = false;

        private Bitmap bm1 = new Bitmap("Orange.bmp");
        private Bitmap bm2 = new Bitmap("Apple.bmp");
        private Bitmap bm3 = new Bitmap("Pineapple.bmp");

        private Font aFont = new Font("Times New Roman", 18, FontStyle.Bold);

        public Form1()
        {
            InitializeComponent();
            this.Width = 900;
            this.Height = 700;
            button1.Text = "Start";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (!startButtonPushed)
            {
                button1.Text = "Pause";
                startButtonPushed = true;
            }
            else
            {
                button1.Text = "Start";
                startButtonPushed = false;
            }

        }
        void pause()
        {
            while (!startButtonPushed) ;
            return;
        }

        void showPresentation()
        {
            if (!showStart)
            {
                showStart = true;
                Graphics dc = pictureBox1.CreateGraphics();
                Graphics dcf = this.CreateGraphics();

                drawBitmap(bm1, dc, dcf, "Апельсин");
                if (!startButtonPushed) pause();
                Thread.Sleep(1500);

                if (!startButtonPushed) pause();
                drawBitmap(bm2, dc, dcf, "Яблоко");
                if (!startButtonPushed) pause();
                Thread.Sleep(1500);

                if (!startButtonPushed) pause();
                drawBitmap(bm3, dc, dcf, "Ананас");
                if (!startButtonPushed) pause();
                Thread.Sleep(1500);

                if (!startButtonPushed) pause();
                showStart = false;
                if (!startButtonPushed) pause();
            }
        }

        private void drawBitmap(Bitmap bitmap, Graphics paintBoxDC, Graphics formDC, String label)
        {
            paintBoxDC.Clear(Color.White);
            formDC.Clear(Color.White);

            if (!startButtonPushed) pause();

            for (int i = 10; i > 0; --i)
            {
                paintBoxDC.DrawImage(bitmap, 0, 0, 500 / i, 400 / i);
                Thread.Sleep(50);
            }

            formDC.DrawString(label, aFont, Brushes.Black, 320, 475);
        }


        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Thread thread = new Thread(new ThreadStart(showPresentation));
            thread.Start();
        }

        private void pictureBox1_Click_1(object sender, EventArgs e)
        {
            button1_Click(sender, e);
        }
    }
}
