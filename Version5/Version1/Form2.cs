using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace Version1
{
    public partial class Form2 : Form
    {
        Socket server;
        public Form2()
        {
            InitializeComponent();
        }

        public void setSocket(Socket server)
        {
            this.server = server;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            string mensaje = "6/";
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            string[] words = mensaje.Split('/');
            int num = Convert.ToInt32(words[0]);
            DataView.RowCount = num;
            DataView.ColumnCount = 2;
            int i = 0;
            while (i<num)
            {
                DataView.Rows[i].Cells[0].Value = words[i+1];
                i = i + 1;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
