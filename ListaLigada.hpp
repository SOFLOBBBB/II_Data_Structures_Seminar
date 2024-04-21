#ifndef LISTALIGADA_HPP_INCLUDED
#define LISTALIGADA_HPP_INCLUDED

#include "Assert.hpp"
#include "Eslabon.hpp"

template < typename T > class ListaLigada
{
	private:
		Eslabon< T > *ancla;
		Eslabon< T > *cola;
		Eslabon< T > *actual;
		int tamanio;
		void inicializar( void );
		void eliminarTodo( void );

	public:
	    //Constructor y Destructor
		ListaLigada( void );
		~ListaLigada( void );


		//Funciones (Metodos)
		void vaciar( void );

		T eliminar( void );

		void anterior( void );
		void next( void );

		void irAlInicio(void );
		void irAlFinal( void );

		int posicionActual( void ) const;
		void irAPosicion( int posicion );

		void insertar( const T &item, const int );
		void insertarAlFinal( const T &item, const int );

		void modificar( const T &, const int );

		int obtenerTamanio( void ) const;
		const T &obtenerDato( void ) const;
		const int obtenerEnlace( void ) const;
};

/// I M P L E M EN T A C I O N
//Constructor y destructor

template < typename T >
ListaLigada< T >::ListaLigada( void )
{
	inicializar();
}

template < typename T >
ListaLigada< T >::~ListaLigada( void )
{
	eliminarTodo();
}

template < typename T >
void ListaLigada< T >::inicializar( void )
{
	tamanio = 0;
	actual = cola = ancla = new Eslabon< T >;
}

template < typename T >
void ListaLigada< T >::eliminarTodo( void )
{
	while( ancla != NULL )
	{
		actual = ancla;
		ancla = ancla -> next;
		delete actual;
	}
}


//Funciones (Metodos)


template < typename T >
void ListaLigada< T >::vaciar( void )
{
	eliminarTodo();
	inicializar();
}

template < typename T >
T ListaLigada< T >::eliminar( void )
{
	Assert( tamanio != 0, "Lista vacia" );

	T item = actual -> next -> dato;
	Eslabon< T > *temporal = actual -> next;

	if( cola == actual -> next )
		cola = actual;

	actual -> next = actual -> next -> next;
	delete temporal;

	if( cola == actual )
		anterior();

	tamanio--;
	return item;
}

template < typename T >
void ListaLigada< T >::anterior( void )
{
	if( actual == ancla || actual == ancla -> next )
		return;

	Eslabon< T > *temporal = new Eslabon< T >( ancla );

	while( temporal -> next != actual )
		temporal = temporal -> next;

	actual = temporal;

}

template < typename T >
void ListaLigada< T >::next( void )
{
	if( actual -> next == cola )
		return;

	actual = actual -> next;
}

template < typename T >
void ListaLigada< T >::irAlInicio( void )
{
	actual = ancla;
}

template < typename T >
void ListaLigada< T >::irAlFinal( void )
{
	actual = cola;
	anterior();
}

template < typename T >
int ListaLigada< T >::posicionActual( void ) const
{
	Eslabon< T > *temporal;
	temporal = ancla;
	int i;

	for( i = 0; temporal != actual; i++ )
		temporal = temporal -> next;

	return i;
}

template < typename T >
void ListaLigada< T >::irAPosicion( int posicion )
{
	Assert( ( posicion >= 0 ) && ( posicion <= tamanio ), "Posicion fuera de rango" );

	actual = ancla;

	for( int i = 0; i < posicion; i++ )
		actual = actual -> next;
}

template < typename T >
void ListaLigada< T >::insertar( const T &item, const int valorEnlace )
{
	actual -> next = new Eslabon< T >( item, valorEnlace, actual -> next );
	if( cola == actual )
		cola = actual -> next;
	tamanio++;
}

template < typename T >
void ListaLigada< T >::insertarAlFinal( const T &item, const int valorEnlace )
{
	cola = cola -> next = new Eslabon< T >( item, valorEnlace, cola -> next );
	tamanio++;
}

template < typename T >
void ListaLigada< T >::modificar( const T &nuevo, const int valorEnlace )
{
	Assert( tamanio != 0, "Lista vacia" );
	actual -> next -> dato = nuevo;
	actual -> next -> enlace = valorEnlace;
}

template < typename T >
int ListaLigada< T >::obtenerTamanio( void ) const
{
	return tamanio;
}

template < typename T >
const T &ListaLigada< T >::obtenerDato( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> next -> dato;
}

template < typename T >
const int ListaLigada< T >::obtenerEnlace( void ) const
{
	Assert( tamanio != 0, "Lista vacia" );
	return actual -> next -> enlace;
}

#endif // LISTALIGADA_HPP_INCLUDED
