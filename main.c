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

int main(){
    system("clear");
    conectarServidor();
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
    char opcion;
    char repetir = 1;
    valoresIniciales = cargarValoresIniciales();
    //printf("Cantidad de empleados: %d", CANT_EMP);
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
            if(solicitarUsuario()){
                printf("correcto");
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
    printf("saliendo......\n");
    salir();
    return;
}

bool solicitarUsuario(){
    
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
    /*if(row==NULL){
        printf("\n-----El usuario o contraseña ingresados son incorrectos.-----\n");
    }*/
    freeMysql();
    return row!= NULL;
}

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
            listarAreas(0);
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

void  menuAdministrativo(){


    system("clear");
    char opcion;
    char repetir = 1;
    
    printf("\n-----Valores iniciales-----\n");
    printf("Cedula jurídica: %d\nNombre: %s\nTeléfono: %d\nNumero de la siguiente factura: %d\n\n\n",valoresIniciales.cedulaJuridica, valoresIniciales.nombreComercio, 
                        valoresIniciales.telefono, valoresIniciales.numeroSecSigFact);
    do{
        
        printf("\n#####  Menú administrativo  #####\n\n");
        printf("1.Registro de nomina \n");
        printf("2.Registro ventas. \n");
        printf("3.Consulta de nomina.\n");//////////////////////
        printf("4.Consulta de ventas.\n");
        printf("5.Volver al menú principal.\n");
        printf("6.Salir.\n");
        printf("#############################\n");
        printf("Seleccione una opcion del 1 al 6:\t");

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
            break;

        case '5':
            repetir = 0;
            break;
        case '6':
            printf("saliendo......\n");
            salir();
        default:
            break;
        }
    }while(repetir);
    
    

    return;
}

struct ValoresIniciales cargarValoresIniciales(){
    getValoresIniciales();
    row = mysql_fetch_row(res);
    freeMysql();
    struct ValoresIniciales pValoresIniciales = {atoi(row[0]),row[1],atoi(row[2]),atoi(row[3]),atof(row[4])};
    return pValoresIniciales;
}
//////////////////////////////////
void leerArchivo(){

    FILE *archivo;
    int tamanio;
    int cantidadLineas = 0;
    char ultimoCaracter;
    char ruta[200];
    printf("\nPorfavor indique la ruta del archivo:");
    //scanf("%s",ruta);
    archivo = fopen(/*ruta*/ "test.txt", "r+");
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

void transformarArchivo(FILE *archivo){
    char lineas[RSIZ][LSIZ];
    int i = 0;
    int j = 0;
    
    while(fgets(lineas[i], LSIZ, archivo)){
        lineas[i][strlen(lineas[i])-1]='\0';
        i++;
    }
    j = i;
    printf("\nSe incluiran los siguientes productos\n");
    struct Producto Productos[i];
    for(i = 0; i<j; ++i){
        char *str = lineas[i];
        printf("%s\n",str);
        char *idProducto = strtok(str,",");
        char *nombre = strtok(NULL,",");
        char *costo = strtok(NULL,",");
        char *impAplicado = strtok(NULL,",");
        printf("id:%s\n",idProducto);
        printf("nombre:%s\n",nombre);
        printf("costo:%s\n",costo);
        printf("impAplicado:%s\n",impAplicado);

        if(idProducto != NULL &&
            esNumero(costo) && esNumero(impAplicado)){
            struct Producto pProducto;
            pProducto.idProducto = idProducto;
            pProducto.nombre = nombre;
            pProducto.costo = atoi(costo);
            pProducto.impAplicado = atof(impAplicado);
            printf("idProducto:%s\tnombre:%s\tcosto:%d\timpuesto Aplicado:%f\n\n", 
                        pProducto.idProducto,pProducto.nombre, pProducto.costo, pProducto.impAplicado);
            insertProducto(&pProducto);
        } 
    }
    printf("------------------------------------\n");
    pausa();

    return;

}

struct Area* listarAreas(int *cantidadAreas){
    system("clear");
    getAllAreas();
    printf("##### Areas #####");
    //int cantidadAreas = (int)mysql_num_rows(res);
    //printf("\n\tId Area\t\tNombre\t\tDimensión\t\tProducto principal producido\n");
    int i=0;
    *cantidadAreas = (int)mysql_num_rows(res);
    struct Area *lAreas = malloc(sizeof(struct Area)*(int)mysql_num_rows(res));
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        lAreas[i].nombre = row[1];
        lAreas[i].dimension = atof(row[2]);
        lAreas[i].productoPrincipal = row[3];
        printf("%d.\t%s\t\t%s\t\t%s\t\t\t%s\t\n",i,row[0], row[1],row[2], row[3]);
        i++;
    }
    //imprimirAreas(lAreas, cantidadAreas);
    freeMysql();

    return lAreas;
}


struct Empleado* listarEmpleados(){
    system("clear");
    getAllEmpleados();
    cantEmpleados = (int)mysql_num_rows(res);
    printf("##### Empleados #####");
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

void generarNomina(){
    struct Nomina nomina ;
    printf("\nIngrese el mes:\t");
    /////nomina.mes = getNum("mes");
    nomina.mes = 2;
    while(nomina.mes>12 || nomina.mes<1){
       ////// printf("\n\nIngrese un mes valido (entre 1 y 12):\t");
        //////nomina.mes = getNum("mes");
        
    }
    printf("\nIngrese el año:\t");
    /////nomina.anio = getNum("año");
    nomina.anio = 2022;
    while(nomina.anio>2100 || nomina.anio<2021){
        //////////printf("\n\nIngrese un año valido (entre 2021 y 2100):\t");
       ///////// nomina.anio = getNum("año");
       
    }

    int cantidadNomina = 0;
    nomina.empleados = agregarEmpleados(&cantidadNomina);
   // printf("\n\n%d", nomina.empleados[0].cedula);

    
    //printf("\n%s",nomina.empleados[1].nombre);
    printf("cantidad en nomina: %d", cantidadNomina);


    //imprimir detalle nomina

    system("clear");
    printf("\n##### Detalle de la nomina #####");
    printf("\nAño: \t%d\nMes: \t%d", nomina.anio, nomina.mes);

    float subtotal = 0;
    float total = 0;
    printf("\n\n\tCedula \t\tNombre completo \tLabor \t\tSalario mensual \tSalario cargas sociales \n");
    int i=0;
    while (i < cantidadNomina){
        printf("%d.\t%d \t%s %s %s \t%s \t%f  \t\t%f \n",i,
        nomina.empleados[i].cedula,nomina.empleados[i].nombre,nomina.empleados[i].apellido1, nomina.empleados[i].apellido2,
        nomina.empleados[i].labor,nomina.empleados[i].salarioMensual, nomina.empleados[i].salarioMensual * valoresIniciales.porcentajeCargaSocial);
        subtotal += nomina.empleados[i].salarioMensual;
        total += nomina.empleados[i].salarioMensual * valoresIniciales.porcentajeCargaSocial;
        ++i;
    }
    nomina.subtotal = subtotal;
    nomina.total = total;
    printf("\n\nSubtotal: \t%f\nTotal: \t\t%f", subtotal, total);


    
    getchar();
    char opcion;
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

struct Empleado* agregarEmpleados(int *pCantidadNomina){
    struct Empleado *lEmpleados = listarEmpleados();
    struct Empleado *empleadosNomina = NULL;
    int num = -1;
    int j = 0;
    //printf("cantidad: %d", cantEmpleados);
    printf("\nIngrese el id del empleado u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1)
    {
        if(num < cantEmpleados){
            if(!enNomina(lEmpleados[num].cedula,empleadosNomina,j) ){
            
                empleadosNomina = realloc(empleadosNomina, sizeof(struct Empleado)*++j);
                
                empleadosNomina[j-1] = lEmpleados[num];
                printf ("\n\n##### Empleados en nomina #####");
                int i = 0;
                printf("\n\tCedula \t\tNombre completo \tLabor \t\tSalario mensual \tSalario cargas sociales \n");
                while(i<j){
                    printf("%d.\t%d \t%s %s %s \t%s \t%f  \t\t %f\n",i,
                    empleadosNomina[i].cedula,empleadosNomina[i].nombre,empleadosNomina[i].apellido1, empleadosNomina[i].apellido2,
                    empleadosNomina[i].labor,empleadosNomina[i].salarioMensual, 
                    empleadosNomina[i].salarioMensual * valoresIniciales.porcentajeCargaSocial);
                    ++i;
                }
            }else{
                printf("\nEste empleado ya fue agregado a la nomina");
            }
            
        }else{
            printf("\nEste empleado no existe\n\n");
        }
        printf("\nIngrese el id del empleado u otro caracter para terminar la selección\nOpción: ");
        
    } 
    
    *pCantidadNomina = j;
    //guardar nomina en base de datos
    return empleadosNomina;
}

bool enNomina(int cedula, struct Empleado *nomina, int j){
    int i = 0;
    while (i<j)
    {
        //printf("\n%d", nomina[i].cedula);
        if(cedula == nomina[i].cedula){
            //printf("ya existe");
            return true;
        }
        i++;
    }
    return false;
}



void generarFactura(){
    //obtener y mostrar productos
    struct Factura pFactura;
    int guardar = 0;
    int cantidadProductos;
    struct Producto *productosFactura = menuProductos(&guardar, &cantidadProductos);
    printf("\nquiere guardar?: %d", guardar);
    if(guardar){
        pFactura.productos= productosFactura;
        int i = 0;
        while(i<cantidadProductos){
            pFactura.subtotal += productosFactura[i].costo;
            pFactura.impuestosVenta += (productosFactura[i].costo*productosFactura[i].impAplicado)-productosFactura[i].costo;
            pFactura.Total +=productosFactura[i].costo*productosFactura[i].impAplicado;
            i++;
        }

        getchar();
        printf("\nNombre del cliente:\t");
        scanf("%[^\n]", pFactura.nombreCliente);

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
                
                insertFactura(&pFactura, &valoresIniciales);
                int idFactura = (int) mysql_num_rows(res);
                printf("id de la factura: %d", idFactura);
                freeMysql();
                int i = 0;
                while(i<cantidadProductos){
                    
                    insertEmpleadoXNomina(atoi(pFactura.productos[i].idProducto),idFactura, pFactura.productos[i].cantidad );
                    freeMysql();
                    i++;
                }
            }
        }


    }
    return;
    
}


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
            printf("\n\nsali de agregar: %d:\n\n", j);
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
            imprimirProductos(lProductos, pcantidadProductos,0);       
            printf ("\n\n##### Productos en factura #####");
            int i = 0;
            
            imprimirProductos(productosFactura, j, 1);
            printf("\n\n");
        }         

    }while(repetir);

    *cantidadProductos = pcantidadProductos;

}

struct Producto* agregarProducto(struct Producto *productosFactura,struct Producto *lProductos, int pcantidadProductos, int *j){
    int num = -1;
    int k = *j;
    printf("\nIngrese el id del producto u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < pcantidadProductos){
                productosFactura = realloc(productosFactura, sizeof(struct Producto)*++k);   
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
            printf("\nEste empleado no existe\n\n");
        }
        printf("\nIngrese el id del producto u otro caracter para terminar la selección\nOpción: ");
        
    }
    *j= k; 
    return productosFactura;
}

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
        lProductos[i].costo =  atoi(row[2]);
        lProductos[i].impAplicado = atof(row[3]);
        i++;
    }
    printf("\n\ncantidad productos%d", *pCantidadProductos);
    imprimirProductos(lProductos, *pCantidadProductos,0);
    printf("\n#########################################################\n");
    freeMysql();
    
    return lProductos;
}

bool enFactura(char *idProducto, struct Producto *factura, int j){
    int i = 0;
    while (i<j)
    {
        //printf("\n%d", nomina[i].cedula);
        if(idProducto == factura[i].idProducto){
            //printf("ya existe");
            return true;
        }
        i++;
    }
    return false;
}

void listarNominas(){
    system("clear");
    getAllNominas();

    int i=0;
    int cantidadNominas = (int)mysql_num_rows(res);
    struct Nomina *lNominas =malloc(sizeof(struct Nomina)*cantidadNominas);
    while ((row = mysql_fetch_row(res)) != NULL){
        lNominas[i].mes = atoi(row[1]);
        lNominas[i].anio = atoi(row[2]);
        lNominas[i].subtotal = atof(row[3]);
        lNominas[i].total = atof(row[4]);
        i++;
    }
    imprimirNominas(lNominas, cantidadNominas);
    freeMysql();
    int num = -1;
    printf("\nIngrese el id de la nomina para ver su detalle u otro caracter para terminar la selección\nOpción: ");
    while (scanf("%d", &num)==1){
        if(num < cantidadNominas){
            system("clear");
            printf("\n##### Detalle de la nomina #####");
            printf("\nAño: \t%d\nMes: \t%d\nSubtotal: \t%f\nTotal: \t%f",
                    lNominas[num].anio, lNominas[num].mes,lNominas[num].subtotal, lNominas[num].total);
            int cantEmpleados = getEmpleadosByNomina(num);
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


void imprimirNominas(struct Nomina *lNominas, int cantidad){
    int i = 0;
    printf("##### Nominas #####\n\n\tMes\t\tAño\t\tSubtotal\tTotal\n");
    while (i<cantidad)
    {
        printf("%d.\t%d\t\t%d\t\t%f\t%f\n",i,lNominas[i].mes, lNominas[i].anio, lNominas[i].subtotal, lNominas[i].total);
        i++;
    }
    return;
}

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

void imprimirProductos(struct Producto *lProductos, int cantidad, int mostrarCant){
    int i = 0;
    printf("\n\n\tId Producto \tNombre \t\tCosto \t\tImpuesto aplicado ");
    if(mostrarCant == 1){
        printf("\t\tCantidad");
    }
    printf("\n");
    while(i<cantidad){            
        printf("%d.\t%s \t\t%s \t\t%d \t\t%f ",i,
        lProductos[i].idProducto, lProductos[i].nombre, lProductos[i].costo, lProductos[i].impAplicado);
        if(mostrarCant == 1){
            printf("\t\t%d", lProductos[i].cantidad);
        }
        printf("\n");
        i++;
    }          
}


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


bool esNumero(char *token){
    bool res = true;
    for(int i = 0 ; token[i]!='\0';i++){
        if(!isdigit(token[i])){res = false;}
    }

    return res;
}
void pausa(){
    getchar();
    printf("\n\nPresione enter para continuar....");
    getchar();
    system("clear");
    return;
}
void salir(){
    exit(0);
}