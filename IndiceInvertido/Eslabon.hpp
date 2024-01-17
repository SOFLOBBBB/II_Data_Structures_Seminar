#ifndef ESLABON_HPP_INCLUDED
#define ESLABON_HPP_INCLUDED

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

template < typename T > class Eslabon
{
	public:
		T dato;
		int enlace;
		Eslabon *next;
		Eslabon( const T &auxDato, const int auxEnlace, Eslabon *auxNext = NULL );
		Eslabon( Eslabon *auxNext = NULL );
};

template < typename T >
Eslabon< T >::Eslabon( const T &auxDato, const int auxEnlace, Eslabon *auxNext )
{
	enlace = auxEnlace;
	dato = auxDato;
	next = auxNext;
}

template < typename T >
Eslabon< T >::Eslabon( Eslabon *auxNext )
{
	next = auxNext;
}

#endif // ESLABON_HPP_INCLUDED
