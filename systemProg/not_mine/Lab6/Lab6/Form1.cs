using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab6
{ 
    public partial class Form1 : Form
    {
        private Bitmap redBitmap = (Bitmap)Image.FromFile("red.bmp");
        private Bitmap greenBitmap = (Bitmap)Image.FromFile("green.bmp");

        private bool t1 = false;
        private bool t2 = false;
        private bool t3 = false;

        private List<Button> listButtons = new List<Button>();

        private bool firstPlayerStep = true;
        private bool start = true;
        private int[,] mas;
        private int steps;

        public Form1()
        {
            InitializeComponent();
            listButtons.Add(taskButton1);
            listButtons.Add(taskButton2);
            listButtons.Add(taskButton3);
            listButtons.Add(clearButton);
        }

        private void taskButton1_Click(object sender, EventArgs e)
        {
            t1 = true;
            t2 = false;
            t3 = false;
            label3.Text = "";
            Refresh();
            DrawEmblem(listButtons[0]);
        }

        private void taskButton2_Click(object sender, EventArgs e)
        {
            t1 = false;
            t2 = true;
            t3 = false;
            label3.Text = "";
            Refresh();
        }

        private void taskButton3_Click(object sender, EventArgs e)
        {
            t1 = false;
            t2 = false;
            t3 = true;
            start = true;
            firstPlayerStep = true;
            mas = new int[5, 5];
            steps = 0;
            label3.Text = "First player step";
            Refresh();
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            t1 = false;
            t2 = false;
            t3 = false;
            label3.Text = "";
            Refresh();
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {
            if (t2)
            {
                DrawFlag(e.Graphics);
            }
            if (t3)
            {
                Graphics graphics = e.Graphics;
                Pen blackPen = new Pen(Color.Black, 1);
                e.Graphics.FillRectangle(Brushes.White, new Rectangle(1, 1, 505, 505));
                for (int i = 0; i < 6; ++i)
                {
                    graphics.DrawLine(blackPen, 100 * i + i, 0, 100 * i + i, 504);
                    graphics.DrawLine(blackPen, 0, 100 * i + i, 504, 100 * i + i);
                }
            }
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            if (t1)
            {
                foreach (Button button in listButtons)
                    DrawEmblem(button);
            }
        }

        private void DrawEmblem(Button button)
        {
            Graphics e = Graphics.FromHwnd(button.Handle);
            e.DrawEllipse(new Pen(Color.Black, 3), 5, 5, 20, 20);
            e.FillRectangle(new SolidBrush(Color.Blue), 10, 10, 5, 5);
            e.FillRectangle(new SolidBrush(Color.Red), 10, 15, 5, 5);
            e.FillRectangle(new SolidBrush(Color.Green), 15, 10, 5, 5);
            e.FillRectangle(new SolidBrush(Color.Yellow), 15, 15, 5, 5);
        }

        private void DrawFlag(Graphics graphics)
        {
            graphics.DrawRectangle(new Pen(Color.Black, 1), new Rectangle(0, 0, 310, 190));

            graphics.DrawEllipse(new Pen(Color.Blue, 3), new Rectangle(40, 40, 70, 70));
            graphics.DrawEllipse(new Pen(Color.Yellow, 3), new Rectangle(80, 80, 70, 70));
            graphics.DrawEllipse(new Pen(Color.Black, 3), new Rectangle(120, 40, 70, 70));
            graphics.DrawEllipse(new Pen(Color.Green, 3), new Rectangle(160, 80, 70, 70));
            graphics.DrawEllipse(new Pen(Color.Red, 3), new Rectangle(200, 40, 70, 70));

            graphics.DrawLine(new Pen(Color.Blue, 3), 40 + 70, 40 + 38, 40 + 70, 40 + 50);
            graphics.DrawLine(new Pen(Color.Black, 3), 40 + 150, 40 + 38, 40 + 150, 40 + 50);

            graphics.DrawLine(new Pen(Color.Green, 3), 40 + 158, 40 + 40, 40 + 166, 40 + 40);
            graphics.DrawLine(new Pen(Color.Yellow, 3), 40 + 158 - 82, 40 + 40, 40 + 166 - 82, 40 + 40);
        }

        private void pictureBox1_MouseClick(object sender, MouseEventArgs e)
        {
            if (t3 && start)
            {
                int xPos = e.X / 101;
                int yPos = e.Y / 101;

                if (mas[yPos, xPos] != 0)
                    return;
                steps++;

                Graphics graphics = pictureBox1.CreateGraphics();
                if (firstPlayerStep)
                {
                    //graphics.FillRectangle(new TextureBrush(greenBitmap), new Rectangle(xPos * 101 + 1, yPos * 101 + 1, 100, 100));

                    LinearGradientBrush greenGradientBrush = new LinearGradientBrush(new Point(xPos * 100, yPos * 100), new Point((xPos + 1) * 100, (yPos + 1) * 100),
                                        Color.FromArgb(255, 0, 255, 0), Color.FromArgb(0, 0, 100, 0));
                    graphics.FillRectangle(greenGradientBrush, new Rectangle(xPos * 101 + 1, yPos * 101 + 1, 100, 100));

                    mas[yPos, xPos] = 1;
                    label3.Text = "Second player step";
                }
                else
                {
                    //graphics.FillRectangle(new TextureBrush(redBitmap), new Rectangle(xPos * 101 + 1, yPos * 101 + 1, 100, 100));

                    LinearGradientBrush redGradientBrush = new LinearGradientBrush(new Point(xPos * 100, yPos * 100), new Point((xPos + 1) * 100, (yPos + 1) * 100),
                                                            Color.FromArgb(255, 255, 0, 0), Color.FromArgb(0, 0, 100, 0));
                    graphics.FillRectangle(redGradientBrush, new Rectangle(xPos * 101 + 1, yPos * 101 + 1, 100, 100));

                    mas[yPos, xPos] = 2;
                    label3.Text = "First player step";
                }

                string str = getWinner();
                if (str != "")
                {
                    start = false;
                    label3.Text = str;
                }

                firstPlayerStep = !firstPlayerStep;
            }
        }
        private string getWinner()
        {
            for (int i = 0; i < 5; ++i)
                for (int j = 0; j < 2; ++j)
                    if (mas[i, j] > 0)
                    {
                        for (int k = j + 1; k < 5; ++k)
                        {
                            if (mas[i, k] != mas[i, j])
                                break;
                            else
                            if (k - j == 3)
                                if (mas[i, j] == 1)
                                    return "First player win";
                                else
                                    return "Second player win";
                        }
                    }
            for (int i = 0; i < 2; ++i)
                for (int j = 0; j < 5; ++j)
                    if (mas[i, j] > 0)
                    {
                        for (int k = i + 1; k < 5; ++k)
                        {
                            if (mas[k, j] != mas[i, j])
                                break;
                            else
                            if (k - i == 3)
                                if (mas[i, j] == 1)
                                    return "First player win";
                                else
                                    return "Second player win";
                        }
                    }

            if(steps >= 25)
            {
                return "The game is over, nobody won";
            }
            return "";
        }
    }
}
