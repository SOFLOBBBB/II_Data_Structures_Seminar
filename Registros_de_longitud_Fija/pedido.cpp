#include "pedido.hpp"
#include <limits>


Pedidos::Pedidos()
{
    // Constructor
}

Pedidos::~Pedidos()
{
    // Destructor
}

Pedidos::Pedidos(const Pedidos& other)
{
    // Constructor de copia
    strcpy(codigoProducto, other.codigoProducto);
    cantidad = other.cantidad;
}

void Pedidos::Agregar(const char* codigoProducto, int cantidad)
{
    std::ofstream archivo("Pedidos.txt", std::ios::app);
    archivo << codigoProducto << '|' << cantidad << '|' << std::endl;
    archivo.close();
}

void Pedidos::Imprimir()
{
    std::ifstream archivo("Pedidos.txt");
    if (!archivo.good())
    {
        std::cout << "No existe el archivo" << std::endl;
    }
    else
    {
        while (archivo.getline(codigoProducto, 10, '|'))
        {
            archivo >> cantidad;
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume el salto de línea

            std::cout << "\nCódigo del producto: " << codigoProducto << "\nCantidad: " << cantidad << std::endl;
            system("pause");
        }
    }
    archivo.close();
}

void Pedidos::Buscar(const char* codigoProducto)
{
    std::ifstream archivo("Pedidos.txt");
    if (!archivo.good())
    {
        std::cout << "\nNO EXISTE EL ARCHIVO...\n";
    }
    else
    {
        bool encontrado = false;
        while (archivo.getline(this->codigoProducto, 10, '|'))
        {
            archivo >> cantidad;
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume el salto de línea

            if (strcmp(this->codigoProducto, codigoProducto) == 0)
            {
                encontrado = true;
                std::cout << "\nCódigo del producto: " << this->codigoProducto << "\nCantidad: " << cantidad << std::endl;
                break;
            }
        }

        if (!encontrado)
        {
            std::cout << "\n\nNO EXISTE EL REGISTRO...\n\n";
        }
    }
    archivo.close();
}

void Pedidos::Modificar(const char* codigoProducto, int nuevaCantidad)
{
    std::ifstream archivo("Pedidos.txt");
    std::ofstream archivoTemporal("temporalpedidos.txt", std::ios::app);

    if (!archivo.good())
    {
        std::cout << "\nEL REGISTRO NO EXISTE\n";
    }
    else
    {
        while (archivo.getline(this->codigoProducto, 10, '|'))
        {
            archivo >> cantidad;
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume el salto de línea

            if (strcmp(this->codigoProducto, codigoProducto) == 0)
            {
                cantidad = nuevaCantidad;
            }

            archivoTemporal << this->codigoProducto << '|' << cantidad << '|' << std::endl;
        }

        archivo.close();
        archivoTemporal.close();

        remove("Pedidos.txt");
        rename("temporalpedidos.txt", "Pedidos.txt");
    }
}

void Pedidos::Eliminar(const char* codigoProducto)
{
    std::ifstream archivo("Pedidos.txt");
    std::ofstream archivoTemporal("temporalpedidos.txt", std::ios::app);

    if (!archivo.good())
    {
        std::cout << "\nNO EXISTE EL ARCHIVO...\n";
    }
    else
    {
        bool eliminado = false;
        while (archivo.getline(this->codigoProducto, 10, '|'))
        {
            archivo >> cantidad;
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume el salto de línea

            if (strcmp(this->codigoProducto, codigoProducto) != 0)
            {
                archivoTemporal << this->codigoProducto << '|' << cantidad << '|' << std::endl;
            }
            else
            {
                eliminado = true;
            }
        }

        archivo.close();
        archivoTemporal.close();

        remove("Pedidos.txt");
        rename("temporalpedidos.txt", "Pedidos.txt");

        if (eliminado)
        {
            std::cout << "\n\nEL REGISTRO FUE ELIMINADO...\n\n";
        }
        else
        {
            std::cout << "\n\nNO EXISTE EL REGISTRO...\n\n";
        }
    }
}

void Pedidos::MostrarPedidos()
{
    std::ifstream archivo("Pedidos.txt");
    if (!archivo.good())
    {
        std::cout << "No existe el archivo de pedidos" << std::endl;
    }
    else
    {
        while (archivo.getline(codigoProducto, 10, '|'))
        {
            archivo >> cantidad;
            archivo.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume el salto de línea

            std::cout << "\nCódigo del producto: " << codigoProducto << "\nCantidad: " << cantidad << std::endl;
        }
    }
    archivo.close();
}