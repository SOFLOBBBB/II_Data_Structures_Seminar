#ifndef DEVOLUCIONES_HPP_INCLUDED
#define DEVOLUCIONES_HPP_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#include "ListaLigada.hpp"

#define TAM 100

using namespace std;

template < typename T >
void mostrar( ListaLigada< T > &L );


class IndiceSecundario
{
	public:
		char nombre[ 35 ] = "";
		int enlace;
};

class Ligada
{
	public:
		int id;
		int enlace;
};

class Devolucion
{
	private:
	    //Atributos
		char id[ 10 ] = "";
		char nombre[ 35 ] = "";
		char fecha[ 20 ] = "";
		char motivo[ 40 ] = "";
		char cantidad[ 10 ] = "";

        //Metodos  **PRIVADOS**
        int existeId( const int );

		int buscarEnIndice( const string & );
		int buscarEnLigado( const int );

            //Eliminaciones
		Devolucion eliminarEnArchDatos( const int );
		void eliminarEnNrrs( const int );
		void eliminarEnIndiceLigado( const int, const int );
		void eliminarEnIndiceDevolucions( const string & );

            //Modificaciones
		Devolucion modificarEnArchDatos( const int, const Devolucion& );
		void modificarEnNrrs( const int, const int );
		void modificarEnIndiceDevolucions(  const string &nombreAnterior, const string &nuevoNombre, const int idViejo, const int nuevoId );
		void modificarEnIndiceLigado( const string &, const int );

	public:
	    //Constructor y destructor
		Devolucion( void ){}
		Devolucion( const Devolucion & );

        //Getters y Setters
		char getNombre();
		void setNombre( const string & );

		char getFecha();
		void setFecha( const string & );

		char getMotivo();
		void setMotivo( const string & );

		char getCantidad();
		void setCantidad( const string & );

        char getId();
		void setId( const string & );

		//Funciones (Metodos)

		void inicializar( void );
		void guardar( void );

		Devolucion pedirRegistro( void );
		void agregar( const Devolucion & );
        bool eliminar( const int, Devolucion & );
        void modificar( const int, const Devolucion & );

            //Busqueda
		void buscarPorNombre( const string & );
		bool buscarId( const int, Devolucion & );

            //Mostrado
        void mostrarTodo( void );
        void mostrarLista( void );

        friend ostream &operator<<( ostream &, const Devolucion & );

        //Main de devoluciones
        void menuDevoluciones();

        //Decoracion
};

#endif // DEVOLUCIONES_HPP_INCLUDED
