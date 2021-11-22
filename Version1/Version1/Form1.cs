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
    public partial class Form1 : Form
    {
        Socket server;
        string username;
        string password;
        public Form1()
        {
            InitializeComponent();
        }
        int iniciadoSesion = 0; //variable que es '0' si todavia no hemos iniciado sesion o '1' si ya hemos iniciado sesion.
        private void button1_Click(object sender, EventArgs e) //crear conexion con el servidor
        {
            IPAddress direc = IPAddress.Parse("192.168.56.101");
            IPEndPoint ipep = new IPEndPoint(direc, 9060);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

            }
            catch (SocketException ex)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }


        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (iniciadoSesion == 1)
            {
                if (Tiempo.Checked)//peticion para saber el tiempo jugado
                {
                    string mensaje = "2/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                    MessageBox.Show(mensaje);
                }
                else if (Victorias.Checked)//peticion para saber el numero de victorias
                {
                    string mensaje = "3/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
                   // string texto = "Ha ganado: " + mensaje + " veces.";
                    MessageBox.Show(mensaje);

                }
                if (Top3.Checked)//top 3 jugadores de la base de datos
                {
                    // Enviamos nombre y altura
                    string mensaje = "4/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Recibimos la respuesta del servidor
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('.')[0];
                    MessageBox.Show(mensaje);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('.')[1];
                    MessageBox.Show(mensaje);
                    mensaje = Encoding.ASCII.GetString(msg2).Split('.')[2];
                    MessageBox.Show(mensaje);
                }
            }
            else
                MessageBox.Show("Porfavor, inicie session.");


        }

        private void button3_Click(object sender, EventArgs e)//hacer el log in
        {
            // Enviamos nombre y password
            string mensaje = "1/" + Username.Text + "/" + Password.Text;
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            if (Convert.ToInt32(mensaje)==0)
            {
                MessageBox.Show("El username o la contraseña son incorrectos");
            }
            else
            {
                MessageBox.Show("Se ha iniciado sesión con exito");
                iniciadoSesion = 1;
            }
        }

        private void button4_Click(object sender, EventArgs e)//desconectarse del servidor
        {
            //Mensaje de desconexión
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            username = Username.Text;
            password = Password.Text;
            // Enviamos nombre y password
            string mensaje = "5/" + Username.Text + "/" + Password.Text;
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            if (Convert.ToInt32(mensaje)==0)
            {
                MessageBox.Show("El usuario se ha registrado.");
            }
            else
            {
                MessageBox.Show("No se ha registrado correctamente.");
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (iniciadoSesion==1)
            {
                Form2 listaConectados = new Form2();
                listaConectados.setSocket(server);
                listaConectados.Show();
            }
            else
            {
                MessageBox.Show("Por favor, inicie sessión o registrese.");
            }

        }
    }
}
