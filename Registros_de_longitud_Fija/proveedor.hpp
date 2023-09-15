#ifndef PROVEEDOR_HPP_INCLUDED
#define PROVEEDOR_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

class Proveedor {
public:
    char codigo[10];
    char nombre[50];
    char direccion[100];
    char telefono[15];

    void Capturar();
    void Mostrar();
    void Modificar();
    void Buscar();
    void Eliminar();
};

#endif // PROVEEDOR_HPP_INCLUDED