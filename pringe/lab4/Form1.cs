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
    public partial class Form1 : Form
    {
        public int task = 1;
        public int[,] arr;
        public Form1()
        {
            InitializeComponent();
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void arrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 f2;
            f2 = new Form2();
            f2.Show();
            f2.f1 = this;
            ArrayInit.Enabled = false;
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AboutBox1 abt;
            abt = new AboutBox1();
            abt.Show();
            //abt.ShowDialog();
        }

        private void calculateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form3 f3;
            f3 = new Form3();
            f3.Show();
            f3.f1 = this;
            TaskInit.Enabled = false;
        }

        private void AnswerInit_Click(object sender, EventArgs e)
        {
            Form4 f4;
            f4 = new Form4(this);
            f4.Show();
            AnswerInit.Enabled = false;
        }
    }
}
