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
#endif