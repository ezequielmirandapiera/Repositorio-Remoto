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
using System.Threading;

namespace Version1
{
    public partial class Form1 : Form
    {
        Socket server;
        Thread atender;
        delegate void DelegadoParaEscribir(string mensaje);
        delegate void DelegadoParaAceptar(string username, string YoN);
        string username;
        string password;


        public Form1()
        {
            InitializeComponent();
            //CheckForIllegalCrossThreadCalls = false; //Necesario para que los elementos de los formularios puedan
            //ser atendidos desde threads diferentes a los que los crearon.
        }
        int iniciadoSesion = 0; //variable que es '0' si todavia no hemos iniciado sesion o '1' si ya hemos iniciado sesion.
        int iniciadoConexion = 0; // variable que es '0' si no se ha iniciado la conexion con el servidor y '1' en caso contrario.
        
        int invitador = 0; // variable que sera 1 si has sido el invitador o 0 si eres el invitado.
        bool acepta = false; //Si todos han aceptado la partida.
        bool creacionPartida = false; //cuando el tiempo para crear la partida o alguien rechaze la partida deja de crearla.
        bool creada = false; //Si se ha creado o no la partida

        public void PonLista(string mensaje)
        {
            DataView.Rows.Clear();
            DataView.ColumnCount = 1;
            DataView.ColumnHeadersVisible = true;
            if (mensaje!=null)
            {
                char delimiter = '/';
                string[] division = mensaje.Split(delimiter);
                int i = 0;
                while (i < division.Length)
                {
                    DataView.Rows.Add(division[i]);
                    i = i + 1;

                }
                DataView.AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);
            }
        }
        private void AtenderServidor()
        {

            while (true)
            {
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                string[] trozos = Encoding.ASCII.GetString(msg2).Split('/');
                int codigo = Convert.ToInt32(trozos[0]);
                string mensaje;
                switch (codigo)
                {
                    case 1:
                        mensaje = trozos[1].Split('\0')[0];
                        if (Convert.ToInt32(mensaje) == 0)
                        {
                            MessageBox.Show("El username o la contraseña son incorrectos");
                        }
                        else
                        {
                            MessageBox.Show("Se ha iniciado sesión con exito");
                            iniciadoSesion = 1;
                        }
                        break;
                    case 2:
                        mensaje = trozos[1].Split('\0')[0];
                        MessageBox.Show(mensaje);

                        break;
                    case 3:
                        mensaje = trozos[1].Split('\0')[0];
                        MessageBox.Show(mensaje);

                        break;
                    case 4:
                        try
                        {
                            mensaje = trozos[1].Split('.')[0];
                            MessageBox.Show(mensaje);
                            mensaje = trozos[1].Split('.')[1];
                            MessageBox.Show(mensaje);
                            mensaje = trozos[1].Split('.')[2];
                            MessageBox.Show(mensaje);
                        }
                        catch (IndexOutOfRangeException)
                        {
                            MessageBox.Show("No hay suficiente información para poder hacer esta consulta.");
                        }

                        break;
                    case 5:
                        mensaje = trozos[1].Split('\0')[0];
                        if (Convert.ToInt32(mensaje) == 0)
                        {
                            MessageBox.Show("El usuario se ha registrado.");
                        }
                        else
                        {
                            MessageBox.Show("No se ha registrado correctamente.");
                        }
                        break;
                    case 6:
                        int longitud = trozos.Length;
                        int j = 3;
                        mensaje = trozos[2];
                        while (j < longitud)
                        {
                            mensaje = mensaje + "/" + trozos[j];
                            j = j + 1;
                        }
                        DelegadoParaEscribir delegado = new DelegadoParaEscribir(PonLista);
                        DataView.Invoke(delegado, new object[] { mensaje });
                        break;
                    case 7: //llega una petición de invitación.
                        if (invitador == 0) // Si no eres tu el que has invitado...
                        {
                            DialogResult dialogResult = MessageBox.Show(username + ", ¿quieres unirte a una partida?", "Invitación", MessageBoxButtons.YesNo);
                            if (dialogResult == DialogResult.Yes) // Se acepta la partida.
                            {
                                string answer = "7/SI/" + username;
                                byte[] msg = System.Text.Encoding.ASCII.GetBytes(answer);
                                server.Send(msg);
                            }
                            else if (dialogResult == DialogResult.No) // Se rechaza la partida.
                            {
                                string answer = "7/NO/" + username;
                                byte[] msg = System.Text.Encoding.ASCII.GetBytes(answer);
                                server.Send(msg);
                            }
                        }
                        break;
                    case 8:
                        if (invitador == 1) // El que ha enviado la invitación atentedá esta petición, el resto no.
                        {
                            string username = trozos[1];
                            string YoN = trozos[2];
                            if (YoN == "NO")
                            {
                                acepta = false; // Se rechaza la partida.
                            }
                            DelegadoParaAceptar delegado2 = new DelegadoParaAceptar(aceptarInvitacion);
                            GridInvitados.Invoke(delegado2, new object[] { username, YoN });
                        }
                        break;
                    case 9:
                        MessageBox.Show("No se ha podido crear la partida, los jugadores no han aceptado la partida.");
                        break;
                }
            }

        }

        public void aceptarInvitacion(string username, string YoN)
        {
            string row = username + " ha aceptado la invitación? " + YoN;
            GridInvitados.Rows.Add(row);
            GridInvitados.AutoResizeColumns(DataGridViewAutoSizeColumnsMode.AllCells);
            GridInvitados.ClearSelection();
        }

        private void button1_Click(object sender, EventArgs e) //crear conexion con el servidor
        {
            //IPAddress direc = IPAddress.Parse("147.83.117.22");
            //IPEndPoint ipep = new IPEndPoint(direc, 50057);
            IPAddress direc = IPAddress.Parse("192.168.56.101");
            IPEndPoint ipep = new IPEndPoint(direc, 9060);

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                iniciadoConexion = 1;
                MessageBox.Show("Conectado");

            }
            catch (SocketException ex)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }
            //creamos el thread
            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();
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
                }
                else if (Victorias.Checked)//peticion para saber el numero de victorias
                {
                    string mensaje = "3/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);
                }
                if (Top3.Checked)//top 3 jugadores de la base de datos
                {
                    // Enviamos nombre y altura
                    string mensaje = "4/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);
                }
            }
            else
                MessageBox.Show("Porfavor, inicie session.");


        }

        private void button3_Click(object sender, EventArgs e)//hacer el log in
        {

            if (iniciadoSesion == 0)
            {
                if (iniciadoConexion == 1)
                {
                    username = Username.Text;
                    password = Password.Text;
                    if (username.Length > 0 && password.Length > 0)
                    {
                        // Enviamos nombre y password
                        string mensaje = "1/" + Username.Text + "/" + Password.Text;
                        // Enviamos al servidor el nombre tecleado
                        byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                        server.Send(msg);
                    }
                    else
                        MessageBox.Show("Escriba un username y un password!!");
                }
                else
                    MessageBox.Show("Inicie conexión con el servidor!!");
            }
            else
            {
                MessageBox.Show("Ya se ha iniciado sesión");
            }

        }

        private void button4_Click(object sender, EventArgs e)//desconectarse del servidor
        {
            if (iniciadoConexion == 1)
            {
                //Mensaje de desconexión
                string mensaje = "0/";

                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                // Nos desconectamos
                DataView.Rows.Clear();
                atender.Abort();
                this.BackColor = Color.Gray;
                iniciadoConexion = 0;
                iniciadoSesion = 0;
                server.Shutdown(SocketShutdown.Both);
                server.Close();
            }
            else
                MessageBox.Show("Inicie conexión con el servidor!!");
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (iniciadoConexion == 1)
            {
                username = Username.Text;
                password = Password.Text;
                // Enviamos nombre y password
                string mensaje = "5/" + Username.Text + "/" + Password.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }
            else
                MessageBox.Show("Inicie conexión con el servidor!!");
        }

        private void DataView_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int k = e.RowIndex;
            int r = e.ColumnIndex;
            string invitado = Convert.ToString(DataView.Rows[k].Cells[r].Value);
            // Enviamos nombre y password
            string mensaje = "6/" + invitado;
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
        }

        private void invitacion_Click(object sender, EventArgs e)
        {
            clock.Start();
            invitador = 1;
            acepta = true;
            creacionPartida = true;
            time.Text = "40";
            //enviamos invitación
            string mensaje = "6/";
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            GridInvitados.Rows.Clear();
            GridInvitados.ColumnCount = 1;
            GridInvitados.GridColor = Color.Yellow;

            DelegadoParaAceptar delegado = new DelegadoParaAceptar(aceptarInvitacion);
            GridInvitados.Invoke(delegado, new object[] { username, "SI" });
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            clock.Interval = 1000;
        }
        private void clock_Tick(object sender, EventArgs e)
        {
            int t = Convert.ToInt32(time.Text);
            t = t - 1;
            time.Text = Convert.ToString(t);

            if (t == 0)
            {
                clock.Stop();
                creacionPartida = false; 
                invitador = 0; 
                if (acepta == false)
                {
                    // No se crea la partida. Avisar a todos los usuarios.
                    string mensaje = "8/";
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);
                }
                else if (acepta == true)
                {
                    // Se crea la partida y, por lo tanto, se abren los tableros en todos los usuarios.
                    string mensaje = "9/";
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);
                }
            }
        }
    }
}
