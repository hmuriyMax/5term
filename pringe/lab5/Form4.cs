using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab5
{
    public partial class Form4 : Form
    {
        public Form1 f1;
        public Form4(Form1 fp1)
        {
            InitializeComponent();
            string ans;
            f1 = fp1;
            if (f1.task == 1)
                ans = tsk1(f1.arr);
            else
                ans = tsk2(f1.arr);
            label1.Text = ans;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }

        private bool IsPrst(int num)
        {
            if (num < 2)
                return false;
            for (int i = 2; i < num / 2; i++)
            {
                if (num % i == 0)
                    return false;
            }
            return true;
        }
        private string tsk1(int[,] arr)
        {
            int rows = arr.GetLength(0);
            int cols = arr.GetLength(1);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (IsPrst(arr[i, j]))
                        return "ДА";
                }
            }
            return "НЕТ";
        }

        private string tsk2(int[,] arr)
        {
            int rows = arr.GetLength(0);
            int cols = arr.GetLength(1);
            int sum = 0;
            int num = 0;
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols - i - 1; j++)
                {
                    sum += arr[i, j];
                    num++;
                }
            }
            return String.Format("{.f4}", sum / num);
        }
    }
}
