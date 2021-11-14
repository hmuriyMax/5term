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
    public struct row
    {
        public string name;
        public int num_napr;
        public int num_studs;
    }
    public partial class Form1 : Form
    {
    public Form1()
        {
            InitializeComponent();
        }
        public List<row> lst = new List<row>();

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void inputToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 f2;
            f2 = new Form2();
            f2.Show();
            f2.f1 = this;
            f2.Init();
        }

        private void editToolStripMenuItem_Click(object sender, EventArgs e)
        { 
            Form3 f3;
            f3 = new Form3();
            f3.Show();
            f3.f1 = this;
            f3.Init();
        }
        public void FromListToDT(ref List<row> lst, DataGridView dt, int num = -1) {
            Action<row, int> setter = (el, i) => {
                dt.Rows[i].Cells[0].Value = el.name;
                dt.Rows[i].Cells[1].Value = el.num_napr;
                dt.Rows[i].Cells[2].Value = el.num_studs;
            };
            if (num >= 0) {
                try {
                    dt.RowCount = 1;
                    row el = lst[num];
                    setter(el, 0);
                }
                catch{}
            } else {
                dt.RowCount = Convert.ToBoolean(lst.Count)? lst.Count: 1;
                int i = 0;
                foreach (row el in lst)
                {
                    setter(el, i);
                    i++;
                }
            }
        }

        public void FromDTToList(ref List<row> lst, DataGridView dt, int num = -1) {
            Func<int, row> getter = (i) => new row {
                name = Convert.ToString(dt.Rows[i].Cells[0].Value),
                num_napr = Convert.ToInt32(dt.Rows[i].Cells[1].Value),
                num_studs = Convert.ToInt32(dt.Rows[i].Cells[2].Value)
            };
            if (num >= 0) {
                try {
                    dt.RowCount = 1;
                    lst.RemoveAt(num);
                    row tmp = getter(0);
                    lst.Insert(num, tmp);
                }
                catch {}
            }
            else {
                lst = new List<row>();
                int size = dt.RowCount;
                for (int i = 0; i< size; i++) {
                    if (dt.Rows[i].Cells[0].Value == null || dt.Rows[i].Cells[1].Value == null || dt.Rows[i].Cells[2].Value == null)
                        continue;
                    row el = getter(i);
                    lst.Add(el);
                }
            }
        }

        private void resultToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form4 f4;
            f4 = new Form4();
            f4.Show();
            f4.f1 = this;
            f4.Init();
        }
    }
}
