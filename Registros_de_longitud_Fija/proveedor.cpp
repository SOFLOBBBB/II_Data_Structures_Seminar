#include "proveedor.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

//void Proveedor::Capturar(){
/* std::cout << "CAPTURAR PROVEEDOR" << std::endl;
 std::cout << "Codigo: ";
 std::cin.getline(codigo, 10);
 std::cout << "Nombre: ";
 std::cin.getline(nombre, 50);
 std::cout << "Direccion: ";
 std::cin.getline(direccion, 100);
 std::cout << "Telefono: ";
 std::cin.getline(telefono, 15);

 std::ofstream archivo("proveedores.txt", std::ios::app);
 archivo.write((char*)this, sizeof(*this));
 archivo.close();*/

void Proveedor::Capturar()
{
    Proveedor proveedor;
    std::cout << "\t\t\nCAPTURAR PROVEEDOR\n" << std::endl;
    std::cout << "Codigo: ";
    std::cin.getline(proveedor.codigo, sizeof(proveedor.codigo));

    // Verifica si el código tiene más caracteres de los permitidos y trunca si es necesario
    if (strlen(proveedor.codigo) > sizeof(proveedor.codigo) - 1)
    {
        proveedor.codigo[sizeof(proveedor.codigo) - 1] = '\0';
    }

    std::cout << "Nombre: ";
    std::cin.getline(proveedor.nombre, sizeof(proveedor.nombre));
    if (strlen(proveedor.nombre) > sizeof(proveedor.nombre) - 1)
    {
        proveedor.nombre[sizeof(proveedor.nombre) - 1] = '\0';
    }

    std::cout << "Direccion: ";
    std::cin.getline(proveedor.direccion, sizeof(proveedor.direccion));
    if (strlen(proveedor.direccion) > sizeof(proveedor.direccion) - 1)
    {
        proveedor.direccion[sizeof(proveedor.direccion) - 1] = '\0';
    }

    std::cout << "Telefono: ";
    std::cin.getline(proveedor.telefono, sizeof(proveedor.telefono));
    if (strlen(proveedor.telefono) > sizeof(proveedor.telefono) - 1)
    {
        proveedor.telefono[sizeof(proveedor.telefono) - 1] = '\0';
    }

    std::ofstream archivo("proveedores.txt", std::ios::app | std::ios::binary);
    if (archivo)
    {
        archivo.write(reinterpret_cast<char*>(&proveedor), sizeof(proveedor));
        archivo.close();
    }
    else
    {
        std::cerr << "Error al abrir el archivo." << std::endl;
    }
}


void Proveedor::Mostrar()
{
    /*std::ifstream archivo("proveedores.txt");
    if (!archivo.good())
    {
        std::cout << "\nEl archivo no existe..." << std::endl;
    }
    else
    {
        std::cout << "PROVEEDORES REGISTRADOS" << std::endl;
        while (archivo.read((char*)this, sizeof(*this)))
        {
            std::cout << "Codigo: " << codigo << std::endl;
            std::cout << "Nombre: " << nombre << std::endl;
            std::cout << "Direccion: " << direccion << std::endl;
            std::cout << "Telefono: " << telefono << std::endl;
            std::cout << std::endl;
        }
        archivo.close();
    }*/
    Proveedor proveedor;
    std::ifstream archivo("proveedores.txt", std::ios::binary);
    if (!archivo)
    {
        std::cout << "\nEl archivo no existe..." << std::endl;
    }
    else
    {
        std::cout << "\t\t\nPROVEEDORES REGISTRADOS" << std::endl;
        while (archivo.read(reinterpret_cast<char*>(&proveedor), sizeof(proveedor)))
        {
            std::cout << "Codigo: " << proveedor.codigo << std::endl;
            std::cout << "Nombre: " << proveedor.nombre << std::endl;
            std::cout << "Direccion: " << proveedor.direccion << std::endl;
            std::cout << "Telefono: " << proveedor.telefono << std::endl;
            std::cout << std::endl;
        }
        system("pause");
        archivo.close();
    }

}

void Proveedor::Modificar()
{
    char valor[10];
    std::ifstream archivo("proveedores.txt");
    if (!archivo.good())
    {
        std::cout << "\nEl archivo no existe..." << std::endl;
    }
    else
    {
        std::cout << "\t\t\nMODIFICAR PROVEEDOR\n" << std::endl;
        std::cout << "\tIngrese el codigo del proveedor a modificar: ";
        std::cin.getline(valor, sizeof(valor));

        Proveedor proveedor;
        Proveedor proveedorModificado; // Crear una instancia para almacenar los datos modificados

        std::ofstream archivoTemp("temporal.txt", std::ios::app);

        while (archivo.read(reinterpret_cast<char*>(&proveedor), sizeof(proveedor)))
        {
            if (strcmp(proveedor.codigo, valor) == 0)
            {
                std::cout << "" << std::endl;
                std::cout << "Nuevo codigo: ";
                std::cin.getline(proveedorModificado.codigo, sizeof(proveedorModificado.codigo));
                if (strlen(proveedorModificado.codigo) > sizeof(proveedorModificado.codigo) - 1)
                {
                    proveedorModificado.codigo[sizeof(proveedorModificado.codigo) - 1] = '\0';
                }

                std::cout << "Nuevo nombre: ";
                std::cin.getline(proveedorModificado.nombre, sizeof(proveedorModificado.nombre));
                if (strlen(proveedorModificado.nombre) > sizeof(proveedorModificado.nombre) - 1)
                {
                    proveedorModificado.nombre[sizeof(proveedorModificado.nombre) - 1] = '\0';
                }

                std::cout << "Nueva dirección: ";
                std::cin.getline(proveedorModificado.direccion, sizeof(proveedorModificado.direccion));
                if (strlen(proveedorModificado.direccion) > sizeof(proveedorModificado.direccion) - 1)
                {
                    proveedorModificado.direccion[sizeof(proveedorModificado.direccion) - 1] = '\0';
                }

                std::cout << "Nuevo teléfono: ";
                std::cin.getline(proveedorModificado.telefono, sizeof(proveedorModificado.telefono));
                if (strlen(proveedorModificado.telefono) > sizeof(proveedorModificado.telefono) - 1)
                {
                    proveedorModificado.telefono[sizeof(proveedorModificado.telefono) - 1] = '\0';
                }

                archivoTemp.write(reinterpret_cast<char*>(&proveedorModificado), sizeof(proveedorModificado));
            }
            else
            {
                archivoTemp.write(reinterpret_cast<char*>(&proveedor), sizeof(proveedor));
            }
        }
        archivo.close();
        archivoTemp.close();
        remove("proveedores.txt");
        char oldname[] = "temporal.txt";
        char newname[] = "proveedores.txt";
        rename(oldname, newname);
    }
}

void Proveedor::Eliminar()
{
    char valor[10];
    int opcion = 0;
    std::ifstream archivo("proveedores.txt");
    if (!archivo.good())
    {
        std::cout << "\nEl archivo no existe..." << std::endl;
    }
    else
    {
        std::cout << "ELIMINAR PROVEEDOR" << std::endl;
        std::cout << "Ingrese el codigo del proveedor a eliminar: ";
        std::cin.getline(valor, sizeof(valor));

        Proveedor proveedor;
        std::ofstream archivoTemp("temporal.txt", std::ios::app);

        while (archivo.read(reinterpret_cast<char*>(&proveedor), sizeof(proveedor)))
        {
            if (strcmp(proveedor.codigo, valor) == 0)
            {
                std::cout << "\tProveedor Encontrado" << std::endl;
                std::cout << "Codigo: " << proveedor.codigo << std::endl;
                std::cout << "Nombre: " << proveedor.nombre << std::endl;
                std::cout << "Direccion: " << proveedor.direccion << std::endl;
                std::cout << "Telefono: " << proveedor.telefono << std::endl;
                std::cout << "¿DESEAS ELIMINAR?\n1.- SI\n0.- NO\n>: ";
                std::cin >> opcion;
                if (opcion == 1)
                {
                    // No escribir el proveedor en el archivo temporal
                }
                else
                {
                    archivoTemp.write(reinterpret_cast<char*>(&proveedor), sizeof(proveedor));
                }
            }
            else
            {
                archivoTemp.write(reinterpret_cast<char*>(&proveedor), sizeof(proveedor));
            }
        }
        archivo.close();
        archivoTemp.close();
        remove("proveedores.txt");
        char oldname[] = "temporal.txt";
        char newname[] = "proveedores.txt";
        rename(oldname, newname);
    }
}


void Proveedor::Buscar()
{
    char valor[10];
    std::ifstream archivo("proveedores.txt");
    if (!archivo.good())
    {
        std::cout << "\nEl archivo no existe..." << std::endl;
    }
    else
    {
        std::cout << "\t\tBUSCAR PROVEEDOR" << std::endl;
        std::cout << "Ingrese el codigo del proveedor a buscar: ";
        std::cin.getline(valor, sizeof(valor));

        Proveedor proveedor; // Crear una instancia de Proveedor para almacenar los datos encontrados

        while (archivo.read(reinterpret_cast<char*>(&proveedor), sizeof(proveedor)))
        {
            if (strcmp(proveedor.codigo, valor) == 0)
            {
                std::cout << "\tProveedor Encontrado" << std::endl;
                std::cout << "Codigo: " << proveedor.codigo << std::endl;
                std::cout << "Nombre: " << proveedor.nombre << std::endl;
                std::cout << "Direccion: " << proveedor.direccion << std::endl;
                std::cout << "Telefono: " << proveedor.telefono << std::endl;
                system("pause");
                return; // Salir después de encontrar el proveedor
            }
        }
        std::cout << "Proveedor no encontrado..." << std::endl;
    }
    archivo.close();
}