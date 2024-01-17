#include "ventas.hpp"

Ventas::Ventas(){ }

string Ventas::getProducto() const
{
    return producto;
}

void Ventas::setProducto(const string &value)
{
    producto = value;
}

string Ventas::getFecha() const
{
    return fecha;
}

void Ventas::setFecha(const string &value)
{
    fecha = value;
}

string Ventas::getPrecio() const
{
    return precio;
}

void Ventas::setPrecio(const string &value)
{
    precio = value;
}

string Ventas::getCodigo() const
{
    return codigo;
}

void Ventas::setCodigo(const string &value)
{
    codigo = value;
}

string Ventas::getBandera() const
{
    return bandera;
}

void Ventas::setBandera(const string &value)
{
    bandera = value;
}


