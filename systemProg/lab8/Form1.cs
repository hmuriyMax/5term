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

namespace lab8
{
    public partial class Form1 : Form
    {
        Thread thr1;
        Thread thr2;
        Thread thr3;
        private int[] truenums = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        private int[] nums1;
        private int[] nums2;
        Graphics pic1, pic2, pic3;
        int NUM = 3;
        int WID = 300;
        static Random random;
        private Stopwatch tm1, tm2, tm3;

        public Form1()
        {
            InitializeComponent();
            random = new Random();
            pic1 = pictureBox1.CreateGraphics();
            pic2 = pictureBox2.CreateGraphics();
            pic3 = pictureBox3.CreateGraphics();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Thread mainThread = Thread.CurrentThread;
            richTextBox1.Text = "Имя домена: " + Thread.GetDomain().FriendlyName +
                                 "\nУровень приоритета: " + mainThread.Priority +
                                 "\nСостояние потока: " + mainThread.ThreadState +
                                 "\nПоток запущен? " + (mainThread.IsAlive);
        }

        static int[] RandomPermutation(int[] a)
        {
            int[] res = (int[])(a.Clone());
            var n = a.Length;
            while (n > 1)
            {
                n--;
                var i = random.Next(n + 1);
                var temp = res[i];
                res[i] = res[n];
                res[n] = temp;
            }

            return res;
        }

        private void ShowImage(Graphics pic, int[] nums, Bitmap[] maps)
        {
            int twid = WID / NUM;
            for (int i = 0; i < NUM; i++)
                for (int j = 0; j < NUM; j++)
                {
                    int index = j * NUM + i;
                    pic.DrawImage(maps[nums[index]], i*twid, j*twid, twid, twid);
                }
            Thread.Sleep(300);
        }

        private Bitmap[] CompileImg(int num, Graphics pic, int[] nums)
        {
            Bitmap[] maps = new Bitmap[NUM * NUM];
            for (int i = 0; i < NUM*NUM; i++)
            {
                maps[i] = new Bitmap("bitmap" + (num + i) + ".bmp");
            }

            ShowImage(pic, nums, maps);
            return maps;
        }

        private void SortImg(Bitmap[] maps, Graphics pic, int[] nums)
        {
            for (int i = 0; i < NUM * NUM; i++)
                for (int j = i; j < NUM * NUM; j++)
                    if (nums[j] < nums[i])
                    {
                        int tmp = nums[i];
                        nums[i] = nums[j];
                        nums[j] = tmp;
                        ShowImage(pic, nums, maps);
                    }
        }

        private void CompileImg1()
        {
            tm1.Start();
            SortImg(CompileImg(0, pic1, nums1), pic1, nums1);
            tm1.Stop();
        }

        private void CompileImg2()
        {
            tm2.Start();
            SortImg(CompileImg(NUM*NUM, pic2, nums2), pic2, nums2);
            tm2.Stop();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            tm1 = new Stopwatch();
            tm2 = new Stopwatch();
            tm3 = new Stopwatch();

            nums1 = RandomPermutation(truenums);
            nums2 = RandomPermutation(truenums);

            thr1 = new Thread(CompileImg1);
            thr2 = new Thread(CompileImg2);
            thr3 = new Thread(SystemInfo);

            thr1.Start();
            thr2.Start();
            thr3.Start();

            thr1.Join();
            thr2.Join();
            thr3.Join();

            string str = "";
            TimeSpan ts;

            ts = tm1.Elapsed;
            str += String.Format("Thread 1: {0:00}:{1:000}\n", 
                ts.Seconds, ts.Milliseconds);

            ts = tm2.Elapsed;
            str += String.Format("Thread 2: {0:00}:{1:000}\n",
                ts.Seconds, ts.Milliseconds);

            ts = tm3.Elapsed;
            str += String.Format("Thread 3: {0:00}:{1:000}\n",
                ts.Seconds, ts.Milliseconds);

            richTextBox1.Text = str;
        }

        private string GetSystemInfo()
        {
            
            var output = new StringBuilder();
            output.AppendFormat("Версия Windows: {0}\n", Environment.OSVersion);
            output.AppendFormat("64 Bit? : {0}\n", Environment.Is64BitOperatingSystem);
            output.AppendFormat("Имя компьютера: {0}\n", Environment.MachineName);
            output.AppendFormat("Число процессоров: {0}\n", Environment.ProcessorCount);
            output.AppendFormat("Системная папка : {0}\n", Environment.SystemDirectory);
            output.AppendFormat("Текущая директория: {0}\n", Environment.CurrentDirectory);
            output.AppendFormat("Коммандная строка: {0}\n", Environment.CommandLine);
            output.AppendFormat("Текущий поток: {0}\n", Environment.CurrentManagedThreadId);
            output.AppendFormat("ID процесса: {0}\n", Environment.ProcessId);
            output.AppendFormat("Логические диски : {0}\n", 
                string.Join(", ", Environment.GetLogicalDrives()));
            return output.ToString();
        }

        private void DrawString(string str)
        {
            var font = new Font("Times New Roman", 11);
            pic3.Clear(Color.White);
            pic3.DrawString(str, font, Brushes.Black, 10, 10);
        }

        private void SystemInfo()
        {
            tm3.Start();
            thr1.Join();
            thr2.Join();
            DrawString(GetSystemInfo());
            tm3.Stop();
        }

    }
}
