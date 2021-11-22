#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include<mysql.h>

//Si existe el usuario y la contraseņa es correcta devuelve un 1, si no devuelve 0.
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
	//printf("el resultado es %f", resultado);
	row=mysql_fetch_row(resultado);
	char passwordReal[20];
	printf("el row es %s", row[0]);
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
	printf("La respuesta es %d", respuesta);
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
	char consulta[150];
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

void Top3Jugadores(char ganadores[3], int puntos[3])
{
	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta1[150];
	char consulta[150];
	char consulta2[150];
	int  numJUG;
	int  JUG1;
	
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
			if(row[0]==NULL)
				row[0]="0";
			else{
				int podio=0;
				if((atoi(row[0])>=puntos[0]) && podio==0){
					ganadores[2]=ganadores[1];
					puntos[2]=puntos[1];
					ganadores[1]=ganadores[0];
					puntos[1]=puntos[0];
					ganadores[0]=i;
					puntos[0]=atoi(row[0]);	
					podio=1;
				}
				if((atoi(row[0])>=puntos[1]) && podio==0){
					ganadores[2]=ganadores[1];
					puntos[2]=puntos[1];
					ganadores[1]=i;
					puntos[1]=atoi(row[0]);	
					podio=1;
				}
				if((atoi(row[0])>=puntos[2]) && podio==0){
					ganadores[2]=i;
					puntos[2]=atoi(row[0]);
					podio=1;				
				}
				
			}
			i=i+1;
		}
		printf("1ero: %i con %i puntos\n2ndo: %i con %i puntos\n3ero: %i con %i puntos\n:",ganadores[0],puntos[0],ganadores[1],puntos[1],ganadores[2],puntos[2]);
	}
	else
	   printf("Faltan jugadores");
	mysql_close(conn);
}

//devuelve 0 si se ha registrado y -1 si ya esta registrado.
void Register(char username[20], char password[20], char skin[0], char result[1])
{

	MYSQL *conn;
	int err;
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	char consulta[150];
	char consulta1[150];
	char consulta2[150];
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
		strcat(consulta,"','");
		strcat(consulta,skin);
		strcat(consulta,"');");
		strcpy(result, "0");
		printf("IDs %s, username %s, password %s, skin %s", ultimoIDs, username, password, skin);
		err=mysql_query(conn,consulta);
		if(err!=0){
			printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn),mysql_error(conn));
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


int main(int argc, char *argv[])
{
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[1000];
	char respuesta[1000];
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
	serv_adr.sin_port = htons(9080);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	// Bucle infinito
	for (;;){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		int terminar =0;
		// Entramos en un bucle para atender todas las peticiones de este cliente
		//hasta que se desconecte
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
				printf("respuesta %d", resultado);
				printf ("Codigo: %d, Nombre: %s, password: %s, resultado %d\n", codigo, username, password, resultado);
				char answer[20];
				sprintf(answer, "%d", resultado);
				strcpy(respuesta, answer);
				
			}
			
			if (codigo ==0) //peticion de desconexion
				terminar=1;
			
			else if (codigo ==2) // peticion para saber el tiempo total jugado por el username
			{
				int tiempo=TiempoJugado(username);
				char mensaje[1000];
				if (tiempo==0){
					strcpy(mensaje,"El jugador no ha jugado aun");
					strcpy(respuesta,mensaje);						
				}
				else{
					sprintf(respuesta, "El jugador %s ha jugado %d minutos",username,tiempo);
				}
			}
			else if (codigo==3) //saber el numero de victorias por el username
			{
				int victorias=PartidasGanadas(username);
				sprintf(respuesta, "El jugador %s ha ganado %d veces.",username,victorias);			
			}
			else if (codigo==4)//saber el top 3 jugadores de la base de datos
			{
				char ganadores[3];
				int puntos[3];
				Top3Jugadores(ganadores, puntos);
				memset(respuesta,0,1000);
				sprintf(respuesta, "El jugador con mas puntos tiene id: %d y tiene %d puntos. El segundo jugador con mas puntos tiene id: %d y tiene %d puntos. El tercer jugador con mas puntos tiene id: %d y tiene %d puntos.", ganadores[0], puntos[0], ganadores[1], puntos[1], ganadores[2], puntos[2]);
				printf("La respuesta de top 3 es: %s", respuesta);
			}
			else if (codigo==5)//resgistrarse en la base de datos
			{
				p = strtok( NULL, "/");
				
				strcpy (username, p);
				
				p= strtok( NULL, "/");
				
				strcpy (password, p);
				char skin[20];
				printf(skin, "Mario");
				char result[1];
				Register(username, password, skin, result);
				strcpy(respuesta, result);
				printf("Respuesta %s", respuesta);
			}
				
				
			if (codigo !=0)
			{
				
				printf ("Respuesta: %s\n", respuesta);
				// Enviamos respuesta
				write (sock_conn,respuesta, strlen(respuesta));
			}
		}
		// Se acabo el servicio para este cliente
		close(sock_conn); 
	}
}
