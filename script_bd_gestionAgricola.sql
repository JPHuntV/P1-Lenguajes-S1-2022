create database gestionAgricola;
use gestionAgricola;
create table Productos
(
	idProducto varchar(10) primary key,
    nombre varchar(25) not null,
    costo int not null,
    impuestoAplicado float not null
);


DROP procedure IF EXISTS `insertProducto`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertProducto` (pIdProducto varchar(10), in pNombre varchar(25), in pCosto int, in pImpuestoAplicado float)
BEGIN
	insert into Productos (idProducto, nombre, costo, impuestoAplicado)
		values(pIdProducto, pNombre, pCosto, pImpuestoAplicado);
END$$

DELIMITER ;
