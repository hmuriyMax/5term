using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace lab8
{
    public partial class Form2 : Form
    {
        public Form1 f1;
        public Form2()
        {
            InitializeComponent();
        }

        private List<row> ImportFile(string filename = "import.csv")
        {
            List<row> res = new List<row>();
            using (StreamReader sr = new StreamReader(filename))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    row p = new row();
                    string[] parts = line.Split(';');
                    p.name = parts[0];
                    p.num_napr = Convert.ToInt32(parts[1]);
                    p.num_studs = Convert.ToInt32(parts[2]);
                    res.Add(p);
                }
            }
            return res;
        }
        public void Init()
        {
            {/*row tmp;
            tmp = new row { name = "MPEI", num_napr = 56, num_studs = 1500 };
            f1.lst.Add(tmp);
            tmp = new row { name = "Bauman", num_napr = 148, num_studs = 5500 };
            f1.lst.Add(tmp);
            tmp = new row { name = "MSU", num_napr = 206, num_studs = 10004 };
            f1.lst.Add(tmp);
            tmp = new row { name = "HSE", num_napr = 51, num_studs = 1408 };
            f1.lst.Add(tmp);
            tmp = new row { name = "MIPT", num_napr = 100, num_studs = 3800 };
            f1.lst.Add(tmp);*/
            }

            f1.lst = ImportFile();
            f1.FromListToDT(ref f1.lst, dataGridView1);

            {/*dataGridView1.RowCount = 5;
            dataGridView1.Rows[0].Cells[0].Value = "MPEI";
            dataGridView1.Rows[0].Cells[1].Value = "56";
            dataGridView1.Rows[0].Cells[2].Value = "1500";

            dataGridView1.Rows[1].Cells[0].Value = "Bauman";
            dataGridView1.Rows[1].Cells[1].Value = "148";
            dataGridView1.Rows[1].Cells[2].Value = "5500";

            dataGridView1.Rows[2].Cells[0].Value = "MSU";
            dataGridView1.Rows[2].Cells[1].Value = "206";
            dataGridView1.Rows[2].Cells[2].Value = "10004";

            dataGridView1.Rows[3].Cells[0].Value = "HSE";
            dataGridView1.Rows[3].Cells[1].Value = "51";
            dataGridView1.Rows[3].Cells[2].Value = "1408";

            dataGridView1.Rows[4].Cells[0].Value = "MIPT";
            dataGridView1.Rows[4].Cells[1].Value = "100";
            dataGridView1.Rows[4].Cells[2].Value = "3800";*/
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (Convert.ToBoolean(f1.lst.Count))
            {
                f1.FromDTToList(ref f1.lst, dataGridView1);
                f1.editToolStripMenuItem.Enabled = true;
                f1.resultToolStripMenuItem.Enabled = true;
                Close();
            }
        }
    }
}
