using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace 课设
{
    public partial class 管理员操作窗体 : Form
    {
        public 管理员操作窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 管理员操作窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            //跳出对话框询问是否确定要退出系统，若确定，则关闭本窗体并释放资源，退出程序
            if (MessageBox.Show("你确定要退出系统吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
                Application.Exit(); //退出程序
            }
            //若取消关闭窗体
            else
            {
                e.Cancel = true; //取消关闭窗体
            }
        }

        private void 管理员操作窗体_Load(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            添加普通用户信息窗体 f = new 添加普通用户信息窗体();//创建“添加普通用户信息窗体”
            f.Show();//打开“添加普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button2_Click(object sender, EventArgs e)
        {
            查看普通用户信息窗体 f = new 查看普通用户信息窗体();//创建“查看用户信息窗体”
            f.Show();//打开“查看用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button3_Click(object sender, EventArgs e)
        {
            修改普通用户信息窗体 f = new 修改普通用户信息窗体();//创建“修改普通用户信息窗体”
            f.Show();//打开“修改普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button4_Click(object sender, EventArgs e)
        {
            删除普通用户信息窗体 f = new 删除普通用户信息窗体();//创建“删除普通用户信息窗体”
            f.Show();//打开“删除普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button7_Click(object sender, EventArgs e)
        {
            修改监测点信息 f = new 修改监测点信息();
            f.Show();//打开“删除普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button5_Click(object sender, EventArgs e)
        {
            添加监测点信息 f = new 添加监测点信息();
            f.Show();//打开“删除普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button6_Click(object sender, EventArgs e)
        {
            查看监测点信息 f = new 查看监测点信息();
            f.Show();//打开“删除普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button8_Click(object sender, EventArgs e)
        {
            删除监测点信息 f = new 删除监测点信息();
            f.Show();//打开“删除普通用户信息窗体”      
            this.Dispose(); //关闭本窗体并释放资源
        }
    }
}
