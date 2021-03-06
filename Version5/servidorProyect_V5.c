#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>

typedef struct{
	char nombre[20];
	int socket;
}Conectado;

typedef struct{
	Conectado conectados[100];
	int num;
} ListaConectados;

typedef struct{
	int id;
	int jugando; //es 1 si la partida se esta jugando y 0 si no.
	Conectado jugadores[10];
}Partida;

typedef Partida TablaPartidas[100];

ListaConectados miLista;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//problemas de acceso excluyente
int sockets[100];

int Pon (ListaConectados *lista, char nombre[20], int socket){
	//A?ade un nuevo conectado a la lista. Retorna 0 si lo
	//ha a?adido correctamente i -1 si no.
	if (lista->num==100)
		return -1; //no he podido a?adir conectado
	else{
		strcpy(lista->conectados[lista->num].nombre, nombre);
		lista->conectados[lista->num].socket=socket;
		lista->num++;
		return 0;
	}
}

int DamePosicion (ListaConectados *lista, char nombre[20]){
	//devuelve la posicin en la lista o -1 si el nombre no esta en la lista
	int i=0;
	int encontrado=0;
	while ((i<lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre,nombre)==0)
			encontrado=1;
		if(!encontrado)
			i=i+1;
	}
	if (encontrado)
		return i;
	else 
		return -1;
}


int DameSocket (ListaConectados *lista, char nombre[20]){
	//devuelve el cocket al que esta conectado el jugador o -1 si no esta en la lista.
	int i=0;
	int found=0;
	while(i<lista->num && !found)
	{
		if(strcmp(lista->conectados[i].nombre, nombre)==0)
			found=1;
		if(!found)
			i=i+1;
	}
	if(found)
		  return lista->conectados[1].socket;
	else
		return -1;
}

int Elimina(ListaConectados *lista, char nombre[20]){
	//Retorna 0 si elimina correctamente y -1 si ese usuario no est en la lista
	int pos=DamePosicion(lista,nombre);
	if(pos==-1)
		return -1;
	else{
		int i;
		for(i=pos; i< lista->num-1; i++)
		{
			lista->conectados[i] = lista->conectados[i+1];
			//strcpy(lista->conectados[i].nombre, lista->conectados[i+1].nombre);
			//lista->conectados[i].socket= lista->conectados[i+1].socket;
		}
		lista->num--;
		return 0;
	}
}

void DameConectados (ListaConectados *lista, char conectados [300]){
	//Pone en conectados los nombres de todos los conectados
	//separados por /. Primero pone el numero de conectados.Ejemplo:
	// "3/Juan/Maria/Pedro"
	sprintf(conectados, "%d", lista->num);
	printf("%d\n", lista->num);
	printf("%s\n",lista->conectados[0].nombre);
	int i=0;
	while(i<lista->num)
	{
		sprintf(conectados, "%s/%s",conectados, lista->conectados[i].nombre);
		printf("%s\n", conectados);
		i=i+1;
	}
}
	

//Si existe el usuario y la contrase?a es correcta devuelve un 1, si no devuelve 0.
int UsernameExist(char username[20], char password[20])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[150];
	int respuesta;
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn=mysql_real_connect(conn, "localhost","root","mysql","group3",0,NULL,0);
	if(conn==NULL){
		printf("error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	strcpy(consulta,"SELECT jugador.passwrd FROM (jugador) WHERE jugador.username='");
	strcat(consulta,username);
	strcat(consulta,"'");
	err=mysql_query(conn,consulta);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	resultado=mysql_store_result(conn);
	printf("el resultado es %f \n", resultado);
	row=mysql_fetch_row(resultado);
	char passwordReal[20];
	//printf("el row es %s\n", row[0]);
	if(row==NULL || row[0]==NULL)
	{
		printf("No existe un jugador con username: %s\n", username);
		respuesta=0;
	}
	else
	{
		strcpy(passwordReal, row[0]);
		if (strcmp(passwordReal, password)==0)
			respuesta=1;
		else
			respuesta=0;
	}
	printf("La respuesta es %d\n", respuesta);
	mysql_close(conn);
	
	return respuesta;
}



// Funcion que devuelve 0 si no hay informacion de este username o un valor con el tiempo jugado
int TiempoJugado(char username[20])
{
	// quiero saber el tiempo total jugado por el username.
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[150];
	int respuesta;
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn=mysql_real_connect(conn, "localhost","root","mysql","group3",0,NULL,0);
	if(conn==NULL){
		printf("error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	strcpy(consulta,"SELECT SUM(participacion.crono) FROM (jugador,participacion) WHERE jugador.username='");
	strcat(consulta,username);
	strcat(consulta,"' AND jugador.id=participacion.id_J");
	
	err=mysql_query(conn,consulta);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	if(row==NULL || row[0]==NULL)
	{
		printf("No existe un jugador con username: %s\n", username);
		respuesta=0;
	}
	else
		printf("Tiempo total jugado por %s es: %s", username, row[0]);
		respuesta=atoi(row[0]);
	mysql_close(conn);
	
	return respuesta;
}

//devuelve un numero entero que corresponde al numero de partidas ganadas por el username

int PartidasGanadas(char username[20])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	int victorias;
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn=mysql_real_connect(conn, "localhost","root","mysql","group3",0,NULL,0);
	if(conn==NULL){
		printf("error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	strcpy(consulta,"SELECT SUM(participacion.posicion) FROM (jugador,participacion) WHERE jugador.username='");
	strcat(consulta,username);
	strcat(consulta,"' AND jugador.id=participacion.id_J");
	strcat(consulta," AND participacion.posicion='1'");
	
	err=mysql_query(conn,consulta);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	if(row==NULL || row[0]==NULL)
		row[0]=0;
	else
		printf("Partidas ganadas por %s son: %s", username, row[0]);
	printf("El resultado de victorias es %s", row[0]);
	mysql_close(conn);
	victorias=atoi(row[0]);
	return victorias;
}


//Genera dos vectores, uno con las id de los 3 jugadores con mas victorias y otro con el numero de puntos de cada jugador

void Top3Jugadores(char ganadores[200])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta1[500];
	char consulta[500];
	char consulta2[500];
	int  numJUG;
	int  JUG1;
	int p1=0;
	int p2=0;
	int p3=0;
	int id1;
	int id2;
	int id3;
	
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn=mysql_real_connect(conn, "localhost","root","mysql","group3",0,NULL,0);
	if(conn==NULL){
		printf("error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	strcpy(consulta2,"Select MIN(id_J) FROM participacion");
	err=mysql_query(conn,consulta2);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	JUG1=atoi(row[0]);
	
	
	strcpy(consulta1,"Select MAX(id_J) FROM participacion");
	err=mysql_query(conn,consulta1);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	
	if(row!=NULL || row[0]!=NULL){
		
		int i = JUG1;
		char ichar [20];
		numJUG=atoi(row[0]);
		printf("Numero de jugadores %d\n", numJUG);
		while(i<=numJUG){
			strcpy(consulta,"SELECT SUM(participacion.posicion) FROM (jugador,participacion) WHERE jugador.id='");
			sprintf(ichar,"%d",i);
			strcat(consulta,ichar);
			strcat(consulta,"' AND jugador.id=participacion.id_J");
			strcat(consulta," AND participacion.posicion='1'");
			
			err=mysql_query(conn,consulta);
			if(err!=0){
				printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
				exit(1);
			}		
			resultado=mysql_store_result(conn);
			row=mysql_fetch_row(resultado);
			if(row==NULL)
				printf("No existe un jugador con ese id\n");
			else{
				if(row[0]==NULL)
					row[0]="0";
				int pts=atoi(row[0])*3;
				printf("puntos son %d\n",pts);
				int podio=0;
				if(pts>=p1){
					p3=p2;
					id3=id2;
					p2=p1;
					id2=id1;				
					p1=pts;
					id1=i;
				}
				else if(pts>=p2){
					p3=p2;
					id3=id2;
					p2=pts;
					id2=i;
				}
				else if(pts>=p3){
					p3=pts;
					id3=i;
				}
			}
			i=i+1;
		}
		printf("1ero: %i con %i puntos\n2ndo: %i con %i puntos\n3ero: %i con %i puntos\n:",id1,p1,id2,p2,id3,p3);
		i=0;
		while(i<3){
			sprintf(ganadores,"%d/%d/%d/%d/%d/%d/",id1,p1,id2,p2,id3,p3);
			i=i+1;
		}
	}
	else
	   printf("Faltan jugadores\n");
	mysql_close(conn);
}

//devuelve 0 si se ha registrado y -1 si ya esta registrado.
void Register(char username[20], char password[20], char result[1])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[500];
	char consulta1[500];
	char consulta2[500];
	int respuesta;
	int ultimoID;
	conn=mysql_init(NULL);
	if(conn==NULL){
		printf("error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	conn=mysql_real_connect(conn, "localhost","root","mysql","group3",0,NULL,0);
	if(conn==NULL){
		printf("error al inicializar la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	strcpy(consulta2,"Select MAX(id) FROM jugador");
	err=mysql_query(conn,consulta2);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}
	
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	if(row==NULL || row[0]==NULL)
		ultimoID=0;
	else
		ultimoID=atoi(row[0]);
	
	strcpy(consulta1,"SELECT * FROM (jugador) WHERE jugador.username='");
	strcat(consulta1,username);
	strcat(consulta1,"'");
	
	err=mysql_query(conn,consulta1);
	if(err!=0){
		printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
		exit(1);
	}	
	resultado=mysql_store_result(conn);
	row=mysql_fetch_row(resultado);
	int ultimoID1 = ultimoID + 1;
	char ultimoIDs[3];
	sprintf(ultimoIDs,"%d",ultimoID1);
	if(row==NULL || row[0]==NULL)
	{
		strcpy(consulta,"INSERT INTO jugador VALUES(");
		strcat(consulta,ultimoIDs);
		strcat(consulta,",'");
		strcat(consulta,username);
		strcat(consulta,"','");
		strcat(consulta,password);
		strcat(consulta,"');");
		strcpy(result, "0");
		printf("IDs %s, username %s, password %s.\n", ultimoIDs, username, password);
		err=mysql_query(conn,consulta);
		if(err!=0){
			printf("Error al consultar datos de la base %u %s.\n", mysql_errno(conn),mysql_error(conn));
			exit(1);
		}
	}
	else
	{
		strcpy(result, "1");
	}
	printf("La respuesta es %s", result);
	mysql_close(conn);
	
}

void *AtenderCliente(void *socket)
{
	int sock_conn;
	int *s;
	s= (int *) socket;
	sock_conn=*s;
	char peticion[1000];
	char respuesta[1000];
	int ret;
	//miLista.num=0;
	
	int terminar=0;
	while (terminar ==0)
	{
		// Ahora recibimos la petici?n
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que a?adirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		
		printf ("Peticion: %s\n",peticion);
		
		
		// vamos a ver que quieren
		char *p = strtok( peticion, "/");
		int codigo =  atoi (p);
		// Ya tenemos el c?digo de la petici?n
		char username[20];
		char password[20];
		
		if (codigo ==1) //Iniciamos sesion
		{
			p = strtok( NULL, "/");
			
			strcpy (username, p);
			
			p= strtok( NULL, "/");
			
			strcpy (password, p);
			int resultado= UsernameExist(username, password);
			printf ("Codigo: %d, Nombre: %s, password: %s, resultado %d\n", codigo, username, password, resultado);
			char answer[20];
			sprintf(answer, "1/%d", resultado);
			strcpy(respuesta, answer);
			if (resultado==1){
				pthread_mutex_lock( &mutex); //No interrumpas ahora
				int res=Pon(&miLista,username,sock_conn);
				if (res==-1)
					printf("La lista est? llena.\n");
				else
					printf("se ha a?adido a la lista.\n");
				char notificacion[300];
				char conectados[300];
				DameConectados(&miLista, conectados);
				printf("Mis conectados: %s.\n",conectados);
				sprintf(notificacion,"6/%s",conectados);
				printf("La notificacion de conectado es %s\n", notificacion);
				printf("El numero de conectados es %d\n", miLista.num);
				int j;
				for (j=0; j<miLista.num+1;j++)
				{
					write (sockets[j], notificacion, strlen(notificacion));
				}
				pthread_mutex_unlock( &mutex);
			}
		}
		
		if (codigo ==0){
			//peticion de desconexion
			terminar=1;
			pthread_mutex_lock(&mutex);
			int res= Elimina(&miLista,username);
			if (res==-1)
				printf("No esta en la lista.\n");
			else
				printf("Se ha eliminado correctamente.\n");
			char notificacion[300];
			char conectados[300];
			DameConectados(&miLista, conectados);
			printf("Mis conectados: %s.\n",conectados);
			sprintf(notificacion,"6/%s",conectados);
			printf("La notificacion de eliminacion es %s\n", notificacion);
			printf("El numero de conectados es %d\n", miLista.num);
			int j;
			for (j=0; j<miLista.num+1;j++)
			{
				write (sockets[j], notificacion, strlen(notificacion));
			}
			pthread_mutex_unlock(&mutex);
		}
		else if (codigo ==2) // peticion para saber el tiempo total jugado por el username
		{
			int tiempo=TiempoJugado(username);
			char mensaje[1000];
			if (tiempo==0){
				strcpy(mensaje,"2/El jugador no ha jugado aun");
				strcpy(respuesta,mensaje);						
			}
			else{
				sprintf(respuesta, "2/El jugador %s ha jugado %d minutos",username,tiempo);
			}
		}
		else if (codigo==3) //saber el numero de victorias por el username
		{
			int victorias=PartidasGanadas(username);
			sprintf(respuesta, "3/El jugador %s ha ganado %d veces.",username,victorias);			
		}
		else if (codigo==4)//saber el top 3 jugadores de la base de datos
		{
			char ganadores[200];
			Top3Jugadores(ganadores);
			printf("%s", ganadores);
			sprintf(respuesta, "4/%s",ganadores); 
			printf("La respuesta de top 3 es: %s\n", respuesta);
		}
		else if (codigo==5)//resgistrarse en la base de datos
		{
			p = strtok( NULL, "/");
			
			strcpy (username, p);
			
			p= strtok( NULL, "/");
			
			strcpy (password, p);
			char skin[20];
			char result[1];
			Register(username, password, result);
			sprintf(respuesta,"5/%s", result);
			printf("Respuesta %s\n", respuesta);
		}
		else if (codigo==6)//Se recibe una peticion de invitaci?n a los jugadores conectados.
		{
			char notificacion[30];
			sprintf(notificacion, "7/");
			int j;
			for (j=0; j<miLista.num+1;j++)
			{
				write (sockets[j], notificacion, strlen(notificacion));
			}
		}
		else if (codigo==7)// Respuesta a la peticion de invitacion si se acepta o no
		{
			char notificacion[300];
			char username[100];
			char YoN[100];
			p=strtok(NULL, "/");
			strcpy(YoN, p);
			p=strtok(NULL, "/");
			strcpy(username, p);
			sprintf(notificacion, "8/%s/%s/",username,YoN);
			printf("Se envia notificacion %s\n", notificacion);
			int j;
			for (j=0; j<miLista.num+1;j++)
			{
				write (sockets[j], notificacion, strlen(notificacion));//enviamos notificaci?n a todos los conectados.
			}
		}
		else if(codigo==8)
		{
			char notificacion[300];
			sprintf(notificacion, "9/");
			int j;
			for (j=0; j<miLista.num+1;j++)
			{
				write (sockets[j], notificacion, strlen(notificacion));//enviamos notificaci?n a todos los conectados.
			}
		}
		else if(codigo==9)
		{
			char notificacion[300];
			sprintf(notificacion, "10/");
			int j;
			for (j=0; j<miLista.num+1;j++)
			{
				write (sockets[j], notificacion, strlen(notificacion));//enviamos notificaci?n a todos los conectados.
			}
		}
		
		if (codigo !=0 && codigo <6)
		{
			
			printf ("Respuesta: %s\n", respuesta);
			// Enviamos respuesta
			write (sock_conn,respuesta, strlen(respuesta));
		}
	}
	// Se acabo el servicio para este cliente
	close(sock_conn); 
}

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creando socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// establecemos el puerto de escucha
	serv_adr.sin_port = htons(9060);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	pthread_t thread[100];
	// Bucle infinito
	for (i=0; i<100;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente
		pthread_create (&thread[i], NULL, AtenderCliente,&sockets[i]);
	}
}
