#include "Producto.hpp"

using namespace std;

Producto::Producto(){}

string Producto::getExistencias()const
{
    return Existencias;
}

void Producto::setExistencias(const string& aux)
{
    Existencias = aux;
}

int Producto::getPrecio()const
{
    return Precio;
}

void Producto::setPrecio(const int& aux)
{
    Precio = aux;
}

string Producto::getNombre()const
{
    return Nombre;
}

void Producto::setNombre(const string& aux)
{
    Nombre = aux;
}

string Producto::getCodigo()const
{
    return Codigo;
}

void Producto::setCodigo(const string& aux)
{
    Codigo = aux;
}

string Producto::getProveedor()const
{
    return Proveedor;
}

void Producto::setProveedor(const string& aux)
{
    Proveedor = aux;
}

string Producto::getDescripcion()const
{
    return Descripcion;
}

void Producto::setDescripcion(const string& aux)
{
    Descripcion = aux;
}

string Producto::getTipo()const
{
    return Tipo;
}

void Producto::setTipo(const string& aux)
{
    Tipo = aux;
}

Fecha Producto::getFecha()const
{
    return fecha;
}

void Producto::setFecha(const Fecha& aux)
{
    fecha = aux;
}

///**********************************************************

string Producto::toString() const
{
    return " - CODIGO: " + Codigo + "\t| NOMBRE: " + Nombre + "\t| TIPO: " + Tipo + "\t| FECHA: " /*+ fecha */+   "\t| PROVEEDOR: " + Proveedor + "\t| DESCRIPCION: " + Descripcion + "\t| EXISTENCIAS: " + Existencias;
}

///**********************************************************

bool Producto::operator==(const Producto& c) const
{
    return Nombre==(c.Nombre);
}

bool Producto::operator!=(const Producto& c) const
{
    return Nombre!=(c.Nombre);
}

bool Producto::operator<(const Producto& c) const
{
    return Nombre<(c.Nombre);
}

bool Producto::operator<=(const Producto& c) const
{
    return Nombre<=(c.Nombre);
}

bool Producto::operator>(const Producto& c) const
{
    return Nombre>(c.Nombre);
}

bool Producto::operator>=(const Producto& c) const
{
    return Nombre>=(c.Nombre);
}

///**********************************************************

int Producto::compareNombre(const Producto& a, const Producto& b)
{
    return a.Nombre.compare(b.Nombre);
}

int Producto::compareCodigo(const Producto& a, const Producto& b)
{
    return a.Codigo.compare(b.Codigo);
}


int Producto::compareTipo(const Producto& a, const Producto& b)
{
    return a.Tipo.compare(b.Tipo);
}
