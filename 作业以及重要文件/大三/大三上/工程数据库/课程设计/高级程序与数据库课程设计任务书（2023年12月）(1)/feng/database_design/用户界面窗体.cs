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
    public partial class 用户界面窗体 : Form
    {
        public 用户界面窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 用户界面窗体_Load(object sender, EventArgs e)
        {
            try
            {
                string queryStr = "select * from cljlb order by 记录编号 desc";//查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                DataTable dt = new DataTable();
                myDap.Fill(dt);

                listView1.Items.Clear();
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

        private void 用户界面窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("你确定要退出系统吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
                Application.Exit(); //退出程序
            }
        }

        private void 历史数据管理界面ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            历史数据管理界面 f=new 历史数据管理界面();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }
}
