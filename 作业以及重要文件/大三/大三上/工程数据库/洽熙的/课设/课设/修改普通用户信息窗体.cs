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
    public partial class 修改普通用户信息窗体 : Form
    {
        public 修改普通用户信息窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void 修改普通用户信息窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();//创建“管理员操作窗体”
            f.Show();//打开“管理员操作页面窗体”
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void 修改普通用户信息窗体_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")//如果没有输入账号
            {
                MessageBox.Show("请输入帐号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }
            try
            {
                string queryStr = "select * from 用户表 where 帐号='" + textBox1.Text + "'";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable(); 
                myDap.Fill(dt);

                if (dt.Rows.Count == 0) //如果表格中的记录行数为0，即不存在相同的账号
                {
                    MessageBox.Show("该账号不存在,请输入正确的账号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    textBox1.Focus();
                    return;
                }
                else
                {
                    string updateStr = "update 用户表 set 密码='" + textBox2.Text.Trim() + "',姓名='" + textBox4.Text.Trim() + "',性别='" + comboBox1.Text.Trim() + "',手机='" + textBox5.Text.Trim() + "',邮箱='" + textBox6.Text.Trim() + "' where 帐号='" + textBox1.Text.Trim() + "'"; 
                    MySqlCommand cmd = new MySqlCommand(updateStr, 登录窗体.myCon);
                    cmd.ExecuteNonQuery();

                    MessageBox.Show("修改成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox4.Text = "";
                    textBox5.Text = "";
                    textBox6.Text = "";
                    textBox1.Focus();
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox4.Text = "";
            textBox5.Text = "";
            textBox6.Text = "";
            textBox1.Focus();
        }
    }
}
