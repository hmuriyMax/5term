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
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }

        public Form1 f1;
        
        public void Init()
        {
            int max = 0;
            foreach (row el in f1.lst)
                if (el.num_studs > max)
                    max = el.num_studs;

            List<row> tmp = new List<row>();
            foreach (row el in f1.lst)
                if (el.num_studs == max)
                    tmp.Add(el);

            f1.FromListToDT(ref tmp, dataGridView1);
        }
    }
}
