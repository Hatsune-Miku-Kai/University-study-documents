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
    public partial class 管理员界面窗体 : Form
    {
        public 管理员界面窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 管理员界面窗体_Load(object sender, EventArgs e)
        {
            
        }


        private void 管理员界面窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("你确定要退出系统吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
                Application.Exit();
            }
            //2.若取消关闭窗体
            else
            {
                e.Cancel = true; //取消关闭窗体
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            用户管理界面 from = new 用户管理界面();
            from.Show();
 
        }

        private void button3_Click(object sender, EventArgs e)
        {
            监测点管理界面 f=new 监测点管理界面();
            f.Show();
        }
    }
}
