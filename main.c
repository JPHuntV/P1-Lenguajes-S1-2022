#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "server.h"
#include "declaraciones.h"

#define LSIZ 128
#define RSIZ 10

struct ValoresIniciales valoresIniciales;

void transformarArchivo(FILE *archivo);

/*****************************
 * Nombre: main
 * E:ninguna
 * S:Ejecución del programa
 * R:Conexión a la red para establecer conexión con el servidor de base de datos
 * O:Conectarse a la base de datos y dar inicio a la ejecución del programa
 * ***************************/
int main(){
    system("clear");
    conectarServidor();
    valoresIniciales = cargarValoresIniciales();
    menuPrincipal();
    return 0;
}

/*****************************
 * Nombre: menuPrincipal
 * E:ninguna
 * S:menu principal en consola
 * R:Elgir una opción disponible
 * O:Mostrar al usuario un menu y redireccionarlo al menu de la opción que elija
 * ***************************/
void menuPrincipal(){
    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú principal  #####\n\n");
        printf("1.Opciones operativas. \n");
        printf("2.Opciones administrativas. \n");
        printf("3.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 3:\t");
        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            if(solicitarUsuario()){//Verifica que el usuario exista en la base de datos
                printf("Sesión iniciada");
                menuOperativo();
            }else{
                printf("\n-----El usuario o contraseña ingresados son incorrectos.-----\n");
                pausa();
            }
            break;
        case '2':
            menuAdministrativo();
            break;
        
        case '3':
            repetir = 0;
            break;
        
        default:
            break;
        }
    }while(repetir);
    printf("Saliendo......\n");
    salir();
    return;
}


/*****************************
 * Nombre: solicitarUsuario
 * E:Entrada de usuario : nombre de usuario y contraseña
 * S:true si el usuario existe en la base de datos, false si no 
 * R:Debe existir conexión con el servidor de base de datos
 * O:Verificar que el usuario ingresado exista en la base de datos
 * ***************************/
bool solicitarUsuario(){
    system("clear");
    char pUsuario[200];
    printf("Por favor ingrese su nombre de usuario y contraseña\n\nUsuario:\t");
    scanf("%s",pUsuario);
    while((getchar()!='\n'));

    char pClave[200];
    printf("\nContraseña:\t");
    scanf("%s",pClave);
    while((getchar()!='\n'));

    struct Usuario usuario = {pUsuario,pClave};
    getUsuario(&usuario);
    row = mysql_fetch_row(res);
    if(row==NULL){
        printf("\n-----El usuario o contraseña ingresados son incorrectos.-----\n");
    }
    freeMysql();
    return row!= NULL;
}


/*****************************
 * Nombre:menuOperativo
 * E:entrada de usuario:opcion
 * S:llamada a la funcionalidad seleccionada
 * R:debe ingresar usuario y contraseña previamente
 * O:Despliega una lista de opciones (funcionalidades) para que el usuario seleccione
 * ***************************/
void  menuOperativo(){
    system("clear");
    char opcion;
    char repetir = 1;
    do{
        
        printf("\n#####  Menú operativo  #####\n\n");
        printf("1.Cargar productos. \n");
        printf("2.Listar Areas. \n");
        printf("3.Listar Empleados. \n");
        printf("4.Volver al menú principal.\n");
        printf("5.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 4:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            printf("cargar productos");
            leerArchivo();
            break;
        
        case '2':
            printf("listar areas");
            int x ;
            listarAreas(&x);
            break;
        
        case '3':
            printf("listar empleados");
            listarEmpleados();
            break;

        case '4':
            repetir = 0;
            break;
        case '5':
            printf("saliendo......\n");
            salir();
        default:
            break;
        }
    }while(repetir);
    
    

    return;
}


/*****************************
 * Nombre:menuAdministrativo
 * E:entrada de usuario:opcion
 * S:llamada a la funcionalidad seleccionada
 * R:ninguna
 * O:Despliega una lista de opciones (funcionalidades) para que el usuario seleccione
 * ***************************/
void  menuAdministrativo(){
    system("clear");
    char opcion;
    char repetir = 1;
    //obtener siguiente numero factura
    printf("\n-----Valores iniciales-----\n");
    printf("Cedula jurídica: %d\nNombre: %s\nTeléfono: %d\nNumero de la siguiente factura: %d\n\n\n",valoresIniciales.cedulaJuridica, valoresIniciales.nombreComercio, 
                        valoresIniciales.telefono, valoresIniciales.numeroSecSigFact);
    do{
        printf("\n#####  Menú administrativo  #####\n\n");
        printf("1.Registro de nomina \n");
        printf("2.Registro ventas. \n");
        printf("3.Consulta de nomina.\n");
        printf("4.Consulta de ventas.\n");
        printf("5.Consulta Balance anual\n");
        printf("6.Volver al menú principal.\n");
        printf("7.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 7:\t");

        scanf(" %c", &opcion);
        switch (opcion)
        {
        case '1':
            printf("registro de nomina");
            
            generarNomina();
            break;
        
        case '2':
            printf("registro de ventas");
            generarFactura();
            break;

        case '3':
            printf("Consulta de nominas");
            listarNominas();
            break;

        case '4':
            printf("Consulta de ventas");
            listarFacturas();
            break;
        case '5':
            printf("Consulta balance anual");
            listarBalances();
            break;
        case '6':
            repetir = 0;
            break;
        case '7':
            printf("saliendo......\n");
            salir();
        default:
            break;
        }
    }while(repetir);
    return;
}


/*****************************
 * Nombre:cargarValoresIniciales
 * E:arreglo enviado por el servidor con los valores iniciales
 * S:almacén del struct con los valores iniciales
 * R:tener conexión al servidor, debe existir el elemento en la base de datos
 * O:solicita el arreglo de valores iniciales a la base de datos y genera un struct
 * ***************************/
struct ValoresIniciales cargarValoresIniciales(){
    getValoresIniciales();
    row = mysql_fetch_row(res);
    freeMysql();
    struct ValoresIniciales pValoresIniciales = {atoi(row[0]),row[1],atoi(row[2]),atoi(row[3]),atof(row[4])};
    return pValoresIniciales;
}


/*****************************
 * Nombre:leerArchivo
 * E:ruta del archivo que contiene los productos a cargar
 * S:llamada a la función transformar archivo
 * R:El archivo debe existir en la ruta indicada 
 * O:Solicita un archivo txt y lo carga al programa
 * ***************************/
void leerArchivo(){
    FILE *archivo;
    int tamanio;
    int cantidadLineas = 0;
    char ultimoCaracter;
    char ruta[200];
    printf("\nPorfavor indique la ruta del archivo:");
    scanf("%s",ruta);
    archivo = fopen(ruta, "r+");
    while((getchar()!='\n'));
    if(archivo == NULL){
        printf("\n\nLa ruta indicada no existe o no está disponible.\n");
        return;
    }
    else{
        fseek(archivo, 0L, SEEK_END);
        tamanio = ftell(archivo);
        fseek(archivo, tamanio-1, SEEK_SET);
        
        ultimoCaracter = fgetc(archivo);
        
        if(ultimoCaracter!='\n') fputc('\n', archivo);

        fseek(archivo, 0L, SEEK_SET); 

        transformarArchivo(archivo);
    }
    fclose(archivo);
    
    return;    
}


/*****************************
 * Nombre:
 * E:archivo con los productos a insertar
 * S:registro de los productos a base de datos
 * R:poseer conexión al servidor y formato correcto del archivo
 * O:recibe un archivo, lo divide por ",", registra las entradas en la base de datos
 * ***************************/
void transformarArchivo(FILE *archivo){
    char lineas[RSIZ][LSIZ];
    int i = 0;
    int j = 0;
    
    while(fgets(lineas[i], LSIZ, archivo)){
        lineas[i][strlen(lineas[i])-1]='\0';
        i++;
    }
    j = i;
    system("clear");
    printf("\nSe incluiran los siguientes productos\n");
    struct Producto Productos[i];
    for(i = 0; i<j; ++i){
        char *str = lineas[i];
        //printf("%s\n",str);
        char *idProducto = strtok(str,",");//dividiendo por comas
        char *nombre = strtok(NULL,",");
        char *costo = strtok(NULL,",");
        char *impAplicado = strtok(NULL,",");

        if(idProducto != NULL &&
            esNumero(costo) && esNumero(impAplicado)){//generar struct
            struct Producto pProducto;
            pProducto.idProducto = idProducto;
            pProducto.nombre = nombre;
            pProducto.costo = atof(costo);
            pProducto.impAplicado = atof(impAplicado);
            printf("Id Producto: %s\tNombre: %s\tCosto unitario: %f\timpuesto Aplicado: %f\n\n", 
                        pProducto.idProducto,pProducto.nombre, pProducto.costo, pProducto.impAplicado);
            insertProducto(&pProducto);
        } 
    }
    printf("------------------------------------\n");
    pausa();
    return;
}


/*****************************
 * Nombre: listarAreas
 * E:puntero a variable donde se almacena la cantidad de areas
 * S:cantidad de areas mediante puntero y arreglo con las areas registradas
 * R:conexión a la base de datos
 * O:Solicita la lista de areas al servido y  retorna un arreglo con ellas además de su cantidad
 * ***************************/
struct Area* listarAreas(int *cantidadAreas){
    system("clear");
    getAllAreas();
    printf("\n##### Areas #####\n");
    int i=0;
    *cantidadAreas = (int)mysql_num_rows(res);
    struct Area *lAreas = malloc(sizeof(struct Area)*(int)mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        lAreas[i].nombre = row[1];
        lAreas[i].dimension = atof(row[2]);
        lAreas[i].productoPrincipal = row[3];
        printf("[%d].\t%s\t\t%s\t\t%s\t\t\t%s\t\n",i,row[0], row[1],row[2], row[3]);
        i++;
    }
    freeMysql();

    return lAreas;
}



/*****************************
 * Nombre: listarEmpleados
 * E:ninguna
 * S:arreglo con los empleados registrados en base de datos
 * R:conexión a la base de datos
 * O:Solicita la lista de empleados a la base de datos
 * ***************************/
struct Empleado* listarEmpleados(){
    system("clear");
    getAllEmpleados();
    cantEmpleados = (int)mysql_num_rows(res);
    int i=0;
    struct Empleado *lEmpleados =malloc(sizeof(struct Empleado)*(int)mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        lEmpleados[i].cedula = atoi(row[0]);
        lEmpleados[i].nombre = row[1];
        lEmpleados[i].apellido1 =  row[2];
        lEmpleados[i].apellido2 = row[3];
        lEmpleados[i].labor= row[4];
        lEmpleados[i].salarioMensual = atof(row[5]);
        i++;
    }
    imprimirEmpleados(lEmpleados, cantEmpleados);
    printf("\n#########################################################\n");
    freeMysql();
    
    return lEmpleados;
}


/*****************************
 * Nombre: generarNomina
 * E: entrada del usuario mediate inputs
 * S: Struct nomina 
 * R: Conexión a base de datos y valores validos
 * O:
 * ***************************/
void generarNomina(){
    struct Nomina nomina ;

    printf("\nIngrese el mes:\t");
    nomina.mes = getNum("mes");
    while(nomina.mes>12 || nomina.mes<1){
        printf("\n\nIngrese un mes valido (entre 1 y 12):\t");
        nomina.mes = getNum("mes");   
    }

    printf("\nIngrese el año:\t");
    nomina.anio = getNum("año");
    while(nomina.anio>2100 || nomina.anio<2021){
        printf("\n\nIngrese un año valido (entre 2021 y 2100):\t");
        nomina.anio = getNum("año");
    }

    int cantidadNomina = 0;
    nomina.empleados = agregarEmpleados(&cantidadNomina);// agrega empleados a la nomina
    
    //imprimir detalle nomina
    system("clear");
    printf("\n##### Detalle de la nomina #####");
    printf("\nAño: \t%d\nMes: \t%d", nomina.anio, nomina.mes);

    //subtotal y total
    float subtotal = 0;
    float total = 0;
    int i=0;
    imprimirEmpleados(&nomina.empleados[i],cantidadNomina);
    while (i < cantidadNomina){
        subtotal += nomina.empleados[i].salarioMensual;
        total += nomina.empleados[i].salarioMensual * valoresIniciales.porcentajeCargaSocial;
        ++i;
    }
    nomina.subtotal = subtotal;
    nomina.total = total;
    printf("\n\nSubtotal: \t%f\nTotal: \t\t%f", subtotal, total);

    getchar();
    char opcion;

    //guardar nomina en base de datos
    printf("\n\n¿Desea guardar esta nomina ? (y/n): ");
    scanf(" %c", &opcion);
    if(opcion == 'y' || opcion == 'Y'){
        int idNomina;
        insertNomina(&nomina, &idNomina);
        freeMysql();
        int i = 0;
        while(i<cantidadNomina){
            insertEmpleadoXNomina(nomina.empleados[i].cedula,idNomina, cantidadNomina );
            freeMysql();
            i++;
        }
    }
    getchar();
    freeMysql();
    pausa();
    return;

}


/*****************************
 * Nombre: agregarEmpleados
 * E:puntero donde se almacenara la cantidad de empleados que se agruegue
 * S:arreglo con los empleados que formaran parte de la nomina
 * R: conexión a base de datos y una nomina preexistente
 * O:muestra al usuario los empleados registrados y le permite agregarlos a la nomina para luego guardarla
 * ***************************/
struct Empleado* agregarEmpleados(int *pCantidadNomina){
    struct Empleado *lEmpleados = listarEmpleados();
    struct Empleado *empleadosNomina = NULL;
    int num = -1;
    int j = 0;
    printf("\nIngrese el id del empleado u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < cantEmpleados){
            if(!enNomina(lEmpleados[num].cedula,empleadosNomina,j) ){//verificar que no haya sigo agregado
                empleadosNomina = realloc(empleadosNomina, sizeof(struct Empleado)*++j);
                empleadosNomina[j-1] = lEmpleados[num];
                system("clear");
                imprimirEmpleados(lEmpleados, cantEmpleados);
                printf ("\n\n########## Empleados en nomina ##########");
                imprimirEmpleados(empleadosNomina,j);
            }else{
                printf("\nEste empleado ya fue agregado a la nomina");
            } 
        }else{
            printf("\nEste empleado no existe\n\n");
        }
        printf("\nIngrese el id del empleado u otro caracter para terminar la selección\nOpción: ");   
    } 
    *pCantidadNomina = j;
    return empleadosNomina;
}



/*****************************
 * Nombre:enNomina
 * E:cedula de un empleado, nomina en construcción, cantidad de empleados en nomina
 * S:true si el empleado ya está en la nomina, false si no 
 * R:ninguna
 * O:verifica si un empleado ya fue agreagado a la nomina
 * ***************************/
bool enNomina(int cedula, struct Empleado *nomina, int cantidad){
    int i = 0;
    while (i<cantidad)
    {
        if(cedula == nomina[i].cedula){
            return true;
        }
        i++;
    }
    return false;
}


/*****************************
 * Nombre: generarFactura
 * E:entrada del usuario (información de la factura)
 * S:almacen de factura y sus productos en base de datos
 * R:conexión a la base de datos 
 * O:selecciona una lista de productos en información para generar una orden de compra
 * ***************************/
void generarFactura(){
    //obtener y mostrar productos
    struct Factura pFactura;
    int guardar = 0;
    int cantidadProductos = 0;
    struct Producto *pProductos =menuProductos(&guardar, &cantidadProductos);
    pFactura.productos= pProductos;

    printf("\nvoy a imprimir\n");
    printf("\nquiere guardar?: %d", guardar);
    if(guardar){
        int i = 0;
        float subtotal =0;
        float subtotalP = 0;
        float impuesto = 0;
        float impuestoP = 0;
        
        while(i<cantidadProductos){   
            subtotalP = pFactura.productos[i].costo * pFactura.productos[i].cantidad;
            impuestoP = (pFactura.productos[i].costo * pFactura.productos[i].cantidad*pFactura.productos[i].impAplicado/100);
            subtotal = subtotal+ subtotalP;
            impuesto = impuesto +impuestoP;

            printf("\n cantidad: %d, subtotal: %f, impuestos: %f, total: %f",pFactura.productos[i].cantidad,subtotalP, impuestoP, subtotalP+impuestoP);
            i++;
        }
        float total = subtotal + impuesto;
        printf("\n\n\ngeneral\ncantidad: %d, subtotal: %f, impuestos: %f, total: %f",cantidadProductos,subtotal, impuesto, total);
            
        pFactura.subtotal = subtotal;
        pFactura.impuestosVenta = impuesto;
        pFactura.Total = total;
        getchar();
        printf("\nNombre del cliente:\t");
        char pNombreCliente[60];
        scanf(" %[^\n]", pNombreCliente);

        pFactura.nombreCliente = pNombreCliente;
        printf("\nDia(dd):\t");
        scanf("%d", &pFactura.dia);

        printf("\nMes(mm):\t");
        scanf("%d", &pFactura.mes);

        printf("\nAño(AAAA):\t");
        scanf("%d", &pFactura.anio);

        int cantidadAreas = 0;
        struct Area *lAreas = listarAreas(&cantidadAreas);
        printf("cantidad de areas: %d", cantidadAreas);

        printf("\n\nSeleciones el area de producción:\t");
        int num;
        int ingreso = 0;
        while (scanf("%d", &num)==1){
            if(num < cantidadAreas){
                    pFactura.area = lAreas[num];
                    ingreso = 1;
                    break;
            }else{
                printf("\nEsta area no existe\n\n");
            }
        printf("\nIngrese el id del area u otro caracter para cancelar el registro\nOpción: ");  
        }
        if(ingreso){
            getchar();
            char opcion;
            printf("\n\n¿Desea guardar esta factura ? (y/n): ");
            scanf(" %c", &opcion);

            if(opcion == 'y' || opcion == 'Y'){
                int idFactura;
                insertFactura(&pFactura,&idFactura, &valoresIniciales);
                pFactura.numeroFactura = idFactura;
                freeMysql();
                int i = 0;
                while(i<cantidadProductos){
                    insertProductoXFactura(pFactura.productos[i].idProducto,idFactura, pFactura.productos[i].cantidad );
                    freeMysql();
                    i++;

                }
                imprimirDetalleFactura(&pFactura);
                pausa();
            }
        }


    }
    return;
    
}



/*****************************
 * Nombre: menuProductos
 * E:puntero (bandera) para guardar la factura, puntero que almacenará la cantidad de productos 
 * que se agreguen a la orden de compra
 * S:arreglo con los valores agregados a la orden 
 * R:conexión  a la base de datos, si el producto ya existe aumentar cantidad
 * O:Despliega una lista de productos y le permite al usuario agregarlos a su carrito o eliminarlos
 * ***************************/
struct Producto* menuProductos(int *guardar, int *cantidadProductos){
    int pcantidadProductos = 0;
    struct Producto *lProductos = listarProductos(&pcantidadProductos);
    struct Producto *productosFactura = NULL;
    int j = 0;//tamaño array

    char opcion;
        char repetir = 1;
        do{
        
            printf("#####   Menú productos   #####\n\n");
            printf("1)Agregar producto. \n");
            printf("2)Eliminar producto\n");
            printf("3)Guardar\n");
            printf("4)Salir\n");
            printf("#############################\n");
            printf("Seleccione una opción:\t");

            scanf(" %c", &opcion);
            switch (opcion)
            {
            case '1':  
                productosFactura =agregarProducto(productosFactura, lProductos, pcantidadProductos, &j);
                break;
            
            case '2':
                productosFactura =  eliminarProducto(productosFactura, &j);
                break;
            case '3':
                *guardar = 1;
                repetir =0;
                break;
            
            case '4':
                repetir = 0;
                break;
            
            default:
                break;
            }

            if(opcion =='1' || opcion =='2'){
                system("clear");
                imprimirProductos(lProductos, pcantidadProductos,0);       
                printf ("\n\n##### Productos en factura #####");
                int i = 0;
                imprimirProductos(productosFactura, j, 1);
                printf("\n\n");
            }         

        }while(repetir);

    *cantidadProductos = j;

    return productosFactura;

}


/*****************************
 * Nombre:AgregarProducto
 * E:arrelops de productos general y en carrito
 * S:arreglo de productos con el nuevo producto
 * R:deben existir productos 
 * O:Agrega un producto al carrito
 * ***************************/
struct Producto* agregarProducto(struct Producto *productosFactura,struct Producto *lProductos, int pcantidadProductos, int *j){
    int num = -1;
    int k = *j;
    printf("\nIngrese el indice del producto u otro caracter para terminar la selección\n[Indice producto]: ");
    while (scanf("%d", &num)==1){
        if(num < pcantidadProductos){
                productosFactura = realloc(productosFactura, sizeof(struct Producto)*++k);  //aumentar tamaño del arreglo 
                int cantidadProd = 0;
                printf("\nCantidad: ");
                scanf("%d", &cantidadProd);
                if(!enFactura(lProductos[num].idProducto,productosFactura,k) ){
                    productosFactura[k-1] = lProductos[num];
                    productosFactura[k-1].cantidad = cantidadProd;
                    break;
                }else{
                    int t = 0;
                    while (t<k)
                    {
                        if(lProductos[num].idProducto == productosFactura[t].idProducto){
                            productosFactura[t].cantidad += cantidadProd;
                            k--;
                            break;
                        }
                        t++;
                    }
                    break;
                    
                }   
        }else{
            printf("\nEste prodcto no existe\n\n");
        }
        printf("\nIngrese el indice del producto u otro caracter para terminar la selección\n[Indice producto]: ");
    
    }
    *j= k; 
    return productosFactura;
}


/*****************************
 * Nombre: eliminarProducto
 * E:producto en factura, cantidad de procusto
 * S:elimiación del producto
 * R:el producto debe existir
 * O:Remueve un producto del arreglo a registrar
 * ***************************/
struct Producto* eliminarProducto(struct Producto *productosFactura, int *j){
    printf("\n\n\n eliminar productos");

    int num = -1;
    int k = *j;
    printf("\nIngrese el id del producto u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < k){
            int i = 0;
            for(i =1;i <k-1;i++){
                productosFactura[i]=productosFactura[i+1];
            }
            k -=1;
            break;
        }else{
            printf("\nEste producto no existe en la factura\n\n");
        }
        printf("\nIngrese el id del producto u otro caracter para terminar la selección\nOpción: ");         
    } 
    *j = k;
    return productosFactura;
}



/*****************************
 * Nombre:listarProductos
 * E:puntero que almcenara la cantidd de productos
 * S:cantidad de productos y arreglos con ellos
 * R:conexión a base de datosdsldsf
 * O:carga los producto al programa
 * ***************************/
struct Producto* listarProductos(int *pCantidadProductos){
    system("clear");
    getAllProductos();
    *pCantidadProductos = (int)mysql_num_rows(res);
    printf("##### Productos #####");
    int i=0;
    struct Producto *lProductos =malloc(sizeof(struct Producto)*(int)mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        lProductos[i].idProducto = row[0];
        lProductos[i].nombre = row[1];
        lProductos[i].costo =  atof(row[2]);
        lProductos[i].impAplicado = atof(row[3]);
        i++;
    }
    printf("\n\ncantidad productos%d", *pCantidadProductos);
    imprimirProductos(lProductos, *pCantidadProductos,0);
    printf("\n#########################################################\n");
    freeMysql();
    
    return lProductos;
}



/*****************************
 * Nombre:enFactura
 * E:id de un producto y la lista de productos en el carrito
 * S:true si el producto está en el carrito , false si no 
 * R:no tiene
 * O:recibe el id de un producto y verifica si este está o no en el carrito
 * ***************************/
bool enFactura(char *idProducto, struct Producto *factura, int j){
    int i = 0;
    while (i<j)
    {
        if(idProducto == factura[i].idProducto){
            return true;
        }
        i++;
    }
    return false;
}




/*****************************
 * Nombre:listarNominas
 * E:arreglo de nominas desde la base de datos
 * S:arreglo con las nominas obtenidas
 * R:conexión a la base de datos
 * O:solicita la lista de nominas a la base de datos y retorna un arreglo de struct tipo nomina
 * ***************************/
void listarNominas(){
    system("clear");
    getAllNominas();//solicitar nominas a la base de datos

    int i=0;
    int cantidadNominas = (int)mysql_num_rows(res);
    struct Nomina *lNominas =malloc(sizeof(struct Nomina)*cantidadNominas);//transformar respuesta a array
    while ((row = mysql_fetch_row(res)) != NULL){
        lNominas[i].idNomina=atoi(row[0]);
        lNominas[i].mes = atoi(row[1]);
        lNominas[i].anio = atoi(row[2]);
        lNominas[i].subtotal = atof(row[3]);
        lNominas[i].total = atof(row[4]);
        i++;
    }
    freeMysql();
    imprimirNominas(lNominas, cantidadNominas);


    int num = -1;
    printf("\nIngrese el id de la nomina para ver su detalle u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < cantidadNominas){
            system("clear");
            printf("\n##### Detalle de la nomina #####");
            printf("\nAño: \t%d\nMes: \t%d\nSubtotal: \t%f\nTotal: \t%f",
                    lNominas[num].anio, lNominas[num].mes,lNominas[num].subtotal, lNominas[num].total);
            printf("\n\nid de la nomina : %d", lNominas[num].idNomina);
            int cantEmpleados = getEmpleadosByNomina(lNominas[num].idNomina);
            int j=0;
            struct Empleado *lEmpleados =malloc(sizeof(struct Empleado)*(int)mysql_num_rows(res));
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                lEmpleados[j].cedula = atoi(row[0]);
                lEmpleados[j].nombre = row[1];
                lEmpleados[j].apellido1 =  row[2];
                lEmpleados[j].apellido2 = row[3];
                lEmpleados[j].labor= row[4];
                lEmpleados[j].salarioMensual = atof(row[5]);
                j++;
            }

            
            imprimirEmpleados(lEmpleados, cantEmpleados);
            printf("\n#########################################################\n");
            freeMysql();
            pausa();
            imprimirNominas(lNominas, cantidadNominas);
        }else{
            printf("\nEsta nomina no existe\n");
        }
        printf("\nIngrese el id de la nomina para ver su detalle u otro caracter para terminar la selección\nOpción: ");
            
    }
    freeMysql();
    pausa();
    return;
}



/*****************************
 * Nombre:listarFacturas
 * E:arreglo de facturas desde la base de datos
 * S:arreglo con las facturas obtenidas
 * R:conexión a la base de datos
 * O:solicita la lista de facturas y sus productos, retorna un arregl de struct tipo producto e imprime su
 * detalle
 * ***************************/
void listarFacturas(){
    system("clear");
    printf("\nlistar ventas");
    getAllFacturas();//solicitar facturas a la base de datos

    int i=0;
    int cantidadFacturas = (int)mysql_num_rows(res);
    printf("\nobtuve %d resultados\n", cantidadFacturas);
    struct Factura *lFacturas =malloc(sizeof(struct Factura)*cantidadFacturas);//transformar respuesta a array
    while ((row = mysql_fetch_row(res)) != NULL){
        char *fecha = row[4];
        char *anio = strtok(fecha,"-");
        char *mes = strtok(NULL,"-");
        char *dia = strtok(NULL,"-");

        lFacturas[i].numeroFactura = atoi(row[0]);
        lFacturas[i].anio = atoi(anio);
        lFacturas[i].mes =atoi(mes);
        lFacturas[i].dia = atoi(dia);
        lFacturas[i].nombreCliente = row[5];
        lFacturas[i].subtotal = atof(row[6]);
        lFacturas[i].impuestosVenta = atof(row[7]);
        lFacturas[i].Total = atof(row[8]);
        i++;
    }
    freeMysql();
    imprimirFacturas(lFacturas, cantidadFacturas);

    //solica el id de de una factura, luego imprime su detalle 
    int num = -1;
    printf("\nIngrese el id de la factura para ver su detalle u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < cantidadFacturas){
            imprimirDetalleFactura(&lFacturas[num]);
            freeMysql();
            imprimirFacturas(lFacturas, cantidadFacturas);
        }else{
            printf("\nEsta factura no existe\n");
        }
        printf("\nIngrese el id de la factura para ver su detalle u otro caracter para terminar la selección\nOpción: ");
            
    }
    freeMysql();
    pausa();
    return;
}



/*****************************
 * Nombre:imprimirDetalleFactura
 * E:struct factura que se quiere imprimir
 * S:impresión en consola de los detalles
 * R:recibir una factura
 * O:Recibe un struct factura e imprime sus detalles en consola
 * ***************************/
void imprimirDetalleFactura(struct Factura *pFactura){
    system("clear");
    printf("\n##### Detalle de la factura #####"); 

    printf("\nn.Factura: %d", pFactura->numeroFactura);
    printf("\nNombre del comercio: %s", valoresIniciales.nombreComercio);
    printf("\nCed.Jurídica: %d", valoresIniciales.cedulaJuridica);
    printf("\nNúmero de teléfono: %d", valoresIniciales.telefono);
    printf("\nFecha: %d/%d/%d", pFactura->anio, pFactura->mes, pFactura->dia);
    printf("\nNombre del cliente: %s", pFactura->nombreCliente);
    printf("\nDetalle\n------------------------------------------");

    int cantProductos = getProductosByFactura(pFactura->numeroFactura);//solicita todos los producto de la factura
    int j=0;
    struct Producto *lProductos =malloc(sizeof(struct Producto)*(int)mysql_num_rows(res));
   
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        lProductos[j].idProducto = row[0];
        lProductos[j].nombre = row[1];
        lProductos[j].cantidad = atoi(row[7]);
        lProductos[j].impAplicado = atof(row[3]);
        lProductos[j].costo = atof(row[2]);
        j++;
    }
    imprimirProductos(lProductos, cantProductos, 1);

    printf("\n---------------------------------------------------------------------\n");
    freeMysql();
    printf("\nSubtotal: %f", pFactura->subtotal);
    printf("\nIV: %f", pFactura->impuestosVenta);
    printf("\nTotal: %f", pFactura->Total);
    pausa();

    return;
}



/*****************************
 * Nombre:imprimirAreas
 * E:lista de areas a imprimir y cantidad de elementos en arreglo
 * S:impresión en consola de el arreglo de areas
 * R:ninguna
 * O:Imprime un arreglo de struct area
 * ***************************/
void imprimirAreas(struct Area *lAreas, int cantidad){
    int i = 0;
    printf("\n\tId Area\t\tNombre\t\tDimensión\t\tProducto principal producido\n");;
    while (i<cantidad)
    {
        printf("%d.\t%s\t\t%s\t\t%s\t\t\t%s\t\n",i,row[0], row[1],row[2], row[3]);
        i++;
    }
    return;
}



/*****************************
 * Nombre:imprimirNominas
 * E:arreglo de nominas y cantidad de elementos
 * S:imprime en consola el arreglo
 * R:ninguna
 * O:recibe una lista de nominas e imprime su detalle
 * ***************************/
void imprimirNominas(struct Nomina *lNominas, int cantidad){
    int i = 0;
    printf("'\n##### Nominas #####\n\n\tMes\t\tAño\t\tSubtotal\tTotal\n");
    while (i<cantidad)
    {
        printf("[%d].\t%d\t\t%d\t\t%d\t\t%f\t%f\n",i,lNominas[i].idNomina,lNominas[i].mes, lNominas[i].anio, lNominas[i].subtotal, lNominas[i].total);
        i++;
    }
    return;
}



/*****************************
 * Nombre: imprimirEmpleados
 * E:lista de empleados y cantidad de elementos
 * S:imprime el arreglo en consola
 * R:ninguna
 * O:Recibe un arreglo de empleados e imprime su detalle en consola
 * ***************************/
void imprimirEmpleados(struct Empleado *lEmpleados, int cantidad){
    int i = 0;
    printf("\n\n##### Empleados #####\n\n\tCedula \t\tNombre completo \tLabor \t\tSalario mensual \tSalario cargas sociales \n");
    while(i<cantidad){            
        printf("%d.\t%d \t%s %s %s \t%s \t%f  \t\t%f \n",i,
        lEmpleados[i].cedula, lEmpleados[i].nombre, lEmpleados[i].apellido1, lEmpleados[i].apellido2,
        lEmpleados[i].labor, lEmpleados[i].salarioMensual,  lEmpleados[i].salarioMensual*valoresIniciales.porcentajeCargaSocial);
        i++;
    }          
}



/*****************************
 * Nombre:imprimirFacturas
 * E:lista de facturas y cantidad de elementos
 * S:imprime la lista de facturas en consola
 * R:ninguna
 * O:recibe un arreglo de facturas e imprime su detalle
 * ***************************/
void imprimirFacturas(struct Factura *lFacturas, int cantidad){
    int i = 0;
    printf("##### Facturas #####\n\nNumero\t\tFecha\t\tSubtotal\tTotal\n");
    while (i<cantidad)
    {
        printf("%d.\t%d\t\t%d-%d-%d\t\t%f\t%f\n",i,lFacturas[i].numeroFactura, lFacturas[i].anio, lFacturas[i].mes, lFacturas[i].dia,lFacturas[i].subtotal, lFacturas[i].Total);
        i++;
    }
    return;
}



/*****************************
 * Nombre:imprimirProductos
 * E:lista de productos , cantidad de elementos y una bandera(imprimir cantidad de ese producto)
 * S:imprime en consola los detalles del arreglo
 * R:ninguna
 * O:recibe un arreglo de producto e imprime sus elementos en consola
 * ***************************/
void imprimirProductos(struct Producto *lProductos, int cantidad, int mostrarCant){
    int i = 0;
    printf("\n\n\tId Producto \tNombre \t\tCosto \t\tImpuesto aplicado ");
    if(mostrarCant == 1){
        printf("\t\tCantidad");
    }
    printf("\n");
    while(i<cantidad){            
        printf("%d.\t%s \t\t%s \t\t%f \t\t%f ",i,
        lProductos[i].idProducto, lProductos[i].nombre, lProductos[i].costo, lProductos[i].impAplicado);
        if(mostrarCant == 1){
            printf("\t\t%d", lProductos[i].cantidad);
        }
        printf("\n");
        i++;
    }          
}



/*****************************
 * Nombre:listarBalances
 * E:arreglo de balances solicitados a la base de datos
 * S:detalles de los balances en consola
 * R:conexión a la base de datos
 * O:Solicita los balances a la base de datos y los imprime en consola
 * ***************************/
void listarBalances(){
    system("clear");
    getBalanceAnual();//solicita los balances divididos por año

    int i=0;
    int cantidadBalances = (int)mysql_num_rows(res);
    struct Balance *lBalances =malloc(sizeof(struct Balance)*cantidadBalances);//transformar respuesta a array
    while ((row = mysql_fetch_row(res)) != NULL){
        lBalances[i].anio=atoi(row[0]);
        lBalances[i].totalNominas = atoi(row[1]);
        lBalances[i].subtotalFacturas = atoi(row[2]);
        lBalances[i].IVFacturas = atof(row[3]);
        lBalances[i].Balance = atof(row[4]);
        i++;
    }
    freeMysql();
    imprimirBalances(lBalances, cantidadBalances,0);//imprime el arreglo de balances recibidos

    int num = -1;
    printf("\nIngrese el id del para ver su detalle mensual u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < cantidadBalances){
            system("clear");
            printf("\n##### Detalle mesual##### %d",lBalances[num].anio);
            int cantMeses = getBalanceMensual(lBalances[num].anio); //solicita los balances de una año divididos por mes
            int j=0;
            struct Balance *lBalancesMes =malloc(sizeof(struct Balance)*(int)mysql_num_rows(res));//crea un struct con los balances recibidos
            while ((row = mysql_fetch_row(res)) != NULL)
            {
                lBalancesMes[i].mes=atoi(row[0]);
                lBalancesMes[i].anio = atoi(row[1]);
                lBalancesMes[i].totalNominas = atoi(row[2]);
                lBalancesMes[i].subtotalFacturas = atof(row[3]);
                lBalancesMes[i].IVFacturas = atof(row[4]);
                lBalancesMes[i].Balance = atof(row[5]);
                j++;
            }
 
            imprimirBalances(lBalancesMes, cantMeses,1); //solicita impresión de balances mensuales
            printf("\n#########################################################\n");
            freeMysql();
            pausa();
            imprimirBalances(lBalances, cantidadBalances,0);
        }else{
            printf("\nEste año no tiene detalles\n");
        }
        printf("\nIngrese el id del para ver su detalle mensual u otro caracter para terminar la selección\nOpción: ");
        
    }
    freeMysql();
    pausa();
    return;
}



/*****************************
 * Nombre:imprimirBalances
 * E:lista de balances(anuales o mensuales), cantidad de elementos y bandera(mes 1/año 0)
 * S:imprime en consola la lista de balances
 * R:ninguna
 * O:Recibe una arreglo de balances  y los imprime en consola
 * ***************************/
void imprimirBalances(struct Balance *lBalances, int cantidad,int imprimirMes){
    int i = 0;
    printf("'\n##### Balance por año #####\n\n");
    if(imprimirMes){
        printf("\tMes\t");
    }
    printf("\tAño\t\ttotal nomina\t\tSubtotal\tIV Factura\t\tBalance\n");
    while (i<cantidad)
    {

        printf("[%d].\t",i);
        if(imprimirMes){
            printf("%d\t\t",lBalances[i].mes);
        }
        printf("%d\t\t%f\t\t%f\t%f\t%f\n",lBalances[i].anio, lBalances[i].totalNominas, 
        lBalances[i].subtotalFacturas, lBalances[i].IVFacturas,  lBalances[i].Balance);
        i++;
    }
    return;
}



/*****************************
 * Nombre:getNum
 * E:Bandera que indica el dato solicitado
 * S:numero ingresado por el usuario 
 * R:se debe ingresar un numero 
 * O:Solicita un numero al usuario y lo retorna
 * ***************************/
int getNum(char *mesanio){
    int num;
    while(scanf("%d", &num)!=1){
        printf("\nEl valor ingresado es incorrecto\nPor favor intentelo de nuevo\n");
        printf("\nIngrese el %s:\t", mesanio);
        scanf("%*s");
    }
    return num;
    
}
/*******************************************************************/


/*****************************
 * Nombre:esNumero
 * E:char *  a evaluar
 * S:true si es numero, false si no 
 * R:ninguna
 * O:Verifica si un valor es un numero o no 
 * ***************************/
bool esNumero(char *token){
    bool res = true;
    printf(" atoi:\t %d",atoi(token));
    printf(" atof:\t %f\n\n",atof(token));
   
    if(atoi(token) || atof(token)){
        return true;
    }
    return false;
}




/*****************************
 * Nombre:pausa
 * E:ninguna
 * S:pausa en consola
 * R:ninguna
 * O:Pausa la impresión en consola hasta que se presione la tecla enter
 * ***************************/
void pausa(){
    getchar();
    printf("\n\nPresione enter para continuar....");
    getchar();
    system("clear");
    return;
}



/*****************************
 * Nombre:salir
 * E:ningua
 * S:Cierra el programa
 * R:ninguna
 * O:Cancela la ejecución del programa
 * ***************************/
void salir(){
    exit(0);
}