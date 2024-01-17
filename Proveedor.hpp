#ifndef PROVEEDOR_H_INCLUDED
#define PROVEEDOR_H_INCLUDED

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <conio.h>

class Proveedor
{
public:
    char codigo[10] = "";
    char nombre[20] = "";
    char telefono[12] = "";
    char correo[25] = "";
    char contrasena[12] = "";

    Proveedor();
    ~Proveedor();

    void Agregar();
    void Mostrar();
    void Modificar();
    void Buscar();
    void Eliminar();

    void menuOpciones();
};

#endif // PROVEEDOR_H_INCLUDED
