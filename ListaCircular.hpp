#ifndef LISTACIRCULAR_HPP_INCLUDED
#define LISTACIRCULAR_HPP_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <exception>
#include <chrono>
#include <random>
#include <functional>
#include <string>
#include <windows.h>
#include <ctime>

#include "Producto.hpp"
#include "fecha.hpp"

template <class T>
class Lista
{
    class Node;

public:
    class Excepcion: public std::exception
    {
    private:
        std::string msg;
    public:
        Excepcion() noexcept;
        Excepcion(const Excepcion& ex) noexcept : msg(ex.msg) {}
        Excepcion(const std::string& m) : msg(m) { }
        Excepcion& operator = (const Excepcion& ex) noexcept
        {
            msg = ex.msg;
        }
        virtual ~Excepcion() {}
        virtual const char* what() const noexcept
        {
            return msg.c_str();
        }
    };

    typedef Node* posicion;

    Lista();
    Lista(const Lista<T>&);

    ~Lista();

    bool isEmpty() const;


    void insertarProducto(const posicion&, const T&);
    void eliminarProducto(posicion&);
    void modificar(T&);
    //void invertir();

    //void ordenarAscen(int(const T&, const T&));
    //void ordenarDescen(int(const T&, const T&));

    //void ordenarAscenInt();
    //void ordenarDescenInt();

    posicion getPrimerPos() const;
    posicion getUltimoPos()const;
    posicion getAntePos(posicion)const;
    posicion getSigPos(posicion)const;

    posicion findProducto(const T&, int(const T&, const T&));

    posicion findProductoInt(const T&);

    void borraTodo();

    std::string toString() const;

    void print();
    void printInfo();

    T recupera (posicion) const;

    void moveTo(int);

    Producto anclaProducto();

    Lista <T>& operator = (const Lista <T>&);

    void gotoxy(const int&, const int&);

private:
    class Node
    {
    private:
        T Producto;
        posicion next;
        posicion prev;

    public:
        Node();
        Node(const T&);

        T getProducto() const;
        posicion getNext() const;
        posicion getPrev() const;


        void setProducto(const T&);
        void setNext(posicion);
        void setPrev(posicion);
    };

    posicion ancla;

    void copyAll(const Lista<T>&);
    bool isValidPos(posicion) const;

};

using namespace std;

///NODO

template <class T>
Lista<T>::Node::Node() : next(nullptr), prev(nullptr) {}

template <class T>
Lista<T>::Node::Node(const T& s) : Producto(s), prev(nullptr), next(nullptr) {}

template <class T>
T Lista<T>::Node::getProducto() const
{
    return Producto;
}

template <class T>
typename Lista<T>::posicion Lista<T>::Node::getNext() const
{
    return next;
}

template <class T>
typename Lista<T>::posicion Lista<T>::Node::getPrev() const
{
    return prev;
}

template <class T>
void Lista<T>::Node::setProducto(const T& s)
{
    Producto = s;
}

template <class T>
void Lista<T>::Node::setNext(posicion p)
{
    next = p;
}

template <class T>
void Lista<T>::Node::setPrev(posicion p)
{
    prev = p;
}

///LISTA

template <class T>
Lista<T>::Lista() : ancla (nullptr) {}

template <class T>
Lista<T>::Lista(const Lista<T>& l) : ancla(nullptr)
{
    copyAll(l);
}

template <class T>
Lista<T>::~Lista()
{
    borraTodo();
}

template <class T>
bool Lista<T>::isEmpty() const
{
    return ancla == nullptr;
}

template <class T>
void Lista<T>::insertarProducto(const posicion& p, const T& s)
{
    if (p != nullptr and !isValidPos(p))
    {
        throw Excepcion ("Posicion invalida, insertarProducto");
    }

    posicion aux(new Node(s));
    if (aux == nullptr)
    {
        throw Excepcion ("Memoria no disponible, insertarProducto");
    }

    if(p == nullptr)//insercion en el comienzo
    {
        if(ancla == nullptr)
        {
            aux->setPrev(aux);
            aux->setNext(aux);
        }
        else
        {
            aux->setPrev(ancla->getPrev());
            aux->setNext(ancla);

            ancla->getPrev()->setNext(aux);
            ancla->setPrev(aux);
        }
        ancla = aux;
    }
    else//insertar en cualquier otro sitio
    {
        aux->setPrev(p);
        aux->setNext(p->getNext());

        p->getNext()->setPrev(aux);
        p->setNext(aux);
    }
}

template <class T>
void Lista<T>::eliminarProducto(posicion& p)
{
    if(!isValidPos(p))
    {
        throw Excepcion("Posicion invalida, eliminarProducto");
    }

    p->getPrev()->setNext(p->getNext());
    p->getNext()->setPrev(p->getPrev());

    if(p == ancla)//Eliminar el primero
    {
        if(p->getNext() == p)
        {
            ancla = nullptr;
        }
        else
        {
            ancla = ancla->getNext();
        }
    }
    delete p;
}

template <class T>
typename Lista<T>::posicion Lista<T>::getPrimerPos() const
{
    return ancla;
}

template <class T>
typename Lista<T>::posicion Lista<T>::getUltimoPos() const
{
    if(isEmpty())
    {
        return nullptr;
    }

    return ancla->getPrev();
}

template <class T>
typename Lista<T>::posicion Lista<T>::getAntePos(posicion p) const
{
    if(p == ancla or !isValidPos(p))
    {
        return nullptr;
    }
    return p->getPrev();
}

template <class T>
typename Lista<T>::posicion Lista<T>::getSigPos(posicion p) const
{
    if(!isValidPos(p) or p == ancla->getPrev())
    {
        return nullptr;
    }
    return p->getNext();
}

template <class T>
typename Lista<T>::posicion Lista<T>::findProducto(const T &prod, int arti(const T&, const T&))
{
    if(!isEmpty())
    {
        posicion aux(ancla);
        do
        {
            if(arti(aux->getProducto(), prod)==0)
            {
                return aux;
            }
            aux = aux->getNext();
        }
        while(aux != ancla);
    }
    return nullptr;
}

template <class T>
void Lista<T>::modificar(T& e)
{
    Fecha date;
    string tempo;
    Producto tem;
    posicion aux(ancla);
    do
    {
        if(aux->getProducto() == e)
        {
            break;
        }
        aux = aux->getNext();
    }
    while(aux != ancla);

    if(aux->getProducto() == e)
    {
        gotoxy(20, 8);
        cout << "Dame el CODIGO nuevo:", gotoxy(20, 9);
        cout << " -->";
        gotoxy(25, 9);
        getline(cin,tempo);
        tem.setCodigo(tempo);
        gotoxy(20, 11);
        cout << "Dame el NOMBRE nuevo:", gotoxy(20, 12);
        cout << " -->";
        gotoxy(25, 12);
        getline(cin,tempo);
        tem.setNombre(tempo);
        gotoxy(20, 14);
        cout << "Dame el TIPO nuevo:", gotoxy(20, 15);
        cout << " -->";
        gotoxy(25, 15);
        getline(cin,tempo);
        tem.setTipo(tempo);
        gotoxy(20, 17);

        cout << "Dame el DIA / MES / ANIO nuevo: ", gotoxy(20, 18);
        cout << " -->";
        gotoxy(25, 18);
        getline(cin,tempo, '/');
        date.setDia(stoi(tempo.c_str()));
        getline(cin,tempo, '/');
        date.setMes(stoi(tempo.c_str()));
        getline(cin,tempo);
        date.setAnio(stoi(tempo.c_str()));
        tem.setFecha(date);

        gotoxy(20, 20);
        cout << "Dame el PRECIO nuevo:", gotoxy(20, 21);
        cout << " -->";
        gotoxy(25, 21);
        getline(cin,tempo);
        tem.setPrecio(stoi(tempo.c_str()));;
        gotoxy(20, 23);
        cout << "Dame el PROVEEDOR nuevo:", gotoxy(20, 24);
        cout << " -->";
        gotoxy(25, 24);
        getline(cin,tempo);
        tem.setProveedor(tempo);
        gotoxy(20, 26);
        cout << "Dame la DESCRIPCION nueva:", gotoxy(20, 27);
        cout << " -->";
        gotoxy(25, 27);
        getline(cin, tempo);
        tem.setDescripcion(tempo);
        gotoxy(20, 29);
        cout << "Dame las EXISTENCIAS nuevas:", gotoxy(20, 30);
        cout << " -->";
        gotoxy(25, 30);
        getline(cin, tempo);
        tem.setExistencias(tempo);
        aux->setProducto(tem);
    }
    else
    {
        cout << "El producto NO se encuentra" << endl;
    }
}

template <class T>
void Lista<T>::borraTodo()
{
    if(isEmpty())
    {
        return;
    }
    posicion aux;
    posicion mark(ancla);

    do
    {
        aux = ancla;
        ancla = ancla->getNext();
        delete aux;
    }
    while( ancla != mark);
    ancla = nullptr;
}


template <class T>
string Lista<T>::toString() const
{
    string resultado;
    if(!isEmpty())
    {
        posicion aux(ancla);
        do
        {
            resultado += aux->getProducto().toString() + "\n";
            aux = aux->getNext();
        }
        while(aux != ancla);
    }
    return resultado;
}

template <class T>
T Lista<T>::recupera(posicion p) const
{
    if(!isValidPos(p))
    {
        throw Excepcion ("Posicion invalida, recupera");
    }
    return p->getProducto();
}

///***********************************************************************

template <class T>
void Lista<T>::moveTo(int opc)
{
    int i=0;
    if (!isEmpty())
    {
        posicion temp = ancla;
        if(opc==1)
        {
            temp = temp->getNext();
            ancla=temp;
        }
        else if(opc==2)
        {
            temp = temp->getPrev();
            ancla=temp;
        }
    }
}

template <class T>
Producto Lista<T>::anclaProducto()
{
    return ancla->getProducto();
}

template <class T>
void Lista<T>::print()
{
    int x, y;
    if(!isEmpty())
    {
        posicion aux(ancla);
        y=5;
        x=4;
        gotoxy(x, y);
        cout << "-->";
        do
        {
            x=8;

            gotoxy(x, y);
            cout << aux->getProducto().getCodigo(); //CODIGO
            x=25;
            gotoxy(x, y);
            cout << aux->getProducto().getNombre(); //NOMBRE
            x=60;
            gotoxy(x, y);
            cout << aux->getProducto().getTipo(); //TIPO
            x=80;
            gotoxy(x, y);
            cout << aux->getProducto().getFecha().toString(); //FECHA
            x=100;
            gotoxy(x, y);
            cout << aux->getProducto().getPrecio(); //PRECIO
            x=120;
            gotoxy(x, y);
            cout << aux->getProducto().getProveedor(); //PROVEEDORES
            x=150;
            gotoxy(x, y);
            cout << aux->getProducto().getDescripcion(); //DESCRIPCION
            x=200;
            gotoxy(x, y);
            cout << aux->getProducto().getExistencias(); //EXISTENCIA
            y+=2;
            aux = aux->getNext();
        }
        while(aux != ancla);
    }
}

///**********************************************************************

template <class T>
Lista<T>& Lista<T>::operator=(const Lista<T>& l)
{
    borraTodo();
    copyAll(l);
    return *this;
}

template <class T>
void Lista<T>::copyAll(const Lista<T>& l)
{
    if(l.isEmpty())
    {
        return;
    }
    posicion aux (l.ancla);
    posicion last(nullptr);
    posicion newNode;

    do
    {
        if((newNode = new Node(aux->getProducto()))== nullptr)//esto puede fallar
        {
            throw Excepcion ("memoria insuficiente, copyAll");
        }

        if(last == nullptr)
        {
            ancla = newNode;
        }
        else
        {
            newNode->setPrev(last);
            last->setNext(newNode);
        }
        last =newNode;
        aux = aux->getNext();
    }
    while(aux != l.ancla);
    ancla->setPrev(last);
    last->setNext(ancla);
}

template <class T>
bool Lista<T>::isValidPos(posicion p) const
{
    if(!isEmpty())
    {
        posicion aux (ancla);

        do
        {
            if(aux==p)
            {
                return true;
            }
            aux =aux->getNext();
        }
        while(aux != ancla);
    }
    return false;
}

template <class T>
void Lista<T>::gotoxy(const int&x, const int&y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

#endif // LISTACIRCULAR_HPP_INCLUDED
