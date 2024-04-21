#ifndef FECHA_HPP_INCLUDED
#define FECHA_HPP_INCLUDED

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

class Fecha
{
private:
    int Dia;
    int Mes;
    int Anio;

public:
    Fecha();

    int getDia()const;
    void setDia(const int&);
    int getMes()const;
    void setMes(const int&);
    int getAnio()const;
    void setAnio(const int&);
    std::string toString();
};

#endif // FECHA_HPP_INCLUDED
