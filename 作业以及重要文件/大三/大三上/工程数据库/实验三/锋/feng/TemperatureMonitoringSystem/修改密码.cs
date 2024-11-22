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
using static System.Windows.Forms.VisualStyles.VisualStyleElement;


namespace TemperatureMonitoringSystem
{
    public partial class 修改密码 : Form
    {
        public 修改密码()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Dispose();//关闭当前窗体
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                string updateStr = "update yhb set mm='" + textBox3.Text.Trim() + "'where yhm ='"+ Form1.loginUser + "'";//创建修改登录用户密码的SQL语句
                MySqlCommand cmd = new MySqlCommand(updateStr, Form1.myCon); //创建执行SQL语句的命令
                cmd.ExecuteNonQuery(); //执行SQL语句
                MessageBox.Show("修改成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);//弹出对话框
            }
            catch (Exception err)
            {
                //3.如果数据库操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "修改时出现错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void 修改密码_Load(object sender, EventArgs e)
        {

        }
    }
}
