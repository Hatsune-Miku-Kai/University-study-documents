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
    public partial class 添加普通用户信息窗体 : Form
    {
        public 添加普通用户信息窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 添加普通用户信息窗体_Load(object sender, EventArgs e)
        {
            //选中comboBox1列表的第0项，即性别组合框默认选择“男”
            comboBox1.SelectedIndex = 0;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //按取消清空所有文本框
            textBox1.Text = "";
            textBox2.Text = "";
            textBox4.Text = "";
            textBox5.Text = "";
            textBox6.Text = "";
            comboBox1.SelectedIndex = 0;
        }

        private void 添加普通用户信息窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();//创建“管理员操作页面窗体”
            f.Show();//打开“管理员操作页面窗体”
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") //如果没有输入账号
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
            if (textBox4.Text == "") //如果没有姓名
            {
                MessageBox.Show("请输入姓名！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                textBox4.Focus(); 
                return; 
            }
            if (textBox5.Text == "") //如果没有输入手机号码
            {
                MessageBox.Show("请输入手机号码！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                textBox5.Focus(); 
                return; 
            }
            if (textBox6.Text == "") //如果没有输入邮箱
            {
                MessageBox.Show("请输入邮箱！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                textBox6.Focus(); 
                return; 
            }
            try
            {
                string queryStr = "select * from 用户表 where 帐号='" + textBox1.Text + "'";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable(); //定义存储查询结果的表格
                myDap.Fill(dt); //将查询结果填充进表格

                if (dt.Rows.Count == 1) //如果表格中的记录行数为1，即存在相同的账号
                {
                    MessageBox.Show("已存在相同的账号,请重新输入账号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                    textBox1.Focus(); 
                    return; 
                }
                else
                {
                    //将用户填写的信息写入数据库
                    string insertStr = "insert into 用户表 values('" + textBox1.Text.Trim() + "','" + textBox2.Text.Trim() + "','" + textBox3.Text.Trim() + "','" + textBox4.Text.Trim() + "','" + comboBox1.Text.Trim() + "','" + textBox5.Text.Trim() + "','" + textBox6.Text.Trim() + "')"; 
                    MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句                                          
                    MessageBox.Show("添加成功！", "恭喜", MessageBoxButtons.OK, MessageBoxIcon.Information); 
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
    }
}
