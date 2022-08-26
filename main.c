#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "server.h"


#define LSIZ 128
#define RSIZ 10

struct ValoresIniciales valoresIniciales;


void menuPrincipal();

bool solicitarUsuario();
void menuOperativo();
void menuAdministrativo();

int cantEmpleados = 0;
void leerArchivo();
void transformarArchivo(FILE *archivo);
void listarAreas();
struct Empleado* listarEmpleados();
struct ValoresIniciales cargarValoresIniciales();
void generarNomina();
bool enNomina(int cedula, struct Empleado *nomina, int j);
int getNum(char* mesanio);
bool esNumero(char *token);
void pausa();
void salir();

int main(){
    system("clear");
    conectarServidor();
    menuPrincipal();
    return 0;
}

void menuPrincipal(){
    char opcion;
    char repetir = 1;
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
            listarAreas();
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
    valoresIniciales = cargarValoresIniciales();
    printf("\n-----Valores iniciales-----\n");
    printf("Cedula jurídica: %d\nNombre: %s\nTeléfono: %d\nNumero de la siguiente factura: %d\n\n\n",valoresIniciales.cedulaJuridica, valoresIniciales.nombreComercio, 
                        valoresIniciales.telefono, valoresIniciales.numeroSecSigFact);
    do{
        
        printf("\n#####  Menú administrativo  #####\n\n");
        printf("1.Registro de nomina \n");
        printf("2.Registro ventas. \n");
        printf("3.Consulta de nomina.\n");
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
            break;

        case '3':
            printf("Consulta de nominas");
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
    printf("\nentre a cargarlos\n");
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
    printf("\nSe incluiran las siguientes aulas\n");
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

void listarAreas(){
    system("clear");
    getAllAreas();

    printf("\n\tId Area\t\tNombre\t\tDimensión\t\tProducto principal producido\n");
    int i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t\t%s\t\t%s\t\t\t%s\t\n",i,row[0], row[1],row[2], row[3]);
        i++;
    }
    freeMysql();
    pausa();
    return;
}

struct Empleado* listarEmpleados(){
    system("clear");
    getAllEmpleados();
    printf("\ncantidad de empleados: %d\tporcentaje:%f\n\n", (int)mysql_num_rows(res),valoresIniciales.porcentajeCargaSocial);
    cantEmpleados = (int)mysql_num_rows(res);
    printf("\n\tCedula \t\tNombre completo \tLabor \t\tSalario mensual \tSalario cargas sociales \n");
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
        lEmpleados[i].salarioCargasSociales = atof(row[5])*valoresIniciales.porcentajeCargaSocial;
        printf("%d.\t%s \t%s %s %s \t%s \t%s  \t\t%f \n",i,row[0], row[1],row[2], row[3],row[4],row[5],atof(row[5])*valoresIniciales.porcentajeCargaSocial);
        i++;
    }
    freeMysql();
    
    return lEmpleados;
}


void generarNomina(){
    struct Nomina nomina;
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
    printf("\nAño y mes ingresados: %d\t%d",nomina.anio, nomina.mes);

    struct Empleado *lEmpleados = listarEmpleados();
    struct Empleado *empleadosNomina = NULL;


    int num = -1;
    int j = 0;
    printf("cantidad: %d", cantEmpleados);

    printf("selecione un empleado: ");
    while (scanf("%d", &num)==1)
    {
        
        if(num < cantEmpleados){
            if(!enNomina(lEmpleados[num].cedula,empleadosNomina,j) ){
            
                empleadosNomina = realloc(empleadosNomina, sizeof(struct Empleado)*++j);
                
                empleadosNomina[j-1] = lEmpleados[num];
                printf ("\n\nempleados en nomina: ");
                int i = 0;
                printf("\n\tCedula \t\tNombre completo \tLabor \t\tSalario mensual \tSalario cargas sociales \n");
                while(i<j){
                    printf("%d.\t%d \t%s %s %s \t%s \t%f  \t\t \n",i,
                    empleadosNomina[i].cedula,empleadosNomina[i].nombre,empleadosNomina[i].apellido1, empleadosNomina[i].apellido2,
                    empleadosNomina[i].labor,empleadosNomina[i].salarioMensual);
                    ++i;
                }
            }else{
                printf("\nEste empleado ya fue agregado a la nomina");
            }
            
        }else{
            printf("\nEste empleado no existe\n\n");
        }
        printf("\nselecione un empleado: ");
        
    } 
    
    
    //guardar nomina y no repetir empleados
    
    
    return;
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