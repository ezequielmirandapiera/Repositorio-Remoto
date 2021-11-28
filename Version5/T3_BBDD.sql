DROP DATABASE IF EXISTS T3_BBDD;
CREATE DATABASE T3_BBDD;

USE T3_BBDD;

CREATE TABLE partida (
	id INT NOT NULL,
	fecha INT NOT NULL,
	hora INT NOT NULL,
	campo VARCHAR(20),
	PRIMARY KEY (id)
)ENGINE=InnoDB;

CREATE TABLE jugador (
	id INT NOT NULL,
	username VARCHAR(20),
	passwrd VARCHAR(20),
	PRIMARY KEY (id)
)ENGINE=InnoDB;

CREATE TABLE participacion (
	id_J INT,
	id_P INT,
	crono INT NOT NULL,
	posicion INT NOT NULL,
	FOREIGN KEY (id_J) REFERENCES jugador(id),
	FOREIGN KEY (id_P) REFERENCES partida(id)
)ENGINE=InnoDB;


INSERT INTO partida VALUES(1,120521,1022,'azul');
INSERT INTO partida VALUES(2,140521,922,'azul');
INSERT INTO jugador VALUES(1,'victorino',2324);
INSERT INTO jugador VALUES(2,'polete04',2525);
INSERT INTO jugador VALUES(3,'ezequiel',2527);
INSERT INTO jugador VALUES(4,'marcm',1111);
INSERT INTO participacion VALUES(1,1,45,1);
INSERT INTO participacion VALUES(2,1,50,2);
INSERT INTO participacion VALUES(1,2,63,2);
INSERT INTO participacion VALUES(2,2,47,1);
INSERT INTO participacion VALUES(3,1,67,3);
INSERT INTO participacion VALUES(3,2,67,4);
INSERT INTO participacion VALUES(4,1,70,4);
INSERT INTO participacion VALUES(4,2,54,3);



