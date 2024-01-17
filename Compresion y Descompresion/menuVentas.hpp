#ifndef MENUVENTAS_H_INCLUDED
#define MENUVENTAS_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>

#include "ventas.hpp"
#include "listaVentas.hpp"

using namespace std;

class menuVentas
{
public:
    menuVentas();

    void crearVenta(Ventas &p);
    void mostrar(Ventas &p);
    void escribir(const Ventas &p);
    void MostrarVenta();
    void coding();

    void BuscarVenta();
    void ModificarVenta();
    void Eliminar_F_P();
    void Eliminar_L_P();
    void ActivarVenta();

    void Huffman();
    void cargarFrase();
    void mostrarLista();
    void listaOrdenada();
    void mostrarListaArbol();

    void mostrarDiccionario();

    void descifrado();

    void Menu();

    int getCont() const;
    void setCont(int value);

    string getTexto() const;
    void setTexto(const string &value);

private:

    int cont=0;
    List lista;
    string texto;

};

#endif // MENUVENTAS_H_INCLUDED
