#ifndef CANCELACION_HPP_INCLUDED
#define CANCELACION_HPP_INCLUDED

#include <iostream>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <windows.h>

#include "Interfaz.hpp"

class Cancelacion
{
public:
    char codigo[10] = "";
    char Motivo[50] = "";
    char Sugerencia[50] = "";
    char correo[25] = "";
    char Fecha[10] = "";

    void Agregar();
    void Mostrar();
    void Modificar();
    void Buscar();
    void Eliminar();

    void menuOpciones();

};

#endif // CANCELACION_HPP_INCLUDED
