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

namespace database_design
{
    public partial class 创建用户界面 : Form
    {
        public 创建用户界面()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void 创建用户界面_Load(object sender, EventArgs e)
        {
            comboBox1.SelectedIndex = 0;
            comboBox2.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("你确定要取消创建吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
            }
          
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //1.如果没有输入用户名，跳出对话框提示，焦点落在用户名文本框，并结束函数的运行
            if (textBox1.Text == "") //如果没有输入用户名
            {
                MessageBox.Show("请输入用户名", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); //提示信息的对话框
                textBox1.Focus(); //焦点落在用户名文本框
                return; //结束本函数的运行
            }
            //2.如果没有输入密码，跳出对话框提示，焦点落在密码文本框，并结束函数的运行
            if (textBox2.Text == "") //如果没有输入密码
            {
                MessageBox.Show("请输入密码！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); //提示信息的对话框
                textBox2.Focus(); //焦点落在密码文本框
                return; //结束本函数的运行
            }
            //3.如果没有再次输入密码，跳出对话框提示，焦点落在再次输入密码文本框，并结束函数的运行
            if (textBox3.Text == "") //如果没有再次输入密码
            {
                MessageBox.Show("请再次输入密码！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); //提示信息的对话框
                textBox3.Focus(); //焦点落在再次输入密码文本框
                return; //结束本函数的运行
            }
            //4.如果两次输入密码不一致，跳出对话框提示，焦点落在密码文本框，并结束函数的运行
            if (String.Compare(textBox2.Text.Trim(), textBox3.Text.Trim(), false) != 0) //如果两次输入的密码不一致，区分大小写
            {
                MessageBox.Show("两次输入的密码不一致", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); //提示信息的对话框
                textBox2.Focus(); //焦点落在密码文本框
                return; //结束本函数的运行
            }
            try
            {
                //5.根据用户填写的用户名到数据库查询相应的记录，根据查询结果进行对应处理
                //5.1确定根据用户填写的用户名到数据库查询相应的记录的SQL语句
                string queryStr = "select * from yhb where 账号='" + textBox1.Text + "'";
                //5.2执行SQL语句
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                //5.3将查询结果存储进行表格变量dt
                DataTable dt = new DataTable(); //定义存储查询结果的表格
                myDap.Fill(dt); //将查询结果填充进表格
                                //5.4根据查询结果进行相应处理
                                //5.4.1如果查询到对应的记录，则提示用户名存在，焦点落在用户名文本框，并结束函数的运行
                if (dt.Rows.Count == 1) //如果表格中的记录行数为1，即存在相同的用户名
                {
                    MessageBox.Show("已存在相同的用户名,请重新输入用户名！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); //提示信息的对话框
                    textBox1.Focus(); //焦点落在用户名文本框
                    return; //结束本函数的运行
                }
                //5.4.2如果没有查询到对应的记录，即用户名不存在，则将用户填写的信息写入数据库，并提示注册成功，同时清空所有文本框的内容，焦点落在用户名文本框，为下一次注册做准备
                else
                {
                    //5.4.2.1将用户填写的信息写入数据库
                    string insertStr = "insert into yhb values('" + textBox1.Text.Trim() + "','" + textBox2.Text.Trim() + "','" + comboBox1.Text.Trim()+ "','" + textBox4.Text.Trim() + "','" +comboBox2.Text.Trim()+ "','"+textBox5.Text.Trim() + "','" + textBox6.Text.Trim() + "')"; //实现将用户填写的信息写入数据库的SQL语句
                    MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句
                                           //5.4.2.2跳出对话框提示注册成功
                    MessageBox.Show("注册成功！", "恭喜", MessageBoxButtons.OK, MessageBoxIcon.Information); //提示信息的对话框
                                                                                                      //5.4.2.3清空所有文本框的内容，为下一次注册做准备
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox3.Text = "";
                    textBox4.Text = "";
                    textBox5.Text = "";
                    textBox6.Text = "";
                    textBox1.Focus(); //焦点落在用户名文本框
                }
            }
            //6.如果操作数据库出现错误，弹出对话框提示
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示信息的对话框
            }
        }

        private void 创建用户界面_FormClosing(object sender, FormClosingEventArgs e)
        {
                this.Dispose(); //关闭本窗体并释放资源
        }
    }
}
