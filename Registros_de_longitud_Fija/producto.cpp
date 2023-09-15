#include "producto.hpp"

Producto::Producto() {
    // Constructor
}

Producto::~Producto() {
    // Destructor
}

Producto::Producto(const Producto& other) {
    // Copy constructor
    strcpy(codigo, other.codigo);
    strcpy(descripcion, other.descripcion);
    strcpy(precio, other.precio);
}

void Producto::Capturar() {
    std::cout << "Dame el codigo del producto: ";
    std::cin.getline(codigo, 10);
    std::cout << "Dame la descripcion: ";
    std::cin.getline(descripcion, 35);
    std::cout << "Dame el precio: ";
    std::cin.getline(precio, 15);
    std::ofstream Archivo("Producto.txt", std::ios::app);
    Archivo << codigo << '|' << descripcion << '|' << precio << '|' << std::endl;
    Archivo.close();
}

void Producto::Mostrar() {
    std::ifstream Lectura("Producto.txt");
    if (!Lectura.good()) {
        std::cout << "No existe el archivo" << std::endl;
        system("pause");
    } else {
        while (!Lectura.eof()) {
            Lectura.getline(codigo, 10, '|');
            Lectura.getline(descripcion, 35, '|');
            Lectura.getline(precio, 15, '|');
            if (!Lectura.eof())
                std::cout << "\nCodigo: " << codigo << "\nDescripcion: " << descripcion << "\nPrecio: " << precio << std::endl;
        }
        system("pause");
    }
    Lectura.close();
}

void Producto::Buscar() {
    int iguales;
    char alubus[10];

    std::ifstream arc("Producto.txt");
    if (!arc.good()) {
        std::cout << "\nNO EXISTE ARCHIVO...\n";

    } else {
        std::cout << "\nEscribe el codigo del producto a buscar: ";
        std::cin.getline(alubus, 10);


        while (!arc.eof()) {
            arc.getline(codigo, 10, '|');
            arc.getline(descripcion, 35, '|');
            arc.getline(precio, 15, '|');
            iguales = strcmp(codigo, alubus);


            if (iguales == 0) {
                std::cout << "\nCODIGO: " << codigo << "\nDESCRIPCION: " << descripcion << "\nPRECIO: " << precio << std::endl << std::endl;
                system("pause");
                break;
            }
        }

        if (arc.eof()) {
            std::cout << "\n\nNO EXISTE EL REGISTRO...\n\n";
        }
        arc.close();
    }
}

void Producto::Eliminar() {
    int iguales, respuesta = 0;
    char alubus[10];

    std::ifstream arc("Producto.txt");
    if (!arc.good()) {
        std::cout << "\nNO EXISTE ARCHIVO...\n";
    } else {
        std::cout << "\nSe ha eliminado exitosamente el historial ";

        std::ifstream temp("temporalauto.txt", std::ios::app);
        std::ofstream temporal("temporalauto.txt", std::ios::app);

        while (!arc.eof()) {
            arc.getline(codigo, 10, '|');
            arc.getline(descripcion, 35, '|');
            arc.getline(precio, 15, '|');
            iguales = strcmp(codigo, alubus);

            if (iguales != 0) {
                temporal << codigo << '|' << descripcion << '|' << precio << '|' << std::endl;
            }
        }

        arc.close();
        temporal.close();
        remove("Producto.txt");
        rename("temporalauto.txt", "Producto.txt");

        std::cout << "\n\nEL REGISTRO FUE ELIMINADO...\n\n";
    }
}

void Producto::Modificar() {
    int opcion;
    char prodMod[10];
    bool b;

    std::ifstream Lectura("Producto.txt");
    std::ofstream LecturaTemporal("temporalauto.txt", std::ios::app);

    if (!Lectura.good()) {
        std::cout << "\nEL REGISTRO NO EXISTE\n";
    } else {
        std::cout << "\nIntroduce el codigo a modificar: ";
        std::cin.getline(prodMod, 10);

        b = false;

        while (!Lectura.eof()) {
            Lectura.getline(codigo, 10, '|');
            Lectura.getline(descripcion, 35, '|');
            Lectura.getline(precio, 15, '|');

            if (strcmp(codigo, prodMod) == 0 && !b) {
                std::cout << "\nCodigo: " << codigo << "\nDescripcion: " << descripcion << "\nPrecio: " << precio << std::endl;

                std::cout << "\n1) Modificar Codigo";
                std::cout << "\n2) Modificar Descripcion";
                std::cout << "\n3) Modificar Precio";
                std::cout << "\n4) Regresar";

                std::cout << "\n\nElige la opcion a realizar: ";
                std::cin >> opcion;

                std::cin.ignore(); // Consume el '\n' pendiente en el búfer

                switch (opcion) {
                    case 1:
                        std::cout << "\nNuevo Codigo: ";
                        std::cin.getline(codigo, 10);
                        break;
                    case 2:
                        std::cout << "\nNueva Descripcion: ";
                        std::cin.getline(descripcion, 35);
                        break;
                    case 3:
                        std::cout << "\nNuevo Precio: ";
                        std::cin.getline(precio, 15);
                        break;
                    default:
                        std::cout << "\nOpcion no valida" << std::endl;
                }

                if (opcion != 4 && opcion > 0 && opcion < 5)
                    b = true;
            }

            LecturaTemporal << codigo << '|' << descripcion << '|' << precio << '|' << std::endl;
        }

        Lectura.close();
        LecturaTemporal.close();

        if (!b)
            std::cout << "\nNo se encontro el registro" << std::endl;

        remove("Producto.txt");
        rename("temporalauto.txt", "Producto.txt");
    }
}