#ifndef NODELSLVENTAS_HPP_INCLUDED
#define NODELSLVENTAS_HPP_INCLUDED

#include <iostream>

struct NodoLSL
{
    T dato;
    NodoLSL* siguiente;
    NodoLSL(const T& elem, NodoLSL* sig = nullptr):
    dato(elem),
    siguiente(sig){}
};

#endif // NODELSLVENTAS_HPP_INCLUDED
