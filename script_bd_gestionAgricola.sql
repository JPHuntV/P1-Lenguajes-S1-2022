create database gestionAgricola;
use gestionAgricola;
create table Productos
(
	idProducto varchar(10) primary key,
    nombre varchar(25) not null,
    costo int not null,
    impuestoAplicado float not null
);

create table Areas
(
	idArea int primary key auto_increment,
    nombre varchar(25) not null,
    dimension float not null,
    prodPrincipal varchar(25) not null
);

create table Empleados
(
	cedula int primary key,
    nombre varchar(25) not null,
    apellido1 varchar(25) not null,
    apellido2 varchar(25) not null,
    labor varchar(30) not null,
    salarioMensual float not null,
    salarioCargasSociales float not null
);

DROP procedure IF EXISTS `insertProducto`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertProducto` (in pIdProducto varchar(10) , in pNombre varchar(25), in pCosto int, in pImpuestoAplicado float)
BEGIN
	insert into Productos (idProducto, nombre, costo, impuestoAplicado)
		values(pIdProducto, pNombre, pCosto, pImpuestoAplicado);
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertArea`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertArea` (in pNombre varchar(25),in pDimension float, in pProdPrincipal varchar(25))
BEGIN
	insert into Areas (nombre, dimension, prodPrincipal)
		values(pNombre, pDimension, pProdPrincipal);
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertEmpleado`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertEmpleado` (in pCedula int, in pNombre varchar(25), in pApellido1 varchar(25), in pApellido2 varchar(25),
									in pLabor varchar(25), in pSalarioMensual float, in pSalCargasSoc float)
BEGIN
	insert into Empleados (cedula, nombre, apellido1, apellido2, labor, salarioMensual, salarioCargasSociales)
		values(pCedula, pNombre, pApellido1, pApellido2, pLabor, pSalarioMensual, pSalCargasSoc);
END$$

DELIMITER ;


DROP procedure IF EXISTS `getAllAreas`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllAreas` ()
BEGIN
		select * from Areas;
END$$

DELIMITER ;

DROP procedure IF EXISTS `getAllEmpleados`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllEmpleados` ()
BEGIN
		select * from Empleados;
END$$

DELIMITER ;
/*
call insertArea('Area1', 153.000, 'productoA1');
call insertArea('Area2', 15.000, 'productoA2');
call insertArea('Area3', 26.40, 'productoA3');
call insertArea('Area4', 150.000, 'productoA4');
call insertArea('Area5', 895.450, 'productoA5');
call insertArea('Area6', 100.000, 'productoA6');
call insertArea('Area7', 185.000, 'productoA7');
call insertArea('Area8', 14.000, 'productoA8');
call insertArea('Area9', 1654.450, 'productoA9');
call insertArea('Area10', 415.000, 'productoA10');

call insertEmpleado(701234568, 'martin', 'app1','app22', 'secretario', 256.55, 8000);
call insertEmpleado(709874567, 'jose', 'app2','app23', 'carpintero', 256.55, 5456);
call insertEmpleado(701245879, 'maria', 'app13','app24', 'profesor', 256.55, 44874);
call insertEmpleado(621584479, 'pedro', 'app4','app25', 'director', 215.55, 6654);
call insertEmpleado(502154875, 'juan', 'app5','app26', 'secretario', 56.55, 5135);
call insertEmpleado(705223698, 'carlos', 'app6','app247', 'ingeniero', 6556.55, 8845);
call insertEmpleado(452125589, 'pepe', 'app7','app28', 'profesor', 856.55, 62154);
call insertEmpleado(965458565, 'sofia', 'app8','app29', 'secretario', 456.55, 88956);
call insertEmpleado(702800054, 'adrian', 'app9','app210', 'secretario', 966.55, 2215);*/