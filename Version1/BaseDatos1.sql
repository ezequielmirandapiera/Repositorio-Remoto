DROP DATABASE IF EXISTS group3;
CREATE DATABASE group3;

USE group3;

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
	skin VARCHAR(20),
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
INSERT INTO jugador VALUES(1,'victorino','mario');
INSERT INTO jugador VALUES(2,'polete04','luigi');
INSERT INTO participacion VALUES(1,1,45,1);
INSERT INTO participacion VALUES(2,1,50,2);
INSERT INTO participacion VALUES(1,2,63,2);
INSERT INTO participacion VALUES(2,2,47,1);



