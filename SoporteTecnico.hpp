#ifndef SOPORTETECNICO_HPP_INCLUDED
#define SOPORTETECNICO_HPP_INCLUDED

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define NUMREGISTROS 100
#define CONTENEDOR   4

class SoporteTecnico
{
private:
    int opcion;

    char idSolicitud[ 12 ] = "";
    char problema[ 35 ] = "";
    char fecha[ 25 ] = "";
    char estadoActual[20] = "";


    int dispersion( const char llave[ 12 ] );
    long int buscarId( const std::string & );

public:

    SoporteTecnico( void );
    SoporteTecnico( const SoporteTecnico & );

    int getOpcion();
    void setOpcion( const int & );

    char getIdSolicitud();
    void setIdSolicitud( const std::string & );
    char getProblema();
    void setProblema( const std::string & );
    char getFecha();
    void setFecha( const std::string & );
    char getEstadoActual();
    void setEstadoActual( const std::string & );

    friend std::ostream &operator<<( std::ostream &, const SoporteTecnico & );

    bool agregar( const SoporteTecnico & );
    void mostrar( void );
    bool buscar( const std::string &, SoporteTecnico & );
    bool eliminar( const std::string &, SoporteTecnico & );
    bool modificar( const std::string &, const SoporteTecnico & );
    void mostrarIndice( void );
    SoporteTecnico pedirRegistro( void );
    bool contiene( const std::string & );
    void genera( void );

    void menuSoporteTecnico();
    void opcionesMenu();

};

#endif // SOPORTETECNICO_HPP_INCLUDED
