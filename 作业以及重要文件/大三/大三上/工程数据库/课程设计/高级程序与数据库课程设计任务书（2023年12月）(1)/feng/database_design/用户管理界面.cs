using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace database_design
{
    public partial class 用户管理界面 : Form
    {
        public 用户管理界面()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            创建用户界面 from = new 创建用户界面();
            from.Show();
        }

        private void 用户管理界面_FormClosing(object sender, FormClosingEventArgs e)
        {
         
        }

        private void 用户管理界面_Load(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            所有用户信息界面 From = new 所有用户信息界面();
            From.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            修改用户信息界面 from = new 修改用户信息界面();
            from.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            删除用户信息窗体 f=new 删除用户信息窗体();
            f.Show();
        }
    }
}
