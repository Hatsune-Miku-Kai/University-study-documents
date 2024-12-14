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


namespace TemperatureMonitoringSystem
{
    public partial class 系统主界面窗体 : Form
    {
        public 系统主界面窗体()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void 系统主界面窗体_Load(object sender, EventArgs e)
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
            button1.Enabled = true;//设置启动数据监测按钮可用
            button2.Enabled = false;//设置关闭数据监测按钮不可用
            label4.Visible = false;//隐藏测量时间显示标签
            label5.Visible = false;//隐藏温度上限值显示标签
            label3.ForeColor = Color.Red;//设置温度值显示标签的字体颜色为红色
            label3.Text = "数据监测未启动";//设置温度值显示标签的内容为“数据监测未启动”
            comboBox2.Visible = false;//隐藏温度上限值组合框
            button3.Visible = false;//隐藏温度上限值设置按钮
            label6.ForeColor = Color.Red;//设置温度上限值设置标签的字体颜色为红色
            label6.Text = "数据监测未启动";//设置温度上限值设置标签的内容为“数据监测未启动”
            label6.Location = new Point(7, 28);//设置温度上限值设置标签的位置
            button4.Enabled = true;//设置手动刷新按钮可用
            button5.Enabled = false;//设置3s定时刷新按钮不可用
            button6.Enabled = false;//设置关闭定时刷新按钮不可用
            timer1.Enabled = false;//设置定时器不可用
            timer1.Interval = 3000;//设置定时刷新时间为3s
            listView1.View = View.Details;//视图
            listView1.GridLines = true;//网格线

            ColumnHeader ch;//定义一个列标题
            ch = new ColumnHeader();//创建一个列标题

            ch.Text = "记录编号";//设置列标题内容            
            ch.Width = (listView1.Width - 20) / 3;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "温度值";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 3;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列

            ch.Text = "测量时间";//设置列标题内容
            ch.Width = (listView1.Width - 20) / 3;//设置列宽，总宽度减去垂直滚动条宽度后各列等分剩余宽度
            ch.TextAlign = HorizontalAlignment.Center;//设置单元格水平对齐方式
            listView1.Columns.Add((ColumnHeader)ch.Clone());//在listView1中添加1个列
            try
            {
                string queryStr = "select * from jcjlb order by jlbh desc";//查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, Form1.myCon);//执行SQL语句
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
            //6.如果操作数据库出现错误，弹出对话框提示
            catch (Exception err)
            {
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);//提示信息的对话框
            }
        }

        private void 系统主界面窗体_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("你确定要退出系统吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK) //若确定关闭窗体
            {
                this.Dispose(); //关闭本窗体并释放资源
                Application.Exit(); //退出程序
            }
            //2.若取消关闭窗体
            else
            {
                e.Cancel = true; //取消关闭窗体
            }
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label7_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBox1.Text;//设置使用的串口
                serialPort1.ReceivedBytesThreshold = 6;//串口每收到6个字节数据（SDD.DA或SDD.DB）则触发串口接收数据事件函数serialPort1_DataReceived()
                serialPort1.Open();//打开串口
             //2.向单片机发送字符‘A’，表示启动了上位机程序，要求单片机发送设置的温度上限值
                serialPort1.Write("A");
                button1.Enabled = false;//设置启动数据监测按钮不可用
                button2.Enabled = true;//设置停止数据监测按钮可用
                comboBox1.Enabled = false;//设置选择串口列表框不可用
                label3.ForeColor = Color.Black;//恢复温度值显示标签的字体颜色为黑色
                label3.Text = "温度值：";//恢复温度值显示标签的内容为“温度值：”
                label4.Visible = true;//恢复显示测量时间显示标签
                label4.Text = "测量时间：";//恢复温度值显示标签的内容为“温度值：”
                label5.Visible = true;//恢复显示温度上限值显示标签
                label5.Text = "温度上限值：";//恢复温度值显示标签的内容为“温度值：”
                label6.ForeColor = Color.Black;//恢复温度上限值设置标签的字体颜色为黑色
                label6.Text = "温度上限值：";//恢复温度上限值设置标签的内容为“温度上限值：”
                label6.Location = new Point(10, 43);//设置温度上限值设置标签的位置
                comboBox2.Visible = true;//恢复显示温度上限值组合框
                comboBox2.SelectedIndex = 9;//设置默认温度上限值为10度
                button3.Visible = true;//恢复显示温度上限值设置按钮
                button5.Enabled = true;//设置3s定时刷新按钮可用                       
                                       //7.成功启动，弹出对话框进行提示
                MessageBox.Show("开启数据监测！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                //8.串口操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                //1.关闭串口
                serialPort1.Close();
                comboBox1.Enabled = true;//设置选择串口组合框可用
                button1.Enabled = true;//设置启动数据监测按钮可用
                button2.Enabled = false;//设置停止数据监测按钮不可用                
                label3.ForeColor = Color.Red;//设置温度值显示标签的字体颜色为红色
                label3.Text = "温度监测未启动";//设置温度值显示标签的内容为“数据监测未启动”
                label4.Visible = false;//隐藏测量时间显示标签
                label5.Visible = false;//隐藏温度上限值显示标签
                label6.ForeColor = Color.Red;//设置温度上限值设置标签的字体颜色为红色
                label6.Text = "温度监测未启动";//设置温度上限值设置标签的内容为“数据监测未启动”
                label6.Location = new Point(7, 28); //设置温度上限值设置标签的位置
                comboBox2.Visible = false;//隐藏温度上限值组合框
                button3.Visible = false;//隐藏温度上限值设置按钮
                button4.Enabled = true;//设置手动刷新按钮可用
                button5.Enabled = false;//设置3s定时刷新按钮不可用
                button6.Enabled = false;//设置关闭定时刷新按钮不可用
                timer1.Enabled = false;//设置定时器不可用
                                       //6.成功停止数据监测，弹出对话框进行提示
                MessageBox.Show("停止温度监测！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                //7.串口操作出现错误，弹出对话框进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }


        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            //1.读取串口接收到的全部数据
            string rd = serialPort1.ReadExisting();
            //2.判断接收的数据包是否为单片机发送的温度测量值数据包或者温度上限值数据包，如果是进行处理
            //2.1如果是一个完整的温度测量值数据包(SDD.DA)，即数据包长度为6且第一个字符为S，最后一个字符为A
            Control.CheckForIllegalCrossThreadCalls = false;//禁止跨线程调用控件警告提示
            if ((rd.Length == 6) && (rd.Substring(0, 1).Equals("S")) && (rd.Substring(rd.Length - 1, 1).Equals("A")))
            {
                //2.1.1提取数据包中的温度值
                string temperature;
                if (rd.Substring(1, 1).Equals("0"))//如果十位为0，则丢弃十位，获取D.D（SDD.DA）
                {
                    temperature = rd.Substring(2, 3);//从第2个字符开始，获取长度为3的字符子串D.D                   
                }
                else//如果十位不为0，则获取DD.D（SDD.DA）
                {
                    temperature = rd.Substring(1, 4);//从第1个字符开始，获取长度为4的字符子串DD.D
                }
                label3.Text = "温度值：" + temperature + "℃";//显示温度测量值
                label4.Text = "测量时间：" + DateTime.Now.ToString();//显示测量时间
                                                                //2.1.3将温度测量记录存入数据库
                try
                {
                    string insertStr = "insert into jcjlb(wdz,clsj) values(" + temperature + ",'" + DateTime.Now.ToString() + "')"; //写入温度测量值的SQL语句
                    MySqlCommand cmd = new MySqlCommand(insertStr, Form1.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句        
                }
                catch (Exception err)
                {
                    MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                }
            }
            //2.2如果是一个完整的温度测量值数据包(SDD.DB)，即数据包长度为6且第一个字符为S，最后一个字符为B
            if ((rd.Length == 6) && (rd.Substring(0, 1).Equals("S")) && (rd.Substring(rd.Length - 1, 1).Equals("B")))
            {
                //2.2.1提取数据包中的温度上限值
                string temLimit;
                if (rd.Substring(1, 1).Equals("0"))//如果十位为0，则丢弃十位，获取D.D（SDD.DB）
                {
                    temLimit = rd.Substring(2, 3);//从第2个字符开始，获取长度为3的字符子串D.D
                }
                else//如果十位不为0，则获取DD.D（SDD.DB）
                {
                    temLimit = rd.Substring(1, 4);//从第1个字符开始，获取长度为4的字符子串DD.D
                }
                label5.Text = "温度上限值：" + temLimit + "℃";//显示温度上限值
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                //1.构造发送的温度上限值数据包，约定的格式为SDDC
                string sendAla = "";//定义要发送的字符串
                if (comboBox2.Text.Length == 1) sendAla = "S0" + comboBox2.Text + "C";//约定的发送给单片机的数据包格式为SDDC，如果设置的温度上限值小于10，根据组合框的值构造数据包
                else sendAla = "S" + comboBox2.Text + "C";//约定的发送给单片机的数据包格式为SDDC，如果设置的温度上限值大于等于10，根据组合框的值构造数据包
                                                          //2.通过串口向单片机发送温度上限值数据包（格式为SDDC）
                serialPort1.Write(sendAla);
                //3.显示新设置的温度上限值
                label5.Text = "温度上限值：" + comboBox2.Text + "℃";
                //4.提示温度上限值设置成功
                MessageBox.Show("设置温度上限值成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception err)
            {
                //5.如果串口操作出现错误进行提示
                MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            button4.Enabled = true;//设置手动刷新按钮可用
            button6.Enabled = false;//设置关闭定时刷新按钮不可用
            timer1.Enabled = false;//设置定时器不可用
            try
            {
                string queryStr = "select * from jcjlb order by jlbh desc"; //查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, Form1.myCon); //执行SQL语句
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

        private void timer1_Tick(object sender, EventArgs e)
        {
            //1.本事件函数在定时器生效后（timer1.Enable=true）每隔3s被调用1次(因为在窗体打开事件中设置了timer1.Interval=3000）
            try
            {
                string queryStr = "select * from jcjlb order by jlbh desc"; //查询获取所有测量记录并按记录编号降序排列
                MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, Form1.myCon); //执行SQL语句
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

        private void button5_Click(object sender, EventArgs e)
        {
            //1.设置历史数据刷新操作相关按钮状态
            button4.Enabled = false;//设置手动刷新按钮不可用
            button5.Enabled = false;//设置3s定时刷新按钮不可用
            button6.Enabled = true;//设置关闭定时刷新按钮可用
                                   //2.设置定时器有效
            timer1.Enabled = true;
            //3.弹出对话框提示开启了3s定时刷新
            MessageBox.Show("开启3s定时刷新！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //1.设置历史数据刷新操作相关按钮状态
            button4.Enabled = true;//设置手动刷新按钮可用
            button5.Enabled = true;//设置3s定时刷新按钮可用
            button6.Enabled = false;//设置关闭定时刷新按钮不可用
                                    //2.设置定时器无效
            timer1.Enabled = false;
            //3.弹出对话框提示关闭了定时刷新
            MessageBox.Show("关闭定时刷新！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void 数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 清除所有测量数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //1.跳出对话框要求确认是否要清除所有测量记录
            if (MessageBox.Show("你确定要清除所有测量记录吗？", "提示", MessageBoxButtons.OKCancel) == DialogResult.OK)//若确定要清除所有测量记录
            {
                try
                {
                    string deleteStr = "delete from jcjlb"; //删除所有测量记录的SQL语句
                    MySqlCommand cmd = new MySqlCommand(deleteStr, Form1.myCon); //创建执行SQL语句的命令
                    cmd.ExecuteNonQuery(); //执行SQL语句
                                           //3.刷新历史记录显示
                    string queryStr = "select * from jcjlb order by jlbh desc"; //查询获取所有测量记录并按记录编号降序排列
                    MySqlDataAdapter myDap = new MySqlDataAdapter(queryStr, Form1.myCon); //执行SQL语句
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
                    //4.跳出对话框提示成功清除所有测量记录
                    MessageBox.Show("清除所有测量记录成功！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
                catch (Exception err)
                {
                    //5.如果操作出现错误，弹出对话框进行提示
                    MessageBox.Show(err.ToString(), "错误", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                }
            }

        }

        private void chakToolStripMenuItem_Click(object sender, EventArgs e)
        {
            查看和修改个人信息窗体 form = new 查看和修改个人信息窗体();//创建查看和修改个人信息窗体
            form.Show();//打开查看和修改个人信息窗体
        }

        private void groupBox2_Enter(object sender, EventArgs e)
        {

        }

        private void 修改密码ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            修改密码 from = new 修改密码();
            from.Show();
        }

        private void MenuStrip_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }
    }
}
