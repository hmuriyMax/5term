using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab4
{
    public partial class Form2 : Form
    {
        private int rows = 3, cols = 3;
        public Form1 f1;
        public Form2()
        {
            InitializeComponent();
            dataGridView1.RowCount = 3;
            dataGridView1.ColumnCount = 3;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                rows = Convert.ToInt32(textBox1.Text);
            }
            catch
            {
                rows = 3;
                textBox1.Text = "3";
            }
            try
            {
                cols = Convert.ToInt32(textBox2.Text);
            }
            catch
            {
                cols = 3;
                textBox2.Text = "3";
            }
            dataGridView1.RowCount = rows;
            dataGridView1.ColumnCount = cols;
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            f1.ArrayInit.Enabled = true;
            f1.AnswerInit.Enabled = true;
            f1.TaskInit.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            f1.arr = new int[rows, cols];
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    try
                    {
                        f1.arr[i, j] = Convert.ToInt32(dataGridView1.Rows[i].Cells[j].Value);
                    }
                    catch
                    {
                        f1.arr[i, j] = 0;
                        dataGridView1.Rows[i].Cells[j].Value = "0";
                    }
                }
            }
            Close();
        }
    }
}
