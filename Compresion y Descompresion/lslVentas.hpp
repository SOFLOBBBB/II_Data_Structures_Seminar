#ifndef LSLVENTAS_HPP_INCLUDED
#define LSLVENTAS_HPP_INCLUDED

#include <iostream>
#include <stdexcept>

#include "nodeLSLVentas.hpp"

using namespace std;

template<typename T>
class LSL
{
private:

    size_t listSize;
    NodoLSL* listFront;
    NodoLSL* listBack;

public:

    LSL()
    {
        listSize = 0;
        listFront = nullptr;
        listBack = nullptr;
    }

    LSL(const LSL& other)
    {
        listFront = nullptr;
        listBack = nullptr;
        listSize = 0;
        for(size_t i =0; i < other.size(); ++i)
            push_back(other[i]);
    }

    LSL& operator =(const LSL& other)
    {
        listFront = nullptr;
        listBack = nullptr;
        listSize = 0;
        for(size_t i =0; i < other.size(); ++i)
            push_back(other[i]);
        return this;
    }

    ~LSL()
    {
        clear();
    }

    bool empty() const;
    size_t size() const;
    void push_front(const T& elem);/*no pongo const afuera porque no quiero modificar el contenido de la lista*/
    void push_back(const T& elem);
    const T& front() const;
    const T& back() const;
    void pop_front();
    void pop_back();
    void insert(size_t position, const T& elem);
    void erase(size_t position);
    void clear();
    void remove(const T& value);
    T& operator[](size_t idx) const;

};


template<typename T>
bool LSL<T>::empty() const/*garantiza toda la info de la clase va a permanecer const*/
{
    return listSize == 0;
}

template<typename T>
size_t LSL<T>::size() const
{
    return  listSize;
}

template<typename T>
void LSL<T>::push_front(const T &elem)
{
    if(empty())
    {
        listFront = new NodoLSL(elem);/*new reserva memoria*/
        listBack = listFront;
    }
    else
    {
        NodoLSL* temp = new NodoLSL(elem, listFront);
        listFront = temp;
    }
    ++listSize;
}
template<typename T>
void LSL<T>::push_back(const T &elem)
{
    if(empty())
    {
        listFront = new NodoLSL(elem);/*new reserva memoria*/
        listBack = listFront;
    }
    else
    {
        NodoLSL* temp = new NodoLSL(elem);
        listBack -> siguiente = temp;
        listBack = temp;
    }
    ++listSize;
}

template<typename T>
const T &LSL<T>::front() const
{
    if(empty())
        throw invalid_argument("front() on empty list");
    return listFront -> dato;
}

template<typename T>
const T &LSL<T>::back() const
{
    if(empty())
        throw invalid_argument("back() on empty list");
    return listBack -> dato;
}

template<typename T>
void LSL<T>::pop_front()
{
    if(empty())
        throw invalid_argument("pop_front() on empty list");
    NodoLSL* eliminar = listFront;
    listFront = listFront -> siguiente;
    delete eliminar;
    eliminar = nullptr;
    --listSize;
}

template<typename T>
void LSL<T>::pop_back()
{
    if(empty())
        throw invalid_argument("pop_back() on empty list");
    NodoLSL* temp = listFront;
    while(temp -> siguiente != nullptr && temp -> siguiente != listBack)
        temp = temp -> siguiente;
    NodoLSL* eliminar = listBack;
    listBack = temp;
    listBack -> siguiente = nullptr;
    delete eliminar;
    eliminar = nullptr;
    --listSize;
}

template<typename T>
void LSL<T>::insert(size_t position, const T &elem)
{
    if(empty())
        throw invalid_argument("insert() on empty list");
    else if(position > listSize)
        throw invalid_argument("insert() on non valid position");
    else if(position == 0)
        push_front(elem);
    else if(position == listSize)
        push_back(elem);
    else
    {
        NodoLSL* temp = listFront;
        for(size_t i=0; i<position-1; ++i)
            temp = temp -> siguiente;
        NodoLSL* nuevo = new NodoLSL(elem, temp -> siguiente);
        temp -> siguiente = nuevo;
        ++listSize;
    }
}

template<typename T>
void LSL<T>::erase(size_t position)
{
    if(empty())
        throw invalid_argument("erase() on empty list");
    else if(position >= listSize)
        throw invalid_argument("erase() on non valid position");
    else if(position == 0)
        pop_front();
    else if(position == listSize-1)
        pop_back();
    else
    {
        NodoLSL* temp = listFront;
        for(size_t i=0; i< position-1;++i)
            temp = temp->siguiente;
        NodoLSL* eliminar = temp->siguiente;
        temp->siguiente = eliminar->siguiente;/*temp->siguiente->siguiente*/
        delete eliminar;
        eliminar = nullptr;
        --listSize;
    }
}

template<typename T>
void LSL<T>::clear()
{
    for(size_t i=0; i<listSize; ++i)
        pop_front();
    listFront = nullptr;
    listBack = nullptr;
    listSize = 0;
}

template<typename T>
void LSL<T>::remove(const T &value)
{
    if(empty())
        throw invalid_argument("remove() on empty list");
    NodoLSL* temp = listFront;
    T dato;
    size_t i = 0;
    while(temp != 0)
    {
        dato = temp->dato;
        temp = temp ->siguiente;
        if(dato == value)
        {
            erase(i); --i;
        }
        ++i;
    }
}

template<typename T>
T &LSL<T>::operator[](size_t idx) const
{
    if(empty())
        throw invalid_argument("[] on empty list");
    else if(idx >= listSize)
        throw  invalid_argument("index out of range");
    NodoLSL* temp = listFront;
    for(size_t i=0; i < idx; ++i)
        temp = temp->siguiente;
    return temp->dato;
}

#endif // LSLVENTAS_HPP_INCLUDED
