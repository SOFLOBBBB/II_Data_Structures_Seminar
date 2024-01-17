#ifndef INTERFAZ_HPP_INCLUDED
#define INTERFAZ_HPP_INCLUDED

#include <fstream>
#include <conio.h>
#include <chrono>
#include <random>
#include <functional>
#include <windows.h>
#include <ctime>

#include "Producto.hpp"
#include "fecha.hpp"
#include "ListaCircular.hpp"
#include "Pedido.hpp"
#include "Proveedor.hpp"
#include "Cancelacion.hpp"
#include "Empleados.hpp"
#include "IndiceInvertido/Devoluciones.hpp"
#include "AyudaSoporteTecnico.hpp"
#include "usuario.hpp"
#include "Compresion y Descompresion/menuVentas.hpp"
#include "Grafos/MenuUsuarioGrafos.hpp"

class Interfaz
{
private:
    int opc;
    int contPed;
    int PrecioTotal;

public:
    Interfaz();

    void Menu();
    void Opciones();

    ///********** FUNCIONES *************

    /*( 1.0 )*/ void AgregarProductoDelim();
        /*( 1.0.1 )*/ void AgregarDesdeArchivoDelim();
    /*( 1.1 )*/ void AgregarProductoParam();
        /*( 1.1.1 )*/ void AgregarDesdeArchivoParam();
    /*( 1.2 )*/ void AgregarLongitudFija();


    /*( 2 )*/ void ImpresionDeProducto();
    /*( 3 )*/ void BuscarProducto();
    /*( 4 )*/ void ModificarProducto();
    /*( 5 )*/ void EliminarProducto();
    /*( 6 )*/ void PedidoGeneral();
        /*( 6.1 )*/ void PedidoAgregar();
        /*( 6.2 )*/ void PedidoModificar();
        /*( 6.3 )*/ void PedidoBuscar();
        /*( 6.4 )*/ void PedidoEliminar();
        /*( 6.4 )*/ void PedidoImprimir();


    ///********** DISEÑO ***********

    void cuadroCompleto();
    void rectaHorz(const int&, const int&, const int&);
    void rectaVert(const int&, const int&, const int&);
    void titulo(int, int);

    ///******** ATRIBUTOS **********

    int getOpc();
    void setOpc(int&);
    int getContPed();
    void setContPed(int&);

    ///************************************

};

void gotoxy(const int&, const int&);

#endif // INTERFAZ_HPP_INCLUDED
