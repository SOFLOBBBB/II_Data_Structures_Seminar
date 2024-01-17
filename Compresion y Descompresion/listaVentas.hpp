#ifndef LISTAVENTAS_HPP_INCLUDED
#define LISTAVENTAS_HPP_INCLUDED

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#include <fstream>

#include "nodelVentas.hpp"

using namespace std;

class List
{
public:
    List();
    ~List();

    bool isEmpty();
    NodoL* insertData(NodoL* n, int, char);
    void deleteData(NodoL* n);

    NodoL* getFirst();
    NodoL* getLast();
    NodoL* getNext(NodoL*);
    NodoL* getPrev(NodoL*);

    NodoL* findDataChar(char);
    NodoL* findDataF(int i);
    void intercambio(NodoL*, NodoL*);
    void ordenarLista();

    void imprimirLista();
    void clear();

    //Lista A Arbol

    void convertirToArbol();
    void insertArbol(NodoL*n, NodoL*);
    NodoL* deleteArbol(NodoL*);
    void mostrarArbol(NodoL*, int);

    void gotoxy(int x, int y);
    void mostrarArbol2(NodoL *, int x, int y);
    void mostrarArbol3(NodoL *r, int x);

    void diccionario(NodoL*, int);
    void imprimirDiccionario();
    int getHojas(NodoL*, int&);
    void transformarConDiccionario(string);
    void empaquetar();

    void conversionBinCar(string bin);
    int bin_to_Decimal(string byte);
    void guardarDiccionario();

    string getBinario() const;
    void setBinario(const string &value);

    //Descifrado

    void leerArchivo();
    string decimal_to_Bin(int dec);
    void cargarDiccionario();
    void compararDiccionario(string dato);

    int busqueda(string caract);


    char getCaract() const;
    void setCaract(char value);

    string cifrado;

private:

    string stringTotal;
    string binario;
    string codigo;
    int tamanio;

    size_t newtam;

    char caract;

    vector<char> v;
    vector<string> v2;


    int hojas;
    NodoL* H;
    bool isValid(NodoL*);

};

#endif // LISTAVENTAS_HPP_INCLUDED
