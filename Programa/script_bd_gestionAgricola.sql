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
    
    update ValoresIniciales
    set numeroSecSigFact = LAST_INSERT_ID()+1
    where cedulaJuridica = pCedulaJuridica;
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


DROP procedure IF EXISTS `getAllFacturas`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getAllFacturas` ()
BEGIN
		select * from Factura;
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


DROP procedure IF EXISTS `getProductosByFactura`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getProductosByFactura` (in pIdFactura int)
BEGIN
		select * from Productos p
        inner join ProductoXFactura pf on p.idProducto = pf.idProducto
        where numeroFactura = pIdFactura ;
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



DROP procedure IF EXISTS `getBalanceAnual`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getBalanceAnual` ()
BEGIN
		select nominas.anio, ifnull(totalNominaCarga,0), ifnull(subtotalFacturas,0), ifnull(IVFactura,0), 
        ifnull((totalNominaCarga + subtotalFacturas),0) balance 
        from(
			select sum(total) totalNominaCarga, anio from Nominas
			group by anio
		)nominas
		left join(
			select sum(subtotal) subtotalFacturas, sum(impuestoVenta) IVFactura , year(fecha) anio from Factura
			group by anio
		) facturas 
		on facturas.anio = nominas.anio ;
END$$

DELIMITER ;



DROP procedure IF EXISTS `getBalanceMensual`;

DELIMITER $$
USE `gestionAgricola`$$
CREATE PROCEDURE `getBalanceMensual` (in pAnio int)
BEGIN
		select mes, anio, ifnull(sum(totalNominaCarga),0), ifnull(sum(subtotalFacturas),0),ifnull(sum(IVFactura),0), 
        ifnull(sum(totalNominaCarga + subtotalFacturas),0) balance 
        from(
			select mes,anio , sum(total) totalNominaCarga, 0 subtotalFacturas,0 IVFactura
            from Nominas
			where anio = pAnio
			group by mes, anio
		union
			select month(fecha) mes, year(fecha) anio, 0 ,sum(subtotal) subtotalFacturas, sum(impuestoVenta) IVFactura 
            from Factura
			where year(fecha) = pAnio
			group by mes, anio
		) d
        group by mes, anio
        order by mes, anio ASC;
END$$

DELIMITER ;




/************DDL
insert into Usuarios(usuario, clave)
values('jphuntv', 'jp1234'),
	('usrxd','clave05');


insert into ValoresIniciales(cedulaJuridica, nombreComercio, telefono, numeroSecSigFact, porcentajeCargaSocial)
values(356485698, 'Agrosa', 85645587, 2,1.5);

call insertArea('Alpha', 220.45, 'Papa');
call insertArea('Bravo', 150.95, 'Platano');
call insertArea('Charlie', 426.40, 'Yuca');
call insertArea('Delta', 150.000, 'Mango');
call insertArea('Echo', 895.450, 'Banano');
call insertArea('Foxtrot', 100.50, 'Camote');
call insertArea('Golf', 185.000, 'Fresas');
call insertArea('Hotel', 144.564, 'Huevos');
call insertArea('India', 154.450, 'Carne');
call insertArea('Juliett', 415.000, 'Caña');

call insertEmpleado(701234568, 'Conrado', 'Arias','Pallarés', 'Ingeniero', 400.000);
call insertEmpleado(709874567, 'Jose', 'Peña','Armengol', 'Carpintero', 325.652);
call insertEmpleado(201245879, 'Salomé', 'Tomas','Díaz', 'Ingeniero', 400.000);
call insertEmpleado(621584479, 'Ingrid', 'Esparza','Bosch', 'Jardinero', 356.214);
call insertEmpleado(502154875, 'Román', 'Alcázar','Hidalgo', 'Jardinero', 356.214);
call insertEmpleado(705223698, 'Carlos', 'Cruz','Cruz', 'Carpintero', 325.652);
call insertEmpleado(452125589, 'Asdrubal', 'Nevado','Losada', 'Chofer', 320.321);
call insertEmpleado(965458565, 'René', 'Arjona','Ramirez', 'Carpintero', 325.652);
call insertEmpleado(702800054, 'Adrian', 'Antpon','Marques', 'Chofer', 320.321);

*/






