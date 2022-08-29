#ifndef server
#define server

#include <mysql/mysql.h>

//Parametros de conexión a base de datos
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *sqlServer = "localhost";
char *user = "root";
char *password = "JpHv0410";
char *database = "gestionAgricola";

void freeMysql();

/*****************************
 * Nombre: conectarServidor
 * E:parametros de conexión
 * S:conexión a base de datos
 * R:Parametros para conexión deben ser validos
 * O:Establece una conexión con la base da datos
 * ***************************/
int conectarServidor(){
    printf("Estableciendo conexión con el servidor...");
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, sqlServer, user, password, database, 0, NULL, 0)){
        fprintf(stderr, "%s\n", mysql_error(conn));
    }else{
        printf("\nconexion establecida \n");
    }
}


/*****************************
 * Nombre:insertProducto
 * E:struct del producto que se quiere insertar en la base de datos
 * S:respuesta de la ejecución del query
 * R:los parametros enviados deben ser compatibles con el procedure en mysql
 * O:Insertar una nueva fila en la tabla gestionAgricola.Productos
 * ***************************/
void insertProducto(struct Producto *pProducto){
    char query[2000];
    sprintf(query, "call insertProducto('%s','%s', %f,%f)",pProducto->idProducto, pProducto->nombre, pProducto->costo,pProducto->impAplicado);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl producto se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


/*****************************
 * Nombre:insertNomina
 * E:struct de la nomina que se quiere insertar en la base de datos
 * S:respuesta de la ejecución del query
 * R:los parametros enviados deben ser compatibles con el procedure en mysql
 * O:Insertar una nueva fila en la tabla gestionAgricola.Nominas
 * ***************************/
void insertNomina(struct Nomina *pNomina, int *pIdNomina){
    char query[2000];
    sprintf(query, "call insertNomina('%d','%d', %f,%f)",pNomina->mes, pNomina->anio, pNomina->subtotal, pNomina->total);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nLa nomina se ha insertado correctamente!\n");
        res = mysql_store_result(conn);
        *pIdNomina = atoi(mysql_fetch_row(res)[0]);
    }
    return;
}


/*****************************
 * Nombre:insertEmpleadoXNomina
 * E:cedula del empleado y id de la nomina que se quieren insertar en la base de datos
 * S:respuesta de la ejecución del query
 * R:los parametros enviados deben ser compatibles con el procedure en mysql
 * O:Insertar una nueva fila en la tabla gestionAgricola.EmpleadoXNomina
 * ***************************/
void insertEmpleadoXNomina(int cedula, int pIdNomina, int pCantidadNomina){
    char query[2000];    
    sprintf(query, "call insertEmpleadoXNomina('%d','%d')", cedula, pIdNomina);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl empleado se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


/*****************************
 * Nombre:insertFactura
 * E:struct de la factura que se quiere insertar en la base de datos
 * S:respuesta de la ejecución del query
 * R:los parametros enviados deben ser compatibles con el procedure en mysql
 * O:Insertar una nueva fila en la tabla gestionAgricola.Factura
 * ***************************/
void insertFactura(struct Factura *pFactura,int *pIdFactura, struct ValoresIniciales *pValoresIniciales){
    char query[2000];
    sprintf(query, "call insertFactura('%s',%d,%d,'%d-%d-%d','%s',%f,%f,%f)",
            pValoresIniciales->nombreComercio, pValoresIniciales->cedulaJuridica,pValoresIniciales->telefono,
            pFactura->anio, pFactura->mes, pFactura->dia, pFactura->nombreCliente, pFactura->subtotal,pFactura->impuestosVenta,pFactura->Total/*pFactura->subtotal, pFactura->impuestosVenta, pFactura->Total*/);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    
    }else{
        printf("\nLa factura se ha insertado correctamente!\n");
        res = mysql_store_result(conn);
        *pIdFactura = atoi(mysql_fetch_row(res)[0]);
    }

    return;
}


/*****************************
 * Nombre:insertProductoXFactura
 * E:id del producto e id de la factura que se quieren insertar en la base de datos
 * S:respuesta de la ejecución del query
 * R:los parametros enviados deben ser compatibles con el procedure en mysql
 * O:Insertar una nueva fila en la tabla gestionAgricola.ProductoXFactura
 * ***************************/
void insertProductoXFactura(char *pIdProducto, int pIdFactura, int pCantidad){
    char query[2000];    
    sprintf(query, "call insertProductoXFactura('%s','%d','%d')", pIdProducto, pIdFactura, pCantidad);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n\n", mysql_error(conn));
    }else{
        printf("\nEl producto se ha insertado correctamente!\n");
        res = mysql_use_result(conn);
    }
    return;
}


/*****************************
 * Nombre:getAllAreas
 * E:ninguna
 * S:arreglo respuesta del procedure  getAllAreas()
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Areas 
 * ***************************/
int getAllAreas(){
    char *query = "call getAllAreas()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getAllEmpleados
 * E:ninguna
 * S:arreglo respuesta del procedure  getAllEmpleados()
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Empleados 
 * ***************************/
int getAllEmpleados(){
    char *query = "call getAllEmpleados()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getAllNominas
 * E:ninguna
 * S:arreglo respuesta del procedure  getAllNominas()
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Nominas 
 * ***************************/
int getAllNominas(){
    char *query = "call getAllNominas()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getAllFacturas
 * E:ninguna
 * S:arreglo respuesta del procedure  getAllFacturas()
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Factura 
 * ***************************/
int getAllFacturas(){
    char *query = "call getAllFacturas()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getAllProductos
 * E:ninguna
 * S:arreglo respuesta del procedure getAllProductos() 
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Productos 
 * ***************************/
int getAllProductos(){
    char *query = "call getAllProductos()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getBalanceAnual
 * E:ninguna
 * S:arreglo respuesta del procedure  getBalanceAnual()
 * R:ninguna
 * O:Solicita la creacion de una tabla con los balances anuales
 * ***************************/
int getBalanceAnual(){
    char *query = "call getBalanceAnual()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getBalanceMensual
 * E:Año para solicitar los balances
 * S:arreglo respuesta del procedure  getBalanceMensual()
 * R:ninguna
 * O:Solicita la creacion de una tabla con los balances mensuales según el año indicado
 * ***************************/
int getBalanceMensual(int anio){
    char query[2000];
    sprintf(query, "call getBalanceMensual('%d')",anio);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getProductosByFactura
 * E:id de la factura a consultar
 * S:arreglo respuesta del procedure  getProductosByFactura
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Productos en base a ProductosXFactura 
 * ***************************/
int getProductosByFactura(int factura){
    char query[2000];
    sprintf(query, "call getProductosByFactura('%d')",factura);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getEmpleadosByNomina
 * E:Id de la nomina a consultar
 * S:arreglo respuesta del procedure  getEmpleadosByNomina()
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Empleados segun EmpleadosXNomina 
 * ***************************/
int getEmpleadosByNomina(int nomina){
    char query[2000];
    sprintf(query, "call getEmpleadosByNomina('%d')",nomina);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getUsuario
 * E:struct usuario a verificar
 * S:arreglo respuesta del procedure getUserByUsuario  
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.Usuario para el inicio de sesión 
 * ***************************/
int getUsuario(struct Usuario *pUsuario){
    char query[2000];
    sprintf(query, "call getUserByUsuario('%s','%s')",pUsuario->usuario,pUsuario->clave);
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre:getValoresIniciales
 * E:ninguna
 * S:arreglo respuesta del procedure getValoresIniciales() 
 * R:ninguna
 * O:Solicita los datos de la tabla gestionAgricola.ValoresIniciales 
 * ***************************/
int getValoresIniciales(){
    
    char *query = "call getValoresIniciales()";
    if(mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    res = mysql_store_result(conn);
    
    return (int)mysql_num_rows(res);
}


/*****************************
 * Nombre: freeMysql
 * E:ninguna
 * S:limpia el caché de mysql
 * R:ninguna
 * O:Solicita la limpieza del caché
 * ***************************/
void freeMysql(){
    do
    {
        if(res = mysql_store_result(conn)){
            mysql_free_result(res);
        }
    } while (mysql_more_results(conn)&&mysql_next_result(conn));
    
    return;
}
#endif