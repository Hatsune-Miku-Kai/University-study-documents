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
    public partial class 查看普通用户信息窗体 : Form
    {
        public 查看普通用户信息窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 查看普通用户信息窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            管理员操作窗体 f = new 管理员操作窗体();//创建“管理员操作页面窗体”
            f.Show();//打开“管理员操作页面窗体”
            this.Dispose(); //关闭本窗体并释放资源
        }

        private void 查看普通用户信息窗体_Load(object sender, EventArgs e)
        {
            listView1.View = View.Details;//视图
            listView1.GridLines = true;//网格线

            ColumnHeader ch;//定义一个列标题
            ch = new ColumnHeader();//创建一个列标题

            ch.Text = "帐号";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "密码";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "用户类型";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "姓名";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "性别";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "手机";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "邮箱";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 7;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            try
            {
                string queryStr = "select * from 用户表";//查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);//执行SQL语句
                DataTable dt = new DataTable();
                myDap.Fill(dt);
                listView1.Items.Clear(); //清除listView1中原有显示内容
                ListViewItem listItem = null; //定义一个listItem对象 

                for (int m = 0; m < dt.Rows.Count; m++)//逐行读取表格形式的查询结果显示在listView1中
                {
                    if (dt.Rows[m][2].ToString() == "普通用户")
                    {
                        listItem = new ListViewItem(dt.Rows[m][0].ToString());//创建1个listItem对象，其对应listView1中的1个行，并将查询结果每1行的第1个元素添加为其第1项元素
                        for (int n = 1; n < dt.Columns.Count; n++)//读取每一行的剩余其他元素的内容并添加进listItem对象
                        {
                            listItem.SubItems.Add(dt.Rows[m][n].ToString());//将每一行的其他元素添加进listItem对象
                        }
                        listView1.Items.Add(listItem);//将listItem的内容（某1行的数据）添加进listView1并显示
                    }
                }
            }
            catch(Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }
    }
}
