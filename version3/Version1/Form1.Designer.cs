
namespace Version1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador necesaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén usando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido de este método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.button1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.Username = new System.Windows.Forms.TextBox();
            this.Password = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.Tiempo = new System.Windows.Forms.RadioButton();
            this.Victorias = new System.Windows.Forms.RadioButton();
            this.Top3 = new System.Windows.Forms.RadioButton();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.DataView = new System.Windows.Forms.DataGridView();
            this.invitacion = new System.Windows.Forms.Button();
            this.GridInvitados = new System.Windows.Forms.DataGridView();
            this.clock = new System.Windows.Forms.Timer(this.components);
            this.time = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.DataView)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridInvitados)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(25, 21);
            this.button1.Margin = new System.Windows.Forms.Padding(2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(95, 32);
            this.button1.TabIndex = 0;
            this.button1.Text = "INICIAR";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(39, 78);
            this.label1.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "USERNAME";
            // 
            // Username
            // 
            this.Username.Location = new System.Drawing.Point(25, 100);
            this.Username.Margin = new System.Windows.Forms.Padding(2);
            this.Username.Name = "Username";
            this.Username.Size = new System.Drawing.Size(96, 20);
            this.Username.TabIndex = 2;
            // 
            // Password
            // 
            this.Password.Location = new System.Drawing.Point(25, 163);
            this.Password.Margin = new System.Windows.Forms.Padding(2);
            this.Password.Name = "Password";
            this.Password.Size = new System.Drawing.Size(96, 20);
            this.Password.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(37, 142);
            this.label2.Margin = new System.Windows.Forms.Padding(2, 0, 2, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(70, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "PASSWORD";
            // 
            // Tiempo
            // 
            this.Tiempo.AutoSize = true;
            this.Tiempo.Location = new System.Drawing.Point(255, 30);
            this.Tiempo.Margin = new System.Windows.Forms.Padding(2);
            this.Tiempo.Name = "Tiempo";
            this.Tiempo.Size = new System.Drawing.Size(95, 17);
            this.Tiempo.TabIndex = 5;
            this.Tiempo.TabStop = true;
            this.Tiempo.Text = "Tiempo jugado";
            this.Tiempo.UseVisualStyleBackColor = true;
            // 
            // Victorias
            // 
            this.Victorias.AutoSize = true;
            this.Victorias.Location = new System.Drawing.Point(255, 85);
            this.Victorias.Margin = new System.Windows.Forms.Padding(2);
            this.Victorias.Name = "Victorias";
            this.Victorias.Size = new System.Drawing.Size(119, 17);
            this.Victorias.TabIndex = 6;
            this.Victorias.TabStop = true;
            this.Victorias.Text = "Numero de victorias";
            this.Victorias.UseVisualStyleBackColor = true;
            // 
            // Top3
            // 
            this.Top3.AutoSize = true;
            this.Top3.Location = new System.Drawing.Point(255, 140);
            this.Top3.Margin = new System.Windows.Forms.Padding(2);
            this.Top3.Name = "Top3";
            this.Top3.Size = new System.Drawing.Size(141, 17);
            this.Top3.TabIndex = 7;
            this.Top3.TabStop = true;
            this.Top3.Text = "Top 3 mejores jugadores";
            this.Top3.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(269, 184);
            this.button2.Margin = new System.Windows.Forms.Padding(2);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(101, 27);
            this.button2.TabIndex = 8;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(25, 203);
            this.button3.Margin = new System.Windows.Forms.Padding(2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(95, 28);
            this.button3.TabIndex = 9;
            this.button3.Text = "Iniciar Sesión";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(277, 254);
            this.button4.Margin = new System.Windows.Forms.Padding(2);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(73, 27);
            this.button4.TabIndex = 10;
            this.button4.Text = "Salir";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(139, 203);
            this.button5.Margin = new System.Windows.Forms.Padding(2);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(90, 31);
            this.button5.TabIndex = 11;
            this.button5.Text = "Resgistrarse";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // DataView
            // 
            this.DataView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.DataView.Location = new System.Drawing.Point(475, 28);
            this.DataView.Margin = new System.Windows.Forms.Padding(2);
            this.DataView.Name = "DataView";
            this.DataView.RowHeadersWidth = 62;
            this.DataView.RowTemplate.Height = 28;
            this.DataView.Size = new System.Drawing.Size(265, 129);
            this.DataView.TabIndex = 13;
            this.DataView.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.DataView_CellClick);
            // 
            // invitacion
            // 
            this.invitacion.Location = new System.Drawing.Point(541, 163);
            this.invitacion.Name = "invitacion";
            this.invitacion.Size = new System.Drawing.Size(125, 25);
            this.invitacion.TabIndex = 14;
            this.invitacion.Text = "Invitar a jugar";
            this.invitacion.UseVisualStyleBackColor = true;
            this.invitacion.Click += new System.EventHandler(this.invitacion_Click);
            // 
            // GridInvitados
            // 
            this.GridInvitados.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GridInvitados.Location = new System.Drawing.Point(475, 254);
            this.GridInvitados.Name = "GridInvitados";
            this.GridInvitados.Size = new System.Drawing.Size(265, 95);
            this.GridInvitados.TabIndex = 15;
            // 
            // time
            // 
            this.time.AutoSize = true;
            this.time.Location = new System.Drawing.Point(581, 218);
            this.time.Name = "time";
            this.time.Size = new System.Drawing.Size(38, 13);
            this.time.TabIndex = 16;
            this.time.Text = "tiempo";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(831, 365);
            this.Controls.Add(this.time);
            this.Controls.Add(this.GridInvitados);
            this.Controls.Add(this.invitacion);
            this.Controls.Add(this.DataView);
            this.Controls.Add(this.button5);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.Top3);
            this.Controls.Add(this.Victorias);
            this.Controls.Add(this.Tiempo);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.Password);
            this.Controls.Add(this.Username);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button1);
            this.Margin = new System.Windows.Forms.Padding(2);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.DataView)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridInvitados)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Username;
        private System.Windows.Forms.TextBox Password;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.RadioButton Tiempo;
        private System.Windows.Forms.RadioButton Victorias;
        private System.Windows.Forms.RadioButton Top3;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.DataGridView DataView;
        private System.Windows.Forms.Button invitacion;
        private System.Windows.Forms.DataGridView GridInvitados;
        private System.Windows.Forms.Timer clock;
        private System.Windows.Forms.Label time;
    }
}

