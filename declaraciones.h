#ifndef declaraciones
#define declaraciones

void menuPrincipal();

bool solicitarUsuario();
void menuOperativo();
void menuAdministrativo();

int cantEmpleados = 0;
void leerArchivo();

struct Area* listarAreas();
struct Empleado* listarEmpleados();
struct ValoresIniciales cargarValoresIniciales();
void generarNomina();
struct Empleado* agregarEmpleados(int *pCantidadNomina);
bool enNomina(int cedula, struct Empleado *nomina, int j);

void generarFactura();
struct Producto* menuProductos();
struct Producto* agregarProducto(struct Producto *productosFactura,struct Producto *lProductos, int pcantidadProductos, int *j);
struct Producto* eliminarProducto(struct Producto *productosFactura, int *j);
struct Producto* listarProductos(int *pcantidadProductos);
bool enFactura(char *idProducto, struct Producto *factura, int j);
void listarNominas();
void listarFacturas();
void imprimirDetalleFactura(struct Factura *pFactura);
void imprimirNominas(struct Nomina *lNominas, int cantidad);
void imprimirEmpleados(struct Empleado *lEmpleados, int cantidad);
void imprimirProductos(struct Producto *lProductos, int cantidad, int mostrarCantidad);
void imprimirAreas(struct Area *lAreas, int cantidad);
void imprimirFacturas(struct Factura *lFacturas, int cantidad);
void listarBalances();
void imprimirBalances(struct Balance *lBalances, int cantidad,int imprimirMes);
int getNum(char* mesanio);
bool esNumero(char *token);
void pausa();
void salir();

#endif