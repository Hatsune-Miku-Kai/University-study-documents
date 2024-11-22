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
    public partial class 修改监测点信息 : Form
    {
        public 修改监测点信息()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 修改监测点信息_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();
            f.Show();
            this.Dispose(); 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")//如果没有输入监测点编号
            {
                MessageBox.Show("您没有输入监测点编号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }
            try
            {
                string queryStr = "select * from 监测点信息表 where 监测点编号='" + textBox1.Text + "'";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable(); 
                myDap.Fill(dt);

                if (dt.Rows.Count == 0) //如果表格中的记录行数为0，即没有对应的监测点编号可以修改
                {
                    MessageBox.Show("该监测点编号不存在,请输入正确的监测点编号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    textBox1.Focus();
                    return;
                }
                else
                {
                    string updateStr = "update 监测点信息表 set 监测点名称='" + textBox2.Text.Trim() + "',使用仪器编号='" + textBox3.Text.Trim() + "',说明='" + textBox4.Text.Trim() + "' where 监测点编号='" + textBox1.Text.Trim() + "'"; 
                    MySqlCommand cmd = new MySqlCommand(updateStr, 登录窗体.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句

                    MessageBox.Show("修改成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
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
