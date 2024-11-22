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
    public partial class 监测点管理界面 : Form
    {
        public 监测点管理界面()
        {
            InitializeComponent();
            this.StartPosition = FormStartPosition.CenterScreen;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            查看监测点信息 f=new 查看监测点信息();
            f.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            修改监测点信息界面 f = new 修改监测点信息界面();
            f.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            添加监测点信息界面 f = new 添加监测点信息界面();
            f.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            删除监测点信息 f =new 删除监测点信息();
            f.Show();
        }

        private void 监测点管理界面_Load(object sender, EventArgs e)
        {

        }
    }
}
