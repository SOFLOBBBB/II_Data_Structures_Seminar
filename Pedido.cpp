#include "Pedido.hpp"

using namespace std;

Pedido::Pedido(){}

string Pedido::getDireccion()const
{
    return direccion;
}

void Pedido::setDireccion(const string& aux)
{
    direccion = aux;
}

int Pedido::getPrecioTotal()const
{
    return precioTotal;
}

void Pedido::setPrecioTotal(const int& aux)
{
    precioTotal += aux;
}

void Pedido::setPrecioTotalReinicio(const int& aux)
{
    precioTotal = aux;
}

string Pedido::getCodigo()const
{
    return codigo;
}

void Pedido::setCodigo(const string& aux)
{
    codigo = aux;
}

Producto Pedido::getProducto()const
{
    return product;
}

void Pedido::setProducto(const Producto& aux)
{
    product = aux;
}

Fecha Pedido::getFecha()const
{
    return fecha;
}

void Pedido::setFecha(const Fecha& aux)
{
    fecha = aux;
}

///**********************************************************

///Modificar

string Pedido::toString() const {}

///**********************************************************
