#ifndef PRODUCTO_HPP_INCLUDED
#define PRODUCTO_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string.h>

class Producto {
public:
    Producto();
    ~Producto();
    Producto(const Producto& other);

    void Capturar();
    void Mostrar();
    void Buscar();
    void Eliminar();
    void Modificar();

private:
    char codigo[10], descripcion[35], precio[15];
};

#endif // PRODUCTO_HPP_INCLUDED