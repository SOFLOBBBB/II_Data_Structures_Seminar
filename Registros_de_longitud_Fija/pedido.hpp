#ifndef PEDIDO_HPP_INCLUDED
#define PEDIDO_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string.h>
#include <limits>

class Pedidos {
public:
    Pedidos();
    ~Pedidos();
    Pedidos(const Pedidos& other);

    void Agregar(const char* codigoProducto, int cantidad);
    void Imprimir();
    void Buscar(const char* codigoProducto);
    void Modificar(const char* codigoProducto, int nuevaCantidad);
    void Eliminar(const char* codigoProducto);
    void MostrarPedidos();

private:
    char codigoProducto[10];
    int cantidad;
};

#endif // PEDIDO_HPP_INCLUDED