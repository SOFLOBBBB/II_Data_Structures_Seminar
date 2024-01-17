#include "nodelVentas.hpp"

NodoL::NodoL()
{
    next = nullptr;
    prev = nullptr;
    left = nullptr;
    right = nullptr;
    caracter = '-';
    frecuencia = 0;
}

void NodoL::setNext(NodoL*p)
{
    next = p;
}

void NodoL::setPrev(NodoL*p)
{
    prev = p;
}

void NodoL::setLeft(NodoL*p)
{
    left = p;
}

void NodoL::setRight(NodoL*p)
{
    right = p;
}

void NodoL::setFrecuencia(int f)
{
    frecuencia = f;
}

void NodoL::aumentarFrecuencia()
{
    frecuencia++;
}

void NodoL::setCaracter(char c)
{
    caracter = c;
}

NodoL* NodoL::getNext()
{
    return next;
}

NodoL* NodoL::getPrev()
{
    return prev;
}

NodoL* NodoL::getLeft()
{
    return left;
}

NodoL* NodoL::getRight()
{
    return right;
}

int NodoL::getFrecuencia()
{
    return frecuencia;
}

char NodoL::getCaracter()
{
    return caracter;
}
