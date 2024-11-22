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

namespace database_design
{
    public partial class 历史数据管理界面 : Form
    {
        public 历史数据管理界面()
        {
            InitializeComponent();
        }

        private void 历史数据管理界面_Load(object sender, EventArgs e)
        {
            button1.Enabled = true;
            button2.Enabled = true;
            listView1.View = View.Details;
            listView1.GridLines = true;

            ColumnHeader ch;
            ch = new ColumnHeader();

            ch.Text = "记录编号";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "监测点编号";
            ch.Width = (listView1.Width - 20) / 4;
            ch.TextAlign = HorizontalAlignment.Center;
            listView1.Columns.Add((ColumnHeader)ch.Clone());

            ch.Text = "光照度值";
            ch.Width = (listView1.Width - 20) / 4;
            ch.TextAlign = HorizontalAlignment.Center;
            listView1.Columns.Add((ColumnHeader)ch.Clone());

            ch.Text = "测量时间";
            ch.Width = (listView1.Width - 20) / 4;
            ch.TextAlign = HorizontalAlignment.Center;
            listView1.Columns.Add((ColumnHeader)ch.Clone());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("请指定监测点名称", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                textBox1.Focus();
                return;
            }

            string queryStr1 = "select * from jcdxxb where 监测点名称 = '" + textBox1.Text + "'";
            MySqlDataAdapter myDap1 = new MySqlDataAdapter(queryStr1, 登录窗体.myCon);
            DataTable dt1 = new DataTable();
            myDap1.Fill(dt1);

            string jcdbh = dt1.Rows[0][0].ToString();
            try
            {
                string queryStr = "select * from 测量记录表 where 监测点编号 = '" + jcdbh + "' order by 记录编号 desc;";
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable();
                myDap.Fill(dt);

                if (dt.Rows.Count == 0)//如果表格中的记录行数为0，即不存在相关记录
                {
                    MessageBox.Show("该监测点编号不存在或时间段不存在,请重新输入！", "注意", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    textBox1.Focus();
                    return;
                }

                listView1.Items.Clear();
                ListViewItem listItem = null;//定义一个listItem对象
                for (int m = 0; m < dt.Rows.Count; m++)
                {
                    listItem = new ListViewItem(dt.Rows[m][0].ToString());
                    for (int n = 1; n < dt.Columns.Count; n++)
                    {
                        listItem.SubItems.Add(dt.Rows[m][n].ToString());
                    }
                    listView1.Items.Add(listItem);
                }

            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string queryStr1 = "select * from 监测点信息表 where 监测点名称 = '" + textBox1.Text + "'";
            MySqlDataAdapter myDap1 = new MySqlDataAdapter(queryStr1, 登录窗体.myCon);
            DataTable dt1 = new DataTable();
            myDap1.Fill(dt1);

            string jcdbh1 = dt1.Rows[0][0].ToString();
            try
            {
                string updateStr = "delete from 测量记录表 where 监测点编号 = '" + textBox1.Text.Trim() + "' order by 记录编号 desc;";
                MySqlCommand cmd = new MySqlCommand(updateStr, 登录窗体.myCon);
                cmd.ExecuteNonQuery();
                MessageBox.Show("删除成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }
    }
}
