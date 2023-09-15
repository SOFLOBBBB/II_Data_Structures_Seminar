#include "interfaz.hpp"
#include <iostream>
#include <iomanip> // Para setw
#include <cstdlib> // Para system
#include <unistd.h> // Para usleep
#include "producto.hpp"
#include "pedido.hpp"
#include "proveedor.hpp"

InterfazUsuario::InterfazUsuario()
{
    // Constructor
}

InterfazUsuario::~InterfazUsuario()
{
    // Destructor
}

void InterfazUsuario::LimpiarPantalla()
{
    system("cls");
}

void InterfazUsuario::MostrarManiqui()
{
    // ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ----------------------------------------------------=----------------------------------------------------
// ---------------------------------------------------===---------------------------------------------------
// -----------------------------------------------==-=====-==-----------------------------------------------
// ---------------------------------------------=*##*=====*##*=---------------------------------------------
// ---------------------------------------------=:+##*===*##*:=---------------------------------------------
// ---------------------------------------------=. =##*=*##= .----------------------------------------------
// ---------------------------------------------=-  :#####- .+=---------------------------------------------
// ---------------------------------------------+#*. .*#*. :##=---------------------------------------------
// ----------------------------------------------*##-  -  =##+----------------------------------------------
// ----------------------------------------------:=##*. .*##-:----------------------------------------------
// -----------------------------------------------:.*##+##*..-----------------------------------------------
// -----------------------------------------------:  =###=  ------------------------------------------------
// ----------------------------------------------=#+. .+: .*#-----------------------------------------------
// -----------------------------------------------###:   -##*:----------------------------------------------
// ---------------------------------------------: .+##+.+##=  ----------------------------------------------
// ---------------------------------------------+-  :#####: .+*---------------------------------------------
// ---------------------------------------------*#*. .+#+. -##*---------------------------------------------
// ---------------------------------------------:*##=  .  +##+.---------------------------------------------
// ---------------------------------------------. -##*: :*##- .---------------------------------------------
// ----------------------------------------------. .*##+##+. :*---------------------------------------------
// ---------------------------------------------+#:  -###-  =#*---------------------------------------------
// ---------------------------------------------=##+. .+. .*##=---------------------------------------------
// ---------------------------------------------::###-   -##*..---------------------------------------------
// ----------------------------------------------  =##+:+##=  :---------------------------------------------
// ----------------------------------------------.. :*###*:...----------------------------------------------
// ---------------------------------------------------=+=---------------------------------------------------
// ---------------------------------------------------+++---------------------------------------------------
// ---------------------------------------------------=++---------------------------------------------------
// ---------------------------------------------------=++---------------------------------------------------
// ---------------------------------------------------=+=---------------------------------------------------
// ---------------------------------------------------=+=---------------------------------------------------
// ---------------------------------------------------=++---------------------------------------------------
// ---------------------------------------------------+++=--------------------------------------------------
// --------------------------------------------=++--=++++++-=++=--------------------------------------------
// --------------------------------------------+---+=-=+=-==---+--------------------------------------------
// --------------------------------------------=+=++--=+=--++=++--------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------

}

void InterfazUsuario::MenuPrincipal()
{
    int opc;

    do
    {
        LimpiarPantalla();
        std::cout << "\033[1;33m"; // Cambiar el color del texto a amarillo brillante
        MostrarManiqui();
        std::cout << "\033[0m"; // Restaurar el color del texto a predeterminado
        std::cout << "==============================\n";
        std::cout << "     Menu Principal\n";
        std::cout << "==============================\n";
        std::cout << "1. Menu de Productos\n";
        std::cout << "2. Menu de Pedidos\n";
        std::cout << "3. Menu de Proveedores\n";
        std::cout << "4. Salir\n";
        std::cout << "==============================\n";
        std::cout << "Selecciona la opcion (1-4): ";
        std::cin >> opc;
        std::cin.ignore();

        switch (opc)
        {
        case 1:
            MenuProductos(); // Ir al menú de productos
            break;

        case 2:
            MenuPedidos(); // Ir al menú de pedidos
            break;

        case 3:
            MenuProveedores(); // Ir al menú de proveedores
            break;

        case 4:
            std::cout << "¡Hasta luego!...\n";
            break;

        default:
            std::cout << "Opcion no válida\n";
        }
    }
    while (opc != 4);
    usleep(1000000); // Pausa de 1 segundo (1,000,000 microsegundos)
}

void InterfazUsuario::MenuProductos()
{
    int opc;
    Producto producto;

    do
    {
        LimpiarPantalla();
        std::cout << "\033[1;33m"; // Cambiar el color del texto a amarillo brillante
        MostrarManiqui();
        std::cout << "\033[0m"; // Restaurar el color del texto a predeterminado
        std::cout << "==============================\n";
        std::cout << "     Menu de Productos\n";
        std::cout << "==============================\n";
        std::cout << "1. Capturar Producto\n";
        std::cout << "2. Mostrar Productos\n";
        std::cout << "3. Buscar Producto\n";
        std::cout << "4. Eliminar Producto\n";
        std::cout << "5. Modificar Producto\n";
        std::cout << "6. Regresar al Menu Principal\n";
        std::cout << "==============================\n";
        std::cout << "Selecciona la opcion (1-6): ";
        std::cin >> opc;
        std::cin.ignore();

        switch (opc)
        {
        case 1:
            producto.Capturar();
            break;

        case 2:
            producto.Mostrar();
            break;

        case 3:
            producto.Buscar();
            break;

        case 4:
            producto.Eliminar();
            break;

        case 5:
            producto.Modificar();
            break;

        case 6:
            return; // Regresar al Menu Principal

        default:
            std::cout << "Opcion no válida\n";
        }
    }
    while (opc != 6);
}

void InterfazUsuario::MenuPedidos()
{
    int opc;
    Pedidos pedidos;
    do
    {
        LimpiarPantalla();
        std::cout << "\033[1;33m"; // Cambiar el color del texto a amarillo brillante
        MostrarManiqui();
        std::cout << "\033[0m"; // Restaurar el color del texto a predeterminado
        std::cout << "==============================\n";
        std::cout << "       Menu de Pedidos\n";
        std::cout << "==============================\n";
        std::cout << "1. Agregar Pedido\n";
        std::cout << "2. Mostrar Pedidos\n";
        std::cout << "3. Buscar Pedido\n";
        std::cout << "4. Modificar Pedido\n";
        std::cout << "5. Eliminar Pedido\n";
        std::cout << "6. Regresar al Menu Principal\n";
        std::cout << "==============================\n";
        std::cout << "Selecciona la opcion (1-6): ";
        std::cin >> opc;
        std::cin.ignore();

        switch (opc)
        {
        case 1:
            char codigoProducto[10];
            int cantidad;
            std::cout << "Ingrese el codigo del producto: ";
            std::cin.getline(codigoProducto, 10);
            std::cout << "Ingrese la cantidad: ";
            std::cin >> cantidad;
            pedidos.Agregar(codigoProducto, cantidad);
            break;

        case 2:
            pedidos.MostrarPedidos();
            break;

        case 3:
            char codigoBusqueda[10];
            std::cout << "Ingrese el codigo del producto a buscar: ";
            std::cin.ignore();
            std::cin.getline(codigoBusqueda, 10);
            pedidos.Buscar(codigoBusqueda);
            break;

        case 4:
            char codigoModificacion[10];
            int nuevaCantidad;
            std::cout << "Ingrese el codigo del producto a modificar: ";
            std::cin.ignore();
            std::cin.getline(codigoModificacion, 10);
            std::cout << "Ingrese la nueva cantidad: ";
            std::cin >> nuevaCantidad;
            pedidos.Modificar(codigoModificacion, nuevaCantidad);
            break;

        case 5:
            char codigoEliminar[10];
            std::cout << "Ingrese el codigo del producto a eliminar: ";
            std::cin.ignore();
            std::cin.getline(codigoEliminar, 10);
            pedidos.Eliminar(codigoEliminar);
            break;

        case 6:
            return; // Regresar al Menu Principal

        default:
            std::cout << "Opcion no válida\n";
        }
    }
    while (opc != 6);
}

void InterfazUsuario::MenuProveedores()
{
    int opc;
    Proveedor proveedor;
    do
    {
        LimpiarPantalla();
        std::cout << "\033[1;33m"; // Cambiar el color del texto a amarillo brillante
        MostrarManiqui();
        std::cout << "\033[0m"; // Restaurar el color del texto a predeterminado
        std::cout << "==============================\n";
        std::cout << "     Menu de Proveedores\n";
        std::cout << "==============================\n";
        std::cout << "1. Agregar Proveedor\n";
        std::cout << "2. Mostrar Proveedores\n";
        std::cout << "3. Buscar Proveedor\n";
        std::cout << "4. Modificar Proveedor\n";
        std::cout << "5. Eliminar Proveedor\n";
        std::cout << "6. Regresar al Menu Principal\n";
        std::cout << "==============================\n";
        std::cout << "Selecciona la opcion (1-6): ";
        std::cin >> opc;
        std::cin.ignore();

        switch (opc)
        {
        case 1:
            proveedor.Capturar();
            break;

        case 2:
            proveedor.Mostrar();
            break;

        case 3:
            proveedor.Buscar();
            break;

        case 4:
            proveedor.Modificar();
            break;

        case 5:
            proveedor.Eliminar();
            break;

        case 6:
            return; // Regresar al Menu Principal

        default:
            std::cout << "Opcion no válida\n";
        }
    }
    while (opc != 6);
}