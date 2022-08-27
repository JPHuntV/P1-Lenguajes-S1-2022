#ifndef structs
#define structs

struct Producto
{
    char *idProducto;
    char *nombre;
    int costo;
    float impAplicado;
    int cantidad;
};

struct Usuario
{
    char *usuario;
    char *clave;
};

struct ValoresIniciales
{
    int cedulaJuridica;
	char *nombreComercio;
	int telefono;
	int numeroSecSigFact;
	float porcentajeCargaSocial;
};

struct Empleado
{
    int cedula;
	char *nombre;
	char *apellido1;
	char *apellido2;
	char *labor;
	float salarioMensual;
};
struct Nomina
{
    int mes;
    int anio;
    struct Empleado *empleados;
    float subtotal;
    float total;
};

struct Area
{
    char *nombre;
    float dimension;
    char *productoPrincipal;
};


struct Factura
{
    struct Producto *productos;
    char *nombreCliente;
    int dia;
    int mes;
    int anio;
    struct Area area;
    float subtotal;
    float impuestosVenta;
    float Total;

};

#endif