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
    public partial class 删除普通用户信息窗体 : Form
    {
        public 删除普通用户信息窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 删除普通用户信息窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();//创建“管理员操作窗体”
            f.Show();//打开“管理员操作页面窗体”
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")//如果没有输入帐号
            {
                MessageBox.Show("请输入帐号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }
            if (textBox2.Text == "") //如果没有输入密码
            {
                MessageBox.Show("请输入密码！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                textBox2.Focus(); 
                return; 
            }
            try
            {
                string queryStr = "select * from 用户表 where 帐号='" + textBox1.Text + "'";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable(); 
                myDap.Fill(dt);

                if (dt.Rows.Count == 0) //如果表格中的记录行数为0，即不存在该账号
                {
                    MessageBox.Show("该帐号不存在,请输入正确的帐号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    textBox1.Focus();
                    return;
                }
                else 
                {
                    if (!dt.Rows[0][1].ToString().Trim().Equals(textBox2.Text.Trim()))//如果密码不正确，即用户输入的密码与数据库中读出的密码不一致
                    {
                        MessageBox.Show("密码错误", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        textBox2.Focus();
                        return;
                    }
                    else 
                    {
                        string deleteStr = "delete from 用户表 where 帐号='" + textBox1.Text + "' ";
                        MySqlCommand cmd = new MySqlCommand(deleteStr, 登录窗体.myCon);
                        cmd.ExecuteNonQuery();
                        MessageBox.Show("删除该用户帐号成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        textBox1.Text = "";
                        textBox2.Text = "";
                        textBox1.Focus();
                    }

                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            textBox1.Focus();
        }
    }
}
