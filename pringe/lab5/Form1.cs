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
    public partial class Form1 : Form
    {
        public int task = 1;
        public int[,] arr;
        public Form1()
        {
            InitializeComponent();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void arrayToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 f2;
            f2 = new Form2();
            f2.MdiParent = this;
            f2.Show();
        }

        private void TaskInit_Click(object sender, EventArgs e)
        {
            Form3 f3;
            f3 = new Form3();
            f3.MdiParent = this;
            f3.Show();
        }

        private void AnswerInit_Click(object sender, EventArgs e)
        {
            Form4 f4;
            f4 = new Form4(this);
            f4.MdiParent = this;
            f4.Show();
        }

        private void tileHorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileHorizontal);
        }

        private void tileVertToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.TileVertical);
        }

        private void cascadeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.LayoutMdi(MdiLayout.Cascade);
        }

        private void closeCurrentToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (ActiveMdiChild != null)
                ActiveMdiChild.Close();
        }

        private void closeAllToolStripMenuItem_Click(object sender, EventArgs e)
        {
            foreach (Form el in MdiChildren)
            {
                el.Close();
            }
        }
    }
}
