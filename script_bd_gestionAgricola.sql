create database gestionAgricola;
use gestionAgricola;

create table Productos
(
	idProducto varchar(10) primary key,
    nombre varchar(25) not null,
    costo float not null,
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
    salarioMensual float not null
);

create table Usuarios
(
	idUsuario int auto_increment primary key,
    usuario varchar(30) unique not null,
    clave varchar(30) not null
);

create table ValoresIniciales
(
	cedulaJuridica int primary key,
    nombreComercio varchar(30) not null,
    telefono int not null,
    numeroSecSigFact int not null,
    porcentajeCargaSocial float not null
    
);

create table Nominas
(
	idNomina int primary key auto_increment,
    mes tinyint not null,
    anio smallint not null,
    subtotal float not null,
    total float not null
);

create table EmpleadoXNomina
(
	idEmpleadoXNomina int primary key auto_increment,
    cedulaEmpleado int,
    idNomina int,
    foreign key (cedulaEmpleado) references Empleados(cedula),
    foreign key (idNomina) references Nominas(idNomina)
);

create table Factura
(
	numeroFactura int primary key auto_increment,
    nombreLocal varchar(30) not null,
    cedulaJuridica int not null,
    telefono int not null,
    fecha date not null,
    cliente varchar (60),
    subtotal float not null,
    impuestoVenta float not null,
    total float not null
    
);

create table ProductoXFactura(

	idProductoXFactura int primary key auto_increment,
    idProducto varchar(10),
    numeroFactura int, 
    cantidad int not null,
    foreign key (idProducto) references Productos(idProducto),
    foreign key (numeroFactura) references Factura(numeroFactura)
);


DROP procedure IF EXISTS `insertProducto`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertProducto` (in pIdProducto varchar(10) , in pNombre varchar(25), in pCosto float, in pImpuestoAplicado float)
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
									in pLabor varchar(25), in pSalarioMensual float)
BEGIN
	insert into Empleados (cedula, nombre, apellido1, apellido2, labor, salarioMensual)
		values(pCedula, pNombre, pApellido1, pApellido2, pLabor, pSalarioMensual);
END$$

DELIMITER ;



DROP procedure IF EXISTS `insertNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertNomina` (in pMes tinyint, in pAnio smallint, in pSubtotal float, in pTotal float)
BEGIN
	insert into Nominas(mes, anio, subtotal, total)
		values(pMes, pAnio, pSubtotal, pTotal);
	select LAST_INSERT_ID();
END$$

DELIMITER ;



DROP procedure IF EXISTS `insertEmpleadoXNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertEmpleadoXNomina` (in pCedulaEmpleado int, in idNomina int)
BEGIN
	insert into EmpleadoXNomina(cedulaEmpleado, idNomina)
		values(pCedulaEmpleado, idNomina);
END$$

DELIMITER ;



DROP procedure IF EXISTS `insertFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertFactura` (in pNombreLocal varchar(30), in pCedulaJuridica int, in pTelefono int,
									in pFecha date, in pCliente varchar(60), in pSubtotal float,
                                    in pImpuestoVenta float, in pTotal float)
BEGIN
	insert into Factura(nombreLocal, cedulaJuridica, telefono, fecha,cliente, subtotal, impuestoVenta, total)
		values(pNombreLocal, pCedulaJuridica, pTelefono, pFecha,pCliente, pSubtotal, pImpuestoVenta, pTotal);
	select LAST_INSERT_ID();
END$$

DELIMITER ;




DROP procedure IF EXISTS `insertProductoXFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertProductoXFactura` (in pIdProducto varchar(10), in pNumeroFactura int, in pCantidad int)
BEGIN
	insert into ProductoXFactura(idProducto, numeroFactura, cantidad)
		values(pIdProducto, pNumeroFactura, pCantidad);
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




DROP procedure IF EXISTS `getUserByUsuario`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getUserByUsuario` (in pUsuario varchar(30), in pClave varchar(30))
BEGIN
		select * from Usuarios
        where usuario = pUsuario and clave = pClave;
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
DROP procedure IF EXISTS `getValoresIniciales`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getValoresIniciales` ()
BEGIN
		select * from ValoresIniciales;
END$$

DELIMITER ;



DROP procedure IF EXISTS `getAllNominas`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllNominas` ()
BEGIN
		select * from Nominas;
END$$

DELIMITER ;


DROP procedure IF EXISTS `getAllFacturas`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllFacturas` ()
BEGIN
		select * from Facturas;
END$$

DELIMITER ;

DROP procedure IF EXISTS `getAllProductos`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllProductos` ()
BEGIN
		select * from Productos;
END$$

DELIMITER ;




DROP procedure IF EXISTS `getEmpleadosByNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getEmpleadosByNomina` (in pIdNomina int)
BEGIN
		select * from Empleados e
        inner join EmpleadoXNomina en on e.cedula = en.cedulaEmpleado
        where idNomina = pIdNomina ;
END$$

DELIMITER ;


DROP procedure IF EXISTS `getProductosByFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getProductosByFactura` (in pIdFactura int)
BEGIN
		select * from Productos p
        inner join ProductoXFactura pf on p.idProducto = pf.idProducto
        where pf.numeroFactura = pIdFactura ;
END$$

DELIMITER ;




/************DDL
insert into Usuarios(usuario, clave)
values('Usuarioej1', 'contraseñaEj1'),
	('usuarioEj2','contraseñaEj2')


insert into ValoresIniciales(cedulaJuridica, nombreComercio, telefono, numeroSecSigFact, porcentajeCargaSocial)
values(356485698, 'Comercio de ejemplo 01', 85645587, 0,1.5);

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

call insertEmpleado(701234568, 'martin', 'app1','app22', 'secretario', 256.55);
call insertEmpleado(709874567, 'jose', 'app2','app23', 'carpintero', 256.55);
call insertEmpleado(701245879, 'maria', 'app13','app24', 'profesor', 256.55);
call insertEmpleado(621584479, 'pedro', 'app4','app25', 'director', 215.55);
call insertEmpleado(502154875, 'juan', 'app5','app26', 'secretario', 56.55);
call insertEmpleado(705223698, 'carlos', 'app6','app247', 'ingeniero', 6556.55);
call insertEmpleado(452125589, 'pepe', 'app7','app28', 'profesor', 856.55);
call insertEmpleado(965458565, 'sofia', 'app8','app29', 'secretario', 456.55);
call insertEmpleado(702800054, 'adrian', 'app9','app210', 'secretario', 966.55);*/create database gestionAgricola;
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
    salarioMensual float not null
);

create table Usuarios
(
	idUsuario int auto_increment primary key,
    usuario varchar(30) unique not null,
    clave varchar(30) not null
);

create table ValoresIniciales
(
	cedulaJuridica int primary key,
    nombreComercio varchar(30) not null,
    telefono int not null,
    numeroSecSigFact int not null,
    porcentajeCargaSocial float not null
    
);

create table Nominas
(
	idNomina int primary key auto_increment,
    mes tinyint not null,
    anio smallint not null,
    subtotal float not null,
    total float not null
);


create table EmpleadoXNomina
(
	idEmpleadoXNomina int primary key auto_increment,
    cedulaEmpleado int,
    idNomina int,
    foreign key (cedulaEmpleado) references Empleados(cedula),
    foreign key (idNomina) references Nominas(idNomina)
);

create table Factura
(
	numeroFactura int primary key auto_increment,
    nombreLocal varchar(30) not null,
    cedulaJuridica int not null,
    telefono int not null,
    fecha date not null,
    cliente varchar (60),
    subtotal float not null,
    impuestoVenta float not null,
    total float not null
    
);


create table ProductoXFactura(
	idProductoXFactura int primary key auto_increment,
    idProducto varchar(10),
    numeroFactura int, 
    cantidad int not null,
    foreign key (idProducto) references Productos(idProducto),
    foreign key (numeroFactura) references Factura(numeroFactura)
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
									in pLabor varchar(25), in pSalarioMensual float)
BEGIN
	insert into Empleados (cedula, nombre, apellido1, apellido2, labor, salarioMensual)
		values(pCedula, pNombre, pApellido1, pApellido2, pLabor, pSalarioMensual);
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertNomina` (in pMes tinyint, in pAnio smallint, in pSubtotal float, in pTotal float)
BEGIN
	insert into Nominas(mes, anio, subtotal, total)
		values(pMes, pAnio, pSubtotal, pTotal);
	select LAST_INSERT_ID();
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertEmpleadoXNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertEmpleadoXNomina` (in pCedulaEmpleado int, in idNomina int)
BEGIN
	insert into EmpleadoXNomina(cedulaEmpleado, idNomina)
		values(pCedulaEmpleado, idNomina);
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertFactura` (in pNombreLocal varchar(30), in pCedulaJuridica int, in pTelefono int,
									in pFecha date, in pCliente varchar(60), in pSubtotal float,
                                    in pImpuestoVenta float, in pTotal float)
BEGIN
	insert into Factura(nombreLocal, cedulaJuridica, telefono, fecha,cliente, subtotal, impuestoVenta, total)
		values(pNombreLocal, pCedulaJuridica, pTelefono, pFecha,pCliente, pSubtotal, pImpuestoVenta, pTotal);
	select LAST_INSERT_ID();
END$$

DELIMITER ;

DROP procedure IF EXISTS `insertProductoXFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `insertProductoXFactura` (in pIdProducto varchar(10), in pNumeroFactura int, in pCantidad int)
BEGIN
	insert into ProductoXFactura(idProducto, numeroFactura, cantidad)
		values(pIdProducto, pNumeroFactura, pCantidad);
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

DROP procedure IF EXISTS `getUserByUsuario`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getUserByUsuario` (in pUsuario varchar(30), in pClave varchar(30))
BEGIN
		select * from Usuarios
        where usuario = pUsuario and clave = pClave;
END$$

DELIMITER ;

DROP procedure IF EXISTS `getAllEmpleados`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllEmpleados` ()
BEGIN
		select * from Empleados;
END$$


DROP procedure IF EXISTS `getValoresIniciales`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getValoresIniciales` ()
BEGIN
		select * from ValoresIniciales;
END$$


DELIMITER ;

DROP procedure IF EXISTS `getAllNominas`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllNominas` ()
BEGIN
		select * from Nominas;
END$$

DELIMITER ;


DROP procedure IF EXISTS `getAllProductos`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllProductos` ()
BEGIN
		select * from Productos;
END$$

DELIMITER ;



DROP procedure IF EXISTS `getEmpleadosByNomina`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getEmpleadosByNomina` (in pIdNomina int)
BEGIN
		select * from Empleados e
        inner join EmpleadoXNomina en on e.cedula = en.cedulaEmpleado
        where idNomina = pIdNomina ;
END$$

DELIMITER ;

call getEmpleadosByNomina(20);
/************DDL
insert into Usuarios(usuario, clave)
values('Usuarioej1', 'contraseñaEj1'),
	('usuarioEj2','contraseñaEj2')


insert into ValoresIniciales(cedulaJuridica, nombreComercio, telefono, numeroSecSigFact, porcentajeCargaSocial)
values(356485698, 'Comercio de ejemplo 01', 85645587, 0,1.5);

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

call insertEmpleado(701234568, 'martin', 'app1','app22', 'secretario', 256.55);
call insertEmpleado(709874567, 'jose', 'app2','app23', 'carpintero', 256.55);
call insertEmpleado(701245879, 'maria', 'app13','app24', 'profesor', 256.55);
call insertEmpleado(621584479, 'pedro', 'app4','app25', 'director', 215.55);
call insertEmpleado(502154875, 'juan', 'app5','app26', 'secretario', 56.55);
call insertEmpleado(705223698, 'carlos', 'app6','app247', 'ingeniero', 6556.55);
call insertEmpleado(452125589, 'pepe', 'app7','app28', 'profesor', 856.55);
call insertEmpleado(965458565, 'sofia', 'app8','app29', 'secretario', 456.55);
call insertEmpleado(702800054, 'adrian', 'app9','app210', 'secretario', 966.55);*/