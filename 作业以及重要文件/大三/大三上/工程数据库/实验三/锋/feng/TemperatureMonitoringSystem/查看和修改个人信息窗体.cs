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

namespace TemperatureMonitoringSystem
{
    public partial class 查看和修改个人信息窗体 : Form
    {
        public 查看和修改个人信息窗体()
        {
            InitializeComponent();
        }

        private void 查看和修改个人信息窗体_Load(object sender, EventArgs e)
        {
            try
            {
                string queryStr = "select * from yhb where yhm='" + Form1.loginUser + "'"; //查询登录用户信息的SQL语句
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, Form1.myCon); //执行SQL语句
                DataTable dt = new DataTable(); //定义存储查询结果的表格
                myDap.Fill(dt); //将查询结果填充进表格
                                //2.显示从数据库中读取的登录用户的信息
                label2.Text = dt.Rows[0][0].ToString();//显示用户名信息
                textBox1.Text = dt.Rows[0][2].ToString();//显示姓名信息
                                                         //显示性别信息
                if (dt.Rows[0][3].ToString().Equals("男")) comboBox1.SelectedIndex = 0;
                if (dt.Rows[0][3].ToString().Equals("女")) comboBox1.SelectedIndex = 1;
                textBox2.Text = dt.Rows[0][4].ToString();//显示手机号码信息
                textBox3.Text = dt.Rows[0][5].ToString();//显示邮箱信息
            }
            catch (Exception err)
            {
                //3.如果数据库操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            { 
            string updateStr = "update yhb set xm='" + textBox1.Text.Trim() + "',xb='" + comboBox1.Text.Trim() + "',sj='" + textBox2.Text.Trim() + "',yx='" + textBox3.Text.Trim() + "' where yhm='" + Form1.loginUser + "'"; //修改用户信息的SQL语句
            MySqlCommand cmd = new MySqlCommand(updateStr, Form1.myCon); //创建执行SQL语句的命令
            cmd.ExecuteNonQuery(); //执行SQL语句
                                   //2.修改成功后弹出对话框提示
            MessageBox.Show("修改成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                //3.如果数据库操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Dispose();//关闭当前窗体
        }
    }
}
