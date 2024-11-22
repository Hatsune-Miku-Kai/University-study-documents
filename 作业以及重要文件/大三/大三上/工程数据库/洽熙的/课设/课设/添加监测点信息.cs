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
    public partial class 添加监测点信息 : Form
    {
        public 添加监测点信息()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void 添加监测点信息_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();
            f.Show();//打开“管理员操作页面窗体”
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("请输入监测点编号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }
            if (textBox2.Text == "")
            {
                MessageBox.Show("请输入监测点名称！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox2.Focus();
                return;
            }
            if (textBox3.Text == "")
            {
                MessageBox.Show("请输入使用仪器编号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox3.Focus();
                return;
            }
            if (textBox4.Text == "")
            {
                MessageBox.Show("请输入说明！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox4.Focus();
                return;
            }
            try 
            {
                string queryStr = "select * from 监测点信息表 where 监测点编号='" + textBox1.Text + "'";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable(); 
                myDap.Fill(dt);

                if (dt.Rows.Count == 1) //如果表格中的记录行数为1，即存在相同的监测点编号
                {
                    MessageBox.Show("已存在相同的监测点编号,请重新输入账号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                    textBox1.Focus(); 
                    return; 
                }
                else
                {
                    string insertStr = "insert into 监测点信息表 values('" + textBox1.Text.Trim() + "','" + textBox2.Text.Trim() + "','" + textBox3.Text.Trim() + "','" + textBox4.Text.Trim() + "')"; 
                    MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句

                    MessageBox.Show("添加成功！", "恭喜", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    textBox1.Text = "";
                    textBox2.Text = "";
                    textBox3.Text = "";
                    textBox4.Text = "";
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
            textBox3.Text = "";
            textBox4.Text = "";
            textBox1.Focus();
        }
    }
}
