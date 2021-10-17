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
    public partial class Form3 : Form
    {
        public Form1 f1;
        public Form3()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            f1 = (Form1)this.MdiParent;
            f1.task = radioButton1.Checked ? 1 : 2;
            Close();
        }
    }
}
