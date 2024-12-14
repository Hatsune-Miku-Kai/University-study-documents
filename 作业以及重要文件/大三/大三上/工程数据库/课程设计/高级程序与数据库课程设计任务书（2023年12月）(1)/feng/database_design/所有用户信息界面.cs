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
    public partial class 所有用户信息界面 : Form
    {
        public 所有用户信息界面()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 所有用户信息界面_Load(object sender, EventArgs e)
        {
            try
            {
                Microsoft.Win32.RegistryKey keyCom = Microsoft.Win32.Registry.LocalMachine.OpenSubKey("Hardware\\DeviceMap\\SerialComm");
                string[] sSubKeys = keyCom.GetValueNames();
                for (int i = 0; i < sSubKeys.Length; i++)
                {
                    comboBox1.Items.Add((string)keyCom.GetValue(sSubKeys[i]));//在组合框comboBox1中添加获取的串口名称
                    if (i == 1) comboBox1.SelectedIndex = 1;//设置默认串口为列表中的第2项，一般为COM2
                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示信息的对话框
            }
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            listView1.View = View.Details;//视图
            listView1.GridLines = true;//网格线

            ColumnHeader ch;//定义一个列标题
            ch = new ColumnHeader();//创建一个列标题

            ch.Text = "账号";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "密码";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "用户类型";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "姓名";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "性别";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "手机";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "邮箱";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 6;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列
            try
            {
                string queryStr = "select * from yhb where 用户类型='用户' ";//查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);//执行SQL语句
                DataTable dt = new DataTable();//定义一个表格
                myDap.Fill(dt);//将查询结果填充进表格
                listView1.Items.Clear(); //清除listView1中原有显示内容
                ListViewItem listItem = null; //定义一个listItem对象        
                for (int m = 0; m < dt.Rows.Count; m++)//逐行读取表格形式的查询结果显示在listView1中
                {
                    listItem = new ListViewItem(dt.Rows[m][0].ToString());//创建1个listItem对象，其对应listView1中的1个行，并将查询结果每1行的第1个元素添加为其第1项元素
                    for (int n = 1; n < dt.Columns.Count; n++)//读取每一行的剩余其他元素的内容并添加进listItem对象
                    {
                        listItem.SubItems.Add(dt.Rows[m][n].ToString());//将每一行的其他元素添加进listItem对象
                    }
                    listView1.Items.Add(listItem);//将listItem的内容（某1行的数据）添加进listView1并显示
                }
                button1.Enabled = false;
                MessageBox.Show("已显示所有用户信息！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            //6.如果操作数据库出现错误，弹出对话框提示
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示信息的对话框
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                string queryStr = "select * from yhb where 用户类型='用户'"; //查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon); //执行SQL语句
                DataTable dt = new DataTable(); //定义一个表格
                myDap.Fill(dt); //将查询结果填充进表格
                listView1.Items.Clear();//清除listView1中原有显示内容
                ListViewItem listItem = null;//定义一个listItem对象
                for (int m = 0; m < dt.Rows.Count; m++)//逐行读取表格形式的查询结果显示在listView1中
                {
                    listItem = new ListViewItem(dt.Rows[m][0].ToString());//创建1个listItem对象，其对应listView1中的1个行，并将查询结果每1行的第1个元素添加为其第1项元素
                    for (int n = 1; n < dt.Columns.Count; n++)//读取每一行的剩余其他元素的内容并添加进listItem对象
                    {
                        listItem.SubItems.Add(dt.Rows[m][n].ToString());//将每一行的其他元素添加进listItem对象
                    }
                    listView1.Items.Add(listItem);//将listItem的内容（某1行的数据）添加进listView1并显示
                }
                MessageBox.Show("刷新成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
