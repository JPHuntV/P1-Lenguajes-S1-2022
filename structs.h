#ifndef structs
#define structs

struct Producto
{
    char *idProducto;
    char *nombre;
    int costo;
    float impAplicado;
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

#endif