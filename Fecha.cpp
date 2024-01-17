#include "fecha.hpp"

using namespace std;

Fecha::Fecha(){}

int Fecha::getDia()const
{
    return Dia;
}

void Fecha::setDia(const int& aux)
{
    Dia = aux;
}

int Fecha::getMes()const
{
    return Mes;
}

void Fecha::setMes(const int& aux)
{
    Mes = aux;
}

int Fecha::getAnio()const
{
    return Anio;
}

void Fecha::setAnio(const int& aux)
{
    Anio = aux;
}

string Fecha::toString()
{
    return to_string(Dia) + " / " + to_string(Mes) + " / " +  to_string(Anio);
}
