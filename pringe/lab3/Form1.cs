using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        double sum;

        private void button1_Click(object sender, EventArgs e)
        {
            int rows, cols;
            try{
                rows = Convert.ToInt32(textBox1.Text);
            }
            catch{
                rows = 3;
                textBox1.Text = "3";
            }
            try{
                cols = Convert.ToInt32(textBox2.Text);
            }
            catch{
                cols = 3;
                textBox2.Text = "3";
            }
            dataGridView1.RowCount = rows;
            dataGridView1.ColumnCount = cols;

        }

        private double Lab1Swapper(double[,] arr)
        {
            double sum = 0;
            for (int j = 0; j < arr.GetLength(1); j++)
            {
                int n = 0, m = 0;
                double maxClmn = arr[0, j];
                for (int i = 0; i < arr.GetLength(0); i++)
                {
                    if (Math.Abs(arr[i, j]) > Math.Abs(maxClmn))
                    {
                        maxClmn = arr[i, j];
                        n = i;
                        m = j;
                    }
                }
                arr[n, m] = arr[0, j];
                arr[0, j] = maxClmn;

                sum += maxClmn;
            }
            return sum;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            int rows = Convert.ToInt32(textBox1.Text);
            int cols = Convert.ToInt32(textBox2.Text);

            double[,] arr = new double[rows, cols];

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    try {
                        arr[i, j] = Convert.ToDouble(dataGridView1.Rows[i].Cells[j].Value);
                    }
                    catch {
                        arr[i, j] = 0.0;
                        dataGridView1.Rows[i].Cells[j].Value = "0";
                    }
                }
            }
            sum = Lab1Swapper(arr);
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    dataGridView1.Rows[i].Cells[j].Value = Convert.ToString(arr[i, j]);
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            label7.Text = Convert.ToString(sum / dataGridView1.ColumnCount);
        }
    }
}
