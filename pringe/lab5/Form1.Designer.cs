
namespace lab5
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.windowsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ArrayInit = new System.Windows.Forms.ToolStripMenuItem();
            this.TaskInit = new System.Windows.Forms.ToolStripMenuItem();
            this.AnswerInit = new System.Windows.Forms.ToolStripMenuItem();
            this.positionsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileHorToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tileVertToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cascadeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeCurrentToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.windowsToolStripMenuItem,
            this.positionsToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(800, 28);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(46, 24);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(116, 26);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // windowsToolStripMenuItem
            // 
            this.windowsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ArrayInit,
            this.TaskInit,
            this.AnswerInit});
            this.windowsToolStripMenuItem.Name = "windowsToolStripMenuItem";
            this.windowsToolStripMenuItem.Size = new System.Drawing.Size(84, 24);
            this.windowsToolStripMenuItem.Text = "Windows";
            // 
            // ArrayInit
            // 
            this.ArrayInit.Name = "ArrayInit";
            this.ArrayInit.Size = new System.Drawing.Size(224, 26);
            this.ArrayInit.Text = "Array";
            this.ArrayInit.Click += new System.EventHandler(this.arrayToolStripMenuItem_Click);
            // 
            // TaskInit
            // 
            this.TaskInit.Enabled = false;
            this.TaskInit.Name = "TaskInit";
            this.TaskInit.Size = new System.Drawing.Size(224, 26);
            this.TaskInit.Text = "Calculate";
            this.TaskInit.Click += new System.EventHandler(this.TaskInit_Click);
            // 
            // AnswerInit
            // 
            this.AnswerInit.Enabled = false;
            this.AnswerInit.Name = "AnswerInit";
            this.AnswerInit.Size = new System.Drawing.Size(224, 26);
            this.AnswerInit.Text = "Answer";
            this.AnswerInit.Click += new System.EventHandler(this.AnswerInit_Click);
            // 
            // positionsToolStripMenuItem
            // 
            this.positionsToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tileHorToolStripMenuItem,
            this.tileVertToolStripMenuItem,
            this.cascadeToolStripMenuItem,
            this.closeCurrentToolStripMenuItem,
            this.closeAllToolStripMenuItem});
            this.positionsToolStripMenuItem.Name = "positionsToolStripMenuItem";
            this.positionsToolStripMenuItem.Size = new System.Drawing.Size(81, 24);
            this.positionsToolStripMenuItem.Text = "Positions";
            // 
            // tileHorToolStripMenuItem
            // 
            this.tileHorToolStripMenuItem.Name = "tileHorToolStripMenuItem";
            this.tileHorToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.tileHorToolStripMenuItem.Text = "Tile Hor";
            this.tileHorToolStripMenuItem.Click += new System.EventHandler(this.tileHorToolStripMenuItem_Click);
            // 
            // tileVertToolStripMenuItem
            // 
            this.tileVertToolStripMenuItem.Name = "tileVertToolStripMenuItem";
            this.tileVertToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.tileVertToolStripMenuItem.Text = "Tile Vert";
            this.tileVertToolStripMenuItem.Click += new System.EventHandler(this.tileVertToolStripMenuItem_Click);
            // 
            // cascadeToolStripMenuItem
            // 
            this.cascadeToolStripMenuItem.Name = "cascadeToolStripMenuItem";
            this.cascadeToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.cascadeToolStripMenuItem.Text = "Cascade";
            this.cascadeToolStripMenuItem.Click += new System.EventHandler(this.cascadeToolStripMenuItem_Click);
            // 
            // closeCurrentToolStripMenuItem
            // 
            this.closeCurrentToolStripMenuItem.Name = "closeCurrentToolStripMenuItem";
            this.closeCurrentToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.closeCurrentToolStripMenuItem.Text = "Close Current";
            this.closeCurrentToolStripMenuItem.Click += new System.EventHandler(this.closeCurrentToolStripMenuItem_Click);
            // 
            // closeAllToolStripMenuItem
            // 
            this.closeAllToolStripMenuItem.Name = "closeAllToolStripMenuItem";
            this.closeAllToolStripMenuItem.Size = new System.Drawing.Size(224, 26);
            this.closeAllToolStripMenuItem.Text = "Close All";
            this.closeAllToolStripMenuItem.Click += new System.EventHandler(this.closeAllToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.menuStrip1);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "MDI";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem windowsToolStripMenuItem;
        public System.Windows.Forms.ToolStripMenuItem ArrayInit;
        public System.Windows.Forms.ToolStripMenuItem TaskInit;
        public System.Windows.Forms.ToolStripMenuItem AnswerInit;
        private System.Windows.Forms.ToolStripMenuItem positionsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tileHorToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem tileVertToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cascadeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeCurrentToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeAllToolStripMenuItem;
    }
}

