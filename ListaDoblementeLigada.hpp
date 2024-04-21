#ifndef LISTADOBLEMENTELIGADA_HPP_INCLUDED
#define LISTADOBLEMENTELIGADA_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "list.h"
#include "Assert.cpp"
#include "Eslabon.hpp"

template < typename T > class ListaDoblementeLigada
{
	private:
		Eslabon< T > *ancla;
		Eslabon< T > *cola;
		Eslabon< T > *actual;
		int tamanio;
		void inicializar( void );
		void eliminarTodo( void );

	public:
	    //Constructor y destructor
		ListaDoblementeLigada( void );
		~ListaDoblementeLigada( void );

		//Funciones (Metodos)
		void vaciar( void );

		T eliminar( void );

		void anterior( void );
		void siguiente( void );

		int posicionActual( void ) const;
		void irAPosicion( int posicion );

		void irAlInicio(void );
		void irAlFinal( void );

		void insertar( const T &item, const int enlace );
		void insertarAlFinal( const T &item, const int enlace );

		int obtenerTamanio( void ) const;

		const T &obtenerDato( void ) const;
		const int obtenerEnlace( void ) const;
};

///I M P L E M E N T A C I O N
//Constructor y Destructor

template < typename T >
ListaDoblementeLigada< T >::ListaDoblementeLigada( void )
{
	inicializar();
}

template < typename T >
ListaDoblementeLigada< T >::~ListaDoblementeLigada( void )
{
	eliminarTodo();
}

template < typename T >
void ListaDoblementeLigada< T >::inicializar( void )
{
	actual = ancla = new Eslabon< T >;
	ancla -> siguiente = cola = new Eslabon< T >( ancla );
	tamanio = 0;
}

template < typename T >
void ListaDoblementeLigada< T >::eliminarTodo( void )
{
	while( ancla != NULL )
	{
		actual = ancla;
		ancla = ancla -> siguiente;
		delete actual;
	}
}

//Metodos

template < typename T >
void ListaDoblementeLigada< T >::vaciar( void )
{
	eliminarTodo();
	inicializar();
}

template < typename T >
T ListaDoblementeLigada< T >::eliminar( void )
{
	Assert( tamanio != 0, "Lista vacia" );

	T item = actual -> elemento;
	Eslabon< T > *temporal = actual;
	actual -> siguiente -> anterior = actual -> anterior;
	actual -> anterior -> siguiente = actual -> siguiente;
	actual = actual -> anterior;
	delete temporal;
	tamanio--;
	return item;
}

template < typename T >
void ListaDoblementeLigada< T >::anterior( void )
{
	if( actual != ancla )
		actual = actual -> anterior;

}

template < typename T >
void ListaDoblementeLigada< T >::siguiente( void )
{
	if( tamanio != 0 )
		actual = actual -> siguiente;
}

template < typename T >
int ListaDoblementeLigada< T >::posicionActual( void ) const
{
	Eslabon< T > *temporal;
	temporal = ancla;
	int i;

	for( i = 0; temporal != actual; i++ )
		temporal = temporal -> siguiente;

	return i;
}

template < typename T >
void ListaDoblementeLigada< T >::irAPosicion( int posicion )
{
	Assert( ( posicion >= 0 ) && ( posicion < tamanio ), "Posicion fuera de rango" );

	actual = ancla;

	for( int i = 0; i < posicion; i++ )
		actual = actual -> siguiente;
}

template < typename T >
void ListaDoblementeLigada< T >::irAlInicio( void )
{
	if( tamanio != 0 )
		actual = ancla -> siguiente;
}

template < typename T >
void ListaDoblementeLigada< T >::irAlFinal( void )
{
	if( tamanio != 0 )
		actual = cola -> anterior;
}

template < typename T >
void ListaDoblementeLigada< T >::insertar( const T &item, const int enlace )
{
	actual = actual -> siguiente = actual -> siguiente -> anterior = new Eslabon< T >( item, enlace, actual, actual -> siguiente );
	tamanio++;
}

template < typename T >
void ListaDoblementeLigada< T >::insertarAlFinal( const T &item, const int enlace )
{
	actual = cola -> anterior = cola -> anterior -> siguiente = new Eslabon< T >( item, enlace, cola -> anterior, cola );
	tamanio++;
}

template < typename T >
int ListaDoblementeLigada< T >::obtenerTamanio( void ) const
{
	return tamanio;
}

template < typename T >
const T &ListaDoblementeLigada< T >::obtenerDato( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> elemento;
}

template < typename T >
const int ListaDoblementeLigada< T >::obtenerEnlace( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> enlace;
}

#endif // LISTADOBLEMENTELIGADA_HPP_INCLUDED
