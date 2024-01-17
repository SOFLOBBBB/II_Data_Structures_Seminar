#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

#include <string.h>
#include "fecha.hpp"

class Producto
{
private:
    std::string Existencias;
    int Precio;
    std::string Nombre;
    std::string Codigo;
    std::string Proveedor;
    std::string Descripcion;
    std::string Tipo;
    Fecha fecha;

public:
    Producto();

    std::string toString() const;

    std::string getExistencias() const;
    void setExistencias(const std::string&);
    int getPrecio()const;
    void setPrecio(const int&);
    std::string getNombre()const;
    void setNombre(const std::string&);
    std::string getCodigo()const;
    void setCodigo(const std::string&);
    std::string getProveedor()const;
    void setProveedor(const std::string&);
    std::string getDescripcion()const;
    void setDescripcion(const std::string&);
    std::string getTipo()const;
    void setTipo(const std::string&);
    Fecha getFecha()const;
    void setFecha(const Fecha&);

    ///*********************************************

    bool operator == (const Producto&) const;
    bool operator != (const Producto&) const;
    bool operator < (const Producto&) const;
    bool operator <= (const Producto&) const;
    bool operator > (const Producto&) const;
    bool operator >= (const Producto&) const;

    friend std::ofstream& operator << (std::ostream&, const Producto&);
    friend std::ifstream& operator >> (std::istream&, Producto&);

    ///********************************

    static int compareNombre(const Producto&, const Producto&);
    static int compareCodigo(const Producto&, const Producto&);
    static int compareTipo(const Producto&, const Producto&);

};

#endif // PRODUCTO_H_INCLUDED
