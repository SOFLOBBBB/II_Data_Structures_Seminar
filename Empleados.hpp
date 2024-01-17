#ifndef EMPLEADOS_HPP_INCLUDED
#define EMPLEADOS_HPP_INCLUDED

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <vector>

class Empleado
{
public:
    char rfc[14] = "";
    char nombre[30] = "";
    char seccion[30] = "";
    char correo[30] = "";
    char direccion[30] = "";


    char FechaEntrada[12] = "";

    void capturar();
    void buscar();
    void mostrar();
    void Modificar();
    void Eliminar();
    void Mostrar_Indice();
    void Orden();

    void menu();
};

class Indice
{
public:
    char rfc[14];
    long int pos;
};

#endif // EMPLEADOS_HPP_INCLUDED
