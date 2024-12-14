using MySql.Data.MySqlClient;
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
    public partial class 登录窗体 : Form
    {
        public 登录窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }
        public static MySqlConnection myCon;//定义可全局使用的数据库连接变量
        public static string loginUser;//定义可全局使用的用于存储登录系统的用户的用户名变量
        private void button2_Click(object sender, EventArgs e)
        {

        }

        private void 登录窗体_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            try
            {
                //1.根据MySQL的地址、要访问的数据库名称、用户名、密码、使用的字符编码等信息确定连接语句
                string conStr = "data source=localhost;database =swdjcxt;user id=root;password=Guo031028;charset=utf8";
                //2.根据连接语句，创建与数据库的连接对象
                myCon = new MySqlConnection(conStr);
                //3.打开与数据库的连接
                myCon.Open();
            }
            catch (Exception err)//捕捉错误
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示错误信息的对话框
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            //1.如果没有输入用户名，跳出对话框提示，焦点落在用户名文本框，并结束函数的运行
            if (textBox1.Text == "")//如果没有输入用户名
            {
                MessageBox.Show("您没有输入用户名", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);//提示信息的对话框
                textBox1.Focus();//焦点落在用户名文本框
                return;//结束本函数的运行
            }
            //2.如果没有输入密码，跳出对话框提示，焦点落在密码文本框，并结束函数的运行
            if (textBox2.Text == "")//如果没有输入密码
            {
                MessageBox.Show("您没有输入密码", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);//提示信息的对话框
                textBox2.Focus();//焦点落在密码文本框
                return;//结束本函数的运行
            }
            //3.根据用户填写的用户名到数据库查询相应的记录，根据查询结果进行对应处理
            try
            {
                //3.1确定根据用户填写的用户名到数据库查询相应的记录的SQL语句
                string queryStr = "select * from yhb where 账号='" + textBox1.Text + "'and 用户类型='"+comboBox1.Text.Trim()+"'";
                //3.2执行SQL语句
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, myCon);
                //3.3将查询结果存储进行表格变量dt
                DataTable dt = new DataTable();//定义存储查询结果的表格
                myDap.Fill(dt);//将查询结果填充进表格
                               //3.4根据查询结果进行相应处理
                               //3.4.1如果没有查询到对应的记录，则提示用户名不存在，焦点落在用户名文本框，并结束函数的运行
                if (dt.Rows.Count == 0)//如果表格中的记录行数为0，即没有查询到对应的记录
                {
                    MessageBox.Show("该用户不存在", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);//提示信息的对话框
                    textBox1.Focus();//焦点落在用户名文本框
                    return; //结束函数的运行
                }
                //3.4.2如果查询到对应的记录，则比较密码是否正确，并进行对应处理
                else
                {
                    //3.4.2.1如果密码不正确，则弹出对话框提示，焦点落在密码文本框，并结束函数的运行
                    if (!dt.Rows[0][1].ToString().Trim().Equals(textBox2.Text.Trim()))//如果密码不正确，即用户输入的密码与数据库中读出的密码不一致
                    {
                        MessageBox.Show("密码错误", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);//提示信息的对话框
                        textBox2.Focus();//焦点落在密码文本框
                        return;//结束函数的运行
                    }
                    //3.4.2.2如果密码正确，则登录成功，记录登录用户的用户名，打开“系统主界面窗体”，隐藏“登录窗体”
                    if (dt.Rows[0][2].ToString().Trim().Equals("用户"))
                    {
                        loginUser = textBox1.Text.Trim();//记录登录用户的用户名                               
                        用户界面窗体 f = new 用户界面窗体();//创建“系统主界面窗体”
                        f.Show();//打开“系统主界面窗体”      
                        this.Hide();//隐藏“登录窗体”
                    }
                    else 
                    {

                        loginUser = textBox1.Text.Trim();//记录登录用户的用户名
                        管理员界面窗体 f = new 管理员界面窗体();//创建“系统主界面窗体”
                        f.Show();//打开“系统主界面窗体”
                        this.Hide();//隐藏“登录窗体”
                    }
                }
            }
            //4.如果操作数据库出现错误，弹出对话框提示
            catch (Exception err)//捕捉错误
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示信息的对话框
            }
        }
    }
}
