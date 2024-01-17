#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include <string>

#include "fecha.hpp"
#include "Producto.hpp"

class Pedido
{
private:
    std::string direccion;
    int precioTotal;
    Producto product;
    std::string codigo;
    Fecha fecha;

public:
    Pedido();

    std::string getDireccion() const;
    void setDireccion(const std::string&);
    int getPrecioTotal() const;
    void setPrecioTotal(const int&);
    void setPrecioTotalReinicio(const int&);

    Producto getProducto() const;
    void setProducto(const Producto&);
    std::string getCodigo() const;
    void setCodigo(const std::string&);
    Fecha getFecha() const;
    void setFecha(const Fecha&);

    std::string toString() const;
};

#endif // PEDIDO_HPP
