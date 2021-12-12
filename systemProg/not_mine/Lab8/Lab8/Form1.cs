using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab8
{
    public partial class Form1 : Form
    {
        bool DrawImage = false;
        List<Bitmap> image1Parts = new List<Bitmap>();
        List<Bitmap> image2Parts = new List<Bitmap>();

        List<int> truePermutation = new List<int>() { 0, 1, 2, 3 };
        List<int> permutation1 = new List<int>();
        List<int> permutation2 = new List<int>();

        string info;

        Graphics picBox1Graphics;
        Graphics picBox2Graphics;

        Thread thread1;
        Thread thread2;
        Thread thread3;

        Stopwatch watchThread1 = new Stopwatch();
        Stopwatch watchThread2 = new Stopwatch();
        Stopwatch watchThread3 = new Stopwatch();

        private void Main()
        {
            Thread mainThread = Thread.CurrentThread;
            mainThreadInfo.Text = "Имя домена: " + Thread.GetDomain().FriendlyName + "\nИдентификатор контекста: " +
                Thread.CurrentContext.ContextID + "\nЗапущен ли поток? " +
                mainThread.IsAlive.ToString() + "\nУровень приоритета: " + mainThread.Priority.ToString() + "\nСостояние потока: " +
                mainThread.ThreadState.ToString() + "\n";

            thread1 = new Thread(new ThreadStart(GenerateAndDrawFirstPermutation));
            thread2 = new Thread(new ThreadStart(GenerateAndDrawSecondPermutation));
            thread3 = new Thread(new ThreadStart(outputInfoAboutSystem));
            
            watchThread1.Start();
            thread1.Start();
            watchThread2.Start();
            thread2.Start();
            watchThread3.Start();
            thread3.Start();

            thread3.Join();
            watchThread3.Stop();
            TimeSpan ts1 = watchThread1.Elapsed;
            TimeSpan ts2 = watchThread2.Elapsed;
            TimeSpan ts3 = watchThread3.Elapsed;
            string threadsTime;
            threadsTime = String.Format("Thread1: {0:00}s.{1:000}ms\n", ts1.Seconds, ts1.Milliseconds);
            threadsTime += String.Format("Thread2: {0:00}s.{1:000}ms\n", ts2.Seconds, ts2.Milliseconds);
            threadsTime += String.Format("Thread3: {0:00}s.{1:000}ms\n", ts3.Seconds, ts3.Milliseconds);
            timeInfo.Text = threadsTime;
        }

        private void LoadPartImages()
        {
            for (int i = 1; i <= 4; i++)
            {
                image1Parts.Add(new Bitmap("image1\\" + i.ToString() + ".bmp"));
                image2Parts.Add(new Bitmap("image2\\" + i.ToString() + ".bmp"));
            }
        }

        public Form1()
        {
            InitializeComponent();
            LoadPartImages();
            picBox1Graphics = pictureBox1.CreateGraphics();
            picBox2Graphics = pictureBox2.CreateGraphics();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DrawImage = !DrawImage;
            if (DrawImage)
                Main();
            else
            {
                permutation1.Clear();
                permutation2.Clear();
                mainThreadInfo.Text = "";
                timeInfo.Text = "";
                Refresh();
            }
        }

        void DrawImageByPermutation(Graphics graphics, List<Bitmap> image, List<int> ind)
        {
            int width = image[0].Width;
            int height = image[0].Height;

            graphics.DrawImage(image[ind[0]], new Point(0, 0));
            graphics.DrawImage(image[ind[1]], new Point(width, 0));
            graphics.DrawImage(image[ind[2]], new Point(0, height));
            graphics.DrawImage(image[ind[3]], new Point(width, height));

        }

        private void MakePermutation(ref List<int> ind)
        {
            Random rnd = new Random();
            for (int i = ind.Count - 1; i >= 0; i--)
            {
                int j = rnd.Next(i + 1);
                int tmp = ind[i];
                ind[i] = ind[j];
                ind[j] = tmp;
            }

        }

        private void GenerateAndDrawFirstPermutation()
        {
            permutation1.AddRange(truePermutation);
            MakePermutation(ref permutation1);
            while (!permutation1.SequenceEqual(truePermutation))
            {
                MakePermutation(ref permutation1);
                DrawImageByPermutation(picBox1Graphics, image1Parts, permutation1);
                Thread.Sleep(50);

            }
        }

        private void GenerateAndDrawSecondPermutation()
        {
            permutation2.AddRange(truePermutation);
            MakePermutation(ref permutation2);
            while (!permutation2.SequenceEqual(truePermutation))
            {
                MakePermutation(ref permutation2);
                DrawImageByPermutation(picBox2Graphics, image2Parts, permutation2);
                Thread.Sleep(100);

            }
        }

        private string CollectInfoAboutSystem()
        {

            StringBuilder output = new StringBuilder();
            output.AppendFormat("Версия Windows: {0}\n", Environment.OSVersion);
            output.AppendFormat("64 Bit операционная система? : {0}\n", Environment.Is64BitOperatingSystem ? "Yes" : "No");
            output.AppendFormat("Имя компьютера: {0}\n", Environment.MachineName);
            output.AppendFormat("Число процессоров: {0}\n", Environment.ProcessorCount);
            output.AppendFormat("Системная папка : {0}\n", Environment.SystemDirectory);
            output.AppendFormat("Текущая директория: {0}\n", Environment.CurrentDirectory);
            output.AppendFormat("UserDomainName: {0}\n", Environment.UserDomainName);
            output.AppendFormat("UserInteractive: {0}\n", Environment.UserInteractive);
            output.AppendFormat("WorkingSet: {0}\n", Environment.WorkingSet);
            output.AppendFormat("Логические диски : {0}\n",
                  String.Join(", ", Environment.GetLogicalDrives())
               .Replace("\\", String.Empty));

            return output.ToString();
        }

        private void outputInfoAboutSystem()
        {
            string info = CollectInfoAboutSystem();

            thread1.Join();
            watchThread1.Stop();
            thread2.Join();
            watchThread2.Stop();

            MakePresentation(info);
        }

        private void MakePresentation(string info)
        {
            Graphics graphicWnd = this.CreateGraphics();
            Font font = new Font("Times New Roman", 11, FontStyle.Bold);
            graphicWnd.Clear(Color.White);
            graphicWnd.DrawString(info, font, Brushes.Black, 10, 580);
        }
    }
}
