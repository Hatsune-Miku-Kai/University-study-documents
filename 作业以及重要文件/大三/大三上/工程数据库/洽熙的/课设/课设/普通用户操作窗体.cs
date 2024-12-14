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
    public partial class 普通用户操作窗体 : Form
    {
        public 普通用户操作窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        public static MySqlConnection myCon;//定义可全局使用的数据库连接变量
        public static string loginUser;//定义可全局使用的用于存储登录系统的用户的用户名变量

        private void 普通用户操作窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            //跳出对话框询问是否确定要退出系统，若确定，则关闭本窗体并释放资源，退出程序
            if (MessageBox.Show("你确定要退出系统吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
                Application.Exit(); //退出程序
            }
            //若取消关闭窗体
            else
            {
                e.Cancel = true; 
            }
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                //关闭串口
                serialPort1.Close();

                //对数据监测启停区的显示进行设置
                comboBox1.Enabled = true;//设置选择串口组合框可用
                button1.Enabled = true;//设置启动数据监测按钮可用
                button2.Enabled = false;//设置停止数据监测按钮不可用

                label4.Visible = false;//隐藏标签
                label5.Visible = false;
                label6.Visible = false;
                label7.Visible = false;
                label8.Visible = false;
                label9.Visible = false;
                label10.Visible = false;
                label11.Visible = false;
                label12.Visible = false;
                label13.Visible = false;
                label14.Visible = false;
                label15.Visible = false;
                label16.Visible = false;
                label17.Visible = false;
                label18.Visible = false;

                label3.ForeColor = Color.Red;//设置温度值显示标签的字体颜色为红色
                label3.Text = "数据监测未启动";//设置温度值显示标签的内容为“数据监测未启动”

                button4.Enabled = true;//设置手动刷新按钮可用
                button3.Enabled = false;//设置5s定时刷新按钮不可用
                button5.Enabled = false;//设置关闭定时刷新按钮不可用

                timer1.Enabled = false;//设置定时器不可用
                timer1.Interval = 5000;//设置定时刷新时间为5s

                MessageBox.Show("停止数据监测！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            button4.Enabled = true;//设置手动刷新按钮可用
            button3.Enabled = true;//设置5s定时刷新按钮可用
            button5.Enabled = false;//设置关闭定时刷新按钮不可用
            //2.设置定时器无效
            timer1.Enabled = false;
            MessageBox.Show("关闭定时刷新！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void 普通用户操作窗体_Load(object sender, EventArgs e)
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

            button1.Enabled = true;//设置启动按钮可用
            button2.Enabled = false;//设置关闭按钮不可用

            label4.Visible = false;//隐藏标签
            label5.Visible = false;
            label6.Visible = false;
            label7.Visible = false;
            label8.Visible = false;
            label9.Visible = false;
            label10.Visible = false;
            label11.Visible = false;
            label12.Visible = false;
            label13.Visible = false;
            label14.Visible = false;
            label15.Visible = false;
            label16.Visible = false;
            label17.Visible = false;
            label18.Visible = false;

            label3.ForeColor = Color.Red;//设置温度值显示标签的字体颜色为红色
            label3.Text = "数据监测未启动";//设置温度值显示标签的内容为“数据监测未启动”

            button4.Enabled = true;//设置手动刷新按钮可用
            button3.Enabled = false;//设置5s定时刷新按钮不可用
            button5.Enabled = false;//设置关闭定时刷新按钮不可用

            timer1.Enabled = false;//设置定时器不可用
            timer1.Interval = 5000;//设置定时刷新时间为5s

            listView1.View = View.Details;//视图
            listView1.GridLines = true;//网格线
            ColumnHeader ch;//定义一个列标题
            ch = new ColumnHeader();//创建一个列标题

            ch.Text = "记录编号";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "使用仪器编号";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "光照度值";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "测量时间";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 4;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            try
            {
                string queryStr = "select * from 测量记录表 order by 记录编号 desc";//查询获取所有测量记录并按记录编号降序排列
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

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                //对串口参数进行设置并打开串口
                serialPort1.PortName = comboBox1.Text;//设置使用的串口
                serialPort1.ReceivedBytesThreshold = 8;//串口每收到8个字节数据则触发串口接收数据事件函数serialPort1_DataReceived()
                serialPort1.Open();
                serialPort1.Write("OK");

                button1.Enabled = false;
                button2.Enabled = true;
                comboBox1.Enabled = false;

                //对实时温度监测信息区的显示进行设置
                label3.ForeColor = Color.Coral;//恢复温度值显示标签的字体颜色为黑色
                label3.Text = "光照强度：";
                label4.Visible = true;
                label4.Text = "仪器编号：";
                label5.Visible = true;
                label5.Text = "测量时间：";
                label6.Visible = true;
                label6.Text = "监测点名称：";
                label7.Visible = true;
                label7.Text = "光照强度：";
                label8.Visible = true;
                label8.Text = "仪器编号：";
                label9.Visible = true;
                label9.Text = "测量时间：";
                label10.Visible = true;
                label10.Text = "监测点名称：";
                label11.Visible = true;
                label11.Text = "光照强度：";
                label12.Visible = true;
                label12.Text = "仪器编号：";
                label13.Visible = true;
                label13.Text = "测量时间：";
                label14.Visible = true;
                label14.Text = "监测点名称：";
                label16.Visible = true;
                label16.Text = "光照强度：";
                label17.Visible = true;
                label17.Text = "仪器编号：";
                label18.Visible = true;
                label18.Text = "测量时间：";
                label15.Visible = true;
                label15.Text = "监测点名称：";

                button3.Enabled = true;//设置5s定时刷新按钮可用
                MessageBox.Show("开启数据监测！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                //8.串口操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //读取串口接收到的全部数据
            string rd = serialPort1.ReadExisting();
            //判断接收的数据包是否为单片机发送的温度测量值数据包或者温度上限值数据包，如果是进行处理
            //如果是一个完整的温度测量值数据包(SxxxxxxE)，即数据包长度为8且第一个字符为S，最后一个字符为E
            Control.CheckForIllegalCrossThreadCalls = false;//禁止跨线程调用控件警告提示
            if ((rd.Length == 8) && (rd.Substring(0, 1).Equals("S")) && (rd.Substring(rd.Length - 1, 1).Equals("E")))
            {
                //提取数据包中的监测仪器编号
                string yqbh;
                yqbh = rd.Substring(1, 2);//字符数据1-2位位光照度监测仪器编号

                if (yqbh.Equals("01"))
                {
                    string gzd;
                    gzd = rd.Substring(3, 4);
                    //显示
                    label3.Text = "光照强度：" + gzd + ""; ;//显示监测仪器编号
                    label4.Text = "仪器编号：" + yqbh + ""; ;//显示光照度值
                    label5.Text = "测量时间：" + DateTime.Now.ToString();//显示测量时间

                    try
                    {
                        string queryStr = "select * from 监测点信息表 where 使用仪器编号='" + yqbh + "' ";
                        MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                        DataTable dt1 = new DataTable(); 
                        myDap.Fill(dt1); 
                        label6.Text = "监测点名称：" + dt1.Rows[0][1].ToString();
                        string insertStr = "insert into 测量记录表(监测点编号,光照度值,测量时间) values('" + dt1.Rows[0][0].ToString() + "'," + gzd + ",'" + DateTime.Now.ToString() + "');"; //写入监测数据的SQL语句
                        MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon); 
                        cmd.ExecuteNonQuery();        
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                }
                if (yqbh.Equals("02"))
                {
                    string gzd;
                    gzd = rd.Substring(3, 4);
                    //显示
                    label7.Text = "光照强度：" + gzd + ""; ;//显示监测仪器编号
                    label8.Text = "仪器编号：" + yqbh + ""; ;//显示光照度值
                    label9.Text = "测量时间：" + DateTime.Now.ToString();//显示测量时间

                    try
                    {
                        string queryStr = "select * from 监测点信息表 where 使用仪器编号='" + yqbh + "' ";
                        MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                        DataTable dt1 = new DataTable();
                        myDap.Fill(dt1);
                        label10.Text = "监测点名称：" + dt1.Rows[0][1].ToString();
                        string insertStr = "insert into 测量记录表(监测点编号,光照度值,测量时间) values('" + dt1.Rows[0][0].ToString() + "'," + gzd + ",'" + DateTime.Now.ToString() + "');"; //写入监测数据的SQL语句
                        MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon);
                        cmd.ExecuteNonQuery();
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                }
                if (yqbh.Equals("03"))
                {
                    string gzd;
                    gzd = rd.Substring(3, 4);
                    //显示
                    label11.Text = "光照强度：" + gzd + ""; ;//显示监测仪器编号
                    label12.Text = "仪器编号：" + yqbh + ""; ;//显示光照度值
                    label13.Text = "测量时间：" + DateTime.Now.ToString();//显示测量时间

                    try
                    {
                        string queryStr = "select * from 监测点信息表 where 使用仪器编号='" + yqbh + "' ";
                        MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                        DataTable dt1 = new DataTable();
                        myDap.Fill(dt1);
                        label14.Text = "监测点名称：" + dt1.Rows[0][1].ToString();
                        string insertStr = "insert into 测量记录表(监测点编号,光照度值,测量时间) values('" + dt1.Rows[0][0].ToString() + "'," + gzd + ",'" + DateTime.Now.ToString() + "');"; //写入监测数据的SQL语句
                        MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon);
                        cmd.ExecuteNonQuery();
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                }
                if (yqbh.Equals("04"))
                {
                    string gzd;
                    gzd = rd.Substring(3, 4);
                    //显示
                    label16.Text = "光照强度：" + gzd + ""; ;//显示监测仪器编号
                    label17.Text = "仪器编号：" + yqbh + ""; ;//显示光照度值
                    label18.Text = "测量时间：" + DateTime.Now.ToString();//显示测量时间

                    try
                    {
                        string queryStr = "select * from 监测点信息表 where 使用仪器编号='" + yqbh + "' ";
                        MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon);
                        DataTable dt1 = new DataTable();
                        myDap.Fill(dt1);
                        label15.Text = "监测点名称：" + dt1.Rows[0][1].ToString();
                        string insertStr = "insert into 测量记录表(监测点编号,光照度值,测量时间) values('" + dt1.Rows[0][0].ToString() + "'," + gzd + ",'" + DateTime.Now.ToString() + "');"; //写入监测数据的SQL语句
                        MySqlCommand cmd = new MySqlCommand(insertStr, 登录窗体.myCon);
                        cmd.ExecuteNonQuery();
                    }
                    catch (Exception err)
                    {
                        MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    }
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            button4.Enabled = false;//设置手动刷新按钮不可用
            button3.Enabled = false;//设置3s定时刷新按钮不可用
            button5.Enabled = true;//设置关闭定时刷新按钮可用
                                   //2.设置定时器有效
            timer1.Enabled = true; 
            MessageBox.Show("开启5s定时刷新！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            button4.Enabled = true;//设置手动刷新按钮可用
            button5.Enabled = false;//设置关闭定时刷新按钮不可用
            timer1.Enabled = false;//设置定时器不可用

            try
            {
                string queryStr = "select * from 测量记录表 order by 记录编号 desc"; //查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, 登录窗体.myCon); 
                DataTable dt = new DataTable();
                myDap.Fill(dt); 
                listView1.Items.Clear();
                ListViewItem listItem = null;
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

        private void timer1_Tick(object sender, EventArgs e)
        {
            //本事件函数在定时器生效后（timer1.Enable=true）每隔5s被调用1次(因为在窗体打开事件中设置了timer1.Interval=5000）
            try
            {
                string queryStr = "select * from 测量记录表 order by 记录编号 desc"; //查询获取所有测量记录并按记录编号降序排列
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
            }
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void 历史数据管理ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            历史数据管理 f = new 历史数据管理();
            f.Show();      
            this.Dispose();
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }
    }
}
