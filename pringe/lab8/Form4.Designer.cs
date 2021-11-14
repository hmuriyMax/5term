
namespace lab8
{
    partial class Form4
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.uni_name = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.num_crs = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.num_stds = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowUserToAddRows = false;
            this.dataGridView1.AllowUserToDeleteRows = false;
            this.dataGridView1.AllowUserToResizeColumns = false;
            this.dataGridView1.AllowUserToResizeRows = false;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.uni_name,
            this.num_crs,
            this.num_stds});
            this.dataGridView1.Location = new System.Drawing.Point(2, 3);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowHeadersVisible = false;
            this.dataGridView1.RowHeadersWidth = 51;
            this.dataGridView1.RowTemplate.Height = 29;
            this.dataGridView1.Size = new System.Drawing.Size(553, 418);
            this.dataGridView1.TabIndex = 2;
            // 
            // uni_name
            // 
            this.uni_name.HeaderText = "University Name";
            this.uni_name.MinimumWidth = 6;
            this.uni_name.Name = "uni_name";
            this.uni_name.Width = 250;
            // 
            // num_crs
            // 
            this.num_crs.HeaderText = "Num of courses";
            this.num_crs.MinimumWidth = 6;
            this.num_crs.Name = "num_crs";
            this.num_crs.Width = 150;
            // 
            // num_stds
            // 
            this.num_stds.HeaderText = "Num of students";
            this.num_stds.MinimumWidth = 6;
            this.num_stds.Name = "num_stds";
            this.num_stds.Width = 150;
            // 
            // Form4
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(555, 418);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form4";
            this.Text = "Task";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.DataGridViewTextBoxColumn uni_name;
        private System.Windows.Forms.DataGridViewTextBoxColumn num_crs;
        private System.Windows.Forms.DataGridViewTextBoxColumn num_stds;
    }
}