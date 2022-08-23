#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "structs.h"
#include "server.h"


#define LSIZ 128
#define RSIZ 10


void menuPrincipal();

bool solicitarUsuario();
void menuOperativo();
void menuAdministrativo();


void leerArchivo();
void transformarArchivo(FILE *archivo);
void listarAreas();
void listarEmpleados();
struct ValoresIniciales cargarValoresIniciales();
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
    struct ValoresIniciales pValoresIniciales = cargarValoresIniciales();
    printf("\n-----Valores iniciales-----\n");
    printf("Cedula jurídica: %d\nNombre: %s\nTeléfono: %d\nNumero de la siguiente factura: %d\n\n\n",pValoresIniciales.cedulaJuridica, pValoresIniciales.nombreComercio, 
                        pValoresIniciales.telefono, pValoresIniciales.numeroSecSigFact);
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

void listarEmpleados(){
    system("clear");
    getAllEmpleados();

    printf("\n\tCedula\t\tNombre completo\t\tLabor\t\tSalario mensual\t\tSalario cargas sociales\n");
    int i=0;
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%d.\t%s\t%s\t\t\t%s\t\t%s\t\t\t%s\t\n",i,row[0], row[1],row[2], row[3],row[4]);
        i++;
    }
    freeMysql();
    pausa();
    return;
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