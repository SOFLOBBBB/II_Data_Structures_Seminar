#ifndef AYUDASOPORTETECNICO_H_INCLUDED
#define AYUDASOPORTETECNICO_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define NUMREGISTROS 100
#define CONTENEDOR   4

class Soporte
{
    private:
        int opcion;

        char id[ 12 ];
        char problema[ 35 ];
        char fecha[ 25 ];
        char estado[ 20 ];

        int dispersion( const char llave[ 12 ] );
        long int buscarId( const std::string & );

    public:
        Soporte( void );
        Soporte( const Soporte & );

        int getOpcion();
        void setOpcion( const int & );

        void setId( const std::string & );
        void setProblema( const std::string & );
        void setFecha( const std::string & );
        void setEstado( const std::string & );
        friend std::ostream &operator<<( std::ostream &, const Soporte & );

        bool agregar( const Soporte & );
        void mostrar( void );
        bool buscar( const std::string &, Soporte & );
        bool eliminar( const std::string &, Soporte & );
        bool modificar( const std::string &, const Soporte & );
        void mostrarIndice( void );
        Soporte pedirRegistro( void );
        bool contiene( const std::string & );
        void genera( void );

        void menu();
        void opcionesMenu();
};

#endif // AYUDASOPORTETECNICO_H_INCLUDED
