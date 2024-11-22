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
    public partial class 登录窗体 : Form
    {
        public 登录窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }
        public static MySqlConnection myCon;//定义可全局使用的数据库连接变量
        public static string loginUser;//定义可全局使用的用于存储登录系统的用户的用户名变量

        private void 登录窗体_Load(object sender, EventArgs e)
        {
            try
            {
                string conStr = "data source=localhost;database =wsdjcxt;user id=root;password=qq1002686100;charset=utf8";
                myCon = new MySqlConnection(conStr);
                myCon.Open();
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (comboBox1.Text == "")//如果没有选择用户类型
            {
                MessageBox.Show("您没有选择用户类型", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                comboBox1.Focus();
                return;
            }
            if (textBox1.Text == "")//如果没有输入账号
            {
                MessageBox.Show("您没有输入账号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }
            if (textBox2.Text == "")//如果没有输入密码
            {
                MessageBox.Show("您没有输入密码", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox2.Focus();
                return;
            }
            try
            {
                //确定根据用户填写的用户名到数据库查询相应的记录的SQL语句
                string queryStr = "select * from 用户表 where 帐号='" + textBox1.Text + "'";
                //执行SQL语句
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, myCon);
                //将查询结果存储进行表格变量dt
                DataTable dt = new DataTable();//定义存储查询结果的表格
                myDap.Fill(dt);//将查询结果填充进表格

                if (dt.Rows.Count == 0)//如果表格中的记录行数为0，即没有查询到对应的记录
                {
                    MessageBox.Show("账号不存在", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    textBox1.Focus();
                    return;
                }
                //如果查询到对应的记录，则比较密码是否正确，并进行对应处理
                else
                {
                    //如果密码不正确，则弹出对话框提示，焦点落在密码文本框，并结束函数的运行
                    if (!dt.Rows[0][1].ToString().Trim().Equals(textBox2.Text.Trim()))
                    {
                        MessageBox.Show("密码错误", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        textBox2.Focus();
                        return;
                    }
                    if (!dt.Rows[0][2].ToString().Trim().Equals(comboBox1.Text.Trim()))//如果用户类型选择不正确
                    {
                        MessageBox.Show("用户类型错误", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                        comboBox1.Focus();
                        return;
                    }
                    else
                    {
                        if (comboBox1.Text == "管理员")
                        {
                            loginUser = textBox1.Text.Trim();//记录登录用户的账号
                            管理员操作窗体 f = new 管理员操作窗体();//创建“管理员操作窗体”
                            f.Show();//打开“管理员操作窗体”      
                            this.Hide();//隐藏“登录窗体”
                        }
                        if (comboBox1.Text == "普通用户")
                        {
                            loginUser = textBox1.Text.Trim();
                            普通用户操作窗体 f = new 普通用户操作窗体();//创建“普通用户操面窗体”
                            f.Show();//打开“普通用户操作窗体”      
                            this.Hide();
                        }
                    }

                }

            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            comboBox1.Text = "";
            textBox1.Text = "";
            textBox2.Text = "";
        }
    }
}
