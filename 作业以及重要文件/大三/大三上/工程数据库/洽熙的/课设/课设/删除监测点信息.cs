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
    public partial class 删除监测点信息 : Form
    {
        public 删除监测点信息()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 删除监测点信息_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();
            f.Show();
            this.Dispose();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "") 
            {
                MessageBox.Show("请输入监测点编号", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus(); 
                return; 
            }

            string queryStr = "select * from 监测点信息表 where 监测点编号='" + textBox1.Text + "'";
            MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
            DataTable dt = new DataTable();
            myDap.Fill(dt);

            if (dt.Rows.Count == 0) //如果表格中的记录行数为1，即不存在该监测点编号
            {
                MessageBox.Show("该监测点编号不存在,请输入正确的监测点编号！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation); 
                textBox1.Focus(); 
                return; 
            }
            else
            {
                string deleteStr = "delete from 监测点信息表 where 监测点编号='" + textBox1.Text + "' ";
                MySqlCommand cmd = new MySqlCommand(deleteStr, 登录窗体.myCon);
                cmd.ExecuteNonQuery();

                MessageBox.Show("删除该监测点编号成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                textBox1.Text = "";
                textBox1.Focus();
            }
        }
    }
}
