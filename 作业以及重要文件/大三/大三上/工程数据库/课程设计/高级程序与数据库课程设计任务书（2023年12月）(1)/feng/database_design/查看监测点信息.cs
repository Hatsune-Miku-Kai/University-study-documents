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
    public partial class 查看监测点信息 : Form
    {
        public 查看监测点信息()
        {
            InitializeComponent();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void 查看监测点信息_Load(object sender, EventArgs e)
        {
                listView1.View = View.Details;//视图
                listView1.GridLines = true;//网格线

                ColumnHeader ch;//定义一个列标题
                ch = new ColumnHeader();//创建一个列标题

                ch.Text = "监测点编号";//设置列标题内容            
                ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
                ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
                listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

                ch.Text = "监测点名称";//设置列标题内容
                ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
                ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
                listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

                ch.Text = "使用仪器编号";//设置列标题内容
                ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
                ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
                listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

                ch.Text = "说明";//设置列标题内容            
                ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
                ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
                listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

                try
                {
                    string queryStr = "select * from 监测点信息表";//查询获取所有测量记录并按记录编号降序排列
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

                }
                catch (Exception err)
                {
                    MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                }
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }

}
