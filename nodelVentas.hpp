#ifndef NODELVENTAS_HPP_INCLUDED
#define NODELVENTAS_HPP_INCLUDED

class NodoL
{
public:

    NodoL();
    void setNext(NodoL*);
    void setPrev(NodoL*);
    void setLeft(NodoL*);
    void setRight(NodoL*);
    void setFrecuencia(int);
    void setCaracter(char);
    void aumentarFrecuencia();

    NodoL* getNext();
    NodoL* getPrev();
    NodoL* getLeft();
    NodoL* getRight();
    int getFrecuencia();
    char getCaracter();

private:

    int frecuencia;
    char caracter;

    NodoL* next;
    NodoL* prev;
    NodoL* left;
    NodoL* right;

};

#endif // NODELVENTAS_HPP_INCLUDED
