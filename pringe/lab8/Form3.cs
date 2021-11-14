using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab8
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        public Form1 f1;
        int cur = 0;

        public void Init()
        {
            f1.FromListToDT(ref f1.lst, dataGridView1, cur);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            cur--;
            button2.Enabled = true;
            if (cur <= 0)
                button1.Enabled = false;
            if (cur < 0)
                cur = 0;
            Init();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            cur++;
            button1.Enabled = true;
            if (cur >= f1.lst.Count - 1)
                button2.Enabled = false;
            if (cur > f1.lst.Count - 1)
                cur = f1.lst.Count - 1;
            Init();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            f1.FromDTToList(ref f1.lst, dataGridView1, cur);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            f1.lst.RemoveAt(cur);
            if (f1.lst.Count == 1)
            {
                button3.Enabled = false;
                button1.Enabled = false;
                button2.Enabled = false;
            }
            if (cur == f1.lst.Count)
            {
                button1_Click(sender, e);
                button2.Enabled = false;
            }
            else if (cur == 0)
            {
                Init();
                button1.Enabled = false;
            }
            else
            {
                Init();
                if (cur == f1.lst.Count-1)
                    button2.Enabled = false;
            }
        }
    }
}
