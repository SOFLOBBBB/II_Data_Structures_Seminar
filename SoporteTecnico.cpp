#include "SoporteTecnico.hpp"

using namespace std;

//Setters y getters

int SoporteTecnico::getOpcion()
{
    return opcion;
}

void SoporteTecnico::setOpcion(const int& aux)
{
    opcion =  aux;
}

char SoporteTecnico::getIdSolicitud()
{
    return *idSolicitud;
}

void SoporteTecnico::setIdSolicitud( const string &valorIdSolicitud )
{
    int longitud = valorIdSolicitud.size();
    longitud = ( longitud < 12 ? longitud : 11 );
    valorIdSolicitud.copy( idSolicitud, longitud );
    idSolicitud[ longitud ] = '\0';
}

char SoporteTecnico::getProblema()
{
    return *problema;
}

void SoporteTecnico::setProblema( const string &valorProblema )
{
    int longitud = valorProblema.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorProblema.copy( problema, longitud );
    problema[ longitud ] = '\0';
}

char SoporteTecnico::getFecha()
{
    return *fecha;
}

void SoporteTecnico::setFecha( const string &valorFecha )
{
    int longitud = valorFecha.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorFecha.copy( fecha, longitud );
    fecha[ longitud ] = '\0';
}

char SoporteTecnico::getEstadoActual()
{
    return *estadoActual;
}

void SoporteTecnico::setEstadoActual( const string &valorEstadoActual )
{
    int longitud = valorEstadoActual.size();
    longitud = ( longitud < 12 ? longitud : 11 );
    valorEstadoActual.copy( estadoActual, longitud );
    estadoActual[ longitud ] = '\0';
}

// Clase friend que nos ayuda con los archivos

ostream &operator<<( ostream &salida, const SoporteTecnico &soporteTec )
{
    salida << "idSolicitud:     " << soporteTec.idSolicitud << endl
            << "Problema:       " << soporteTec.problema << endl
            << "fecha:          " << soporteTec.fecha << endl
            << "Estado Actual:  " << soporteTec.estadoActual << endl;

    return salida;
}

// constructor
SoporteTecnico::SoporteTecnico( void )
{
    for( int i = 0; i < sizeof( idSolicitud ); idSolicitud[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( problema ); problema[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( fecha ); fecha[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( estadoActual ); estadoActual[ i++ ] = '\0' );
}


bool SoporteTecnico::contiene( const string &idSolicitudABuscar )
{
    if( buscarId( idSolicitudABuscar ) == -1 )
    {
        return false;
    }
    return true;
}

SoporteTecnico SoporteTecnico::pedirRegistro( void )
{
    SoporteTecnico registroARetornar;
    string cadena;

    cout << endl << "\n\n\t\t\tID del Pedido: " << "\n\n\t\t\t -- > ";
    fflush( stdin );
    getline( cin, cadena );
    while( contiene( cadena ) || cadena.size() == 0 )
    {
        cout << "\n\n\t\t\tEse ID ya existe o la cadena es invalida: " << "\n\n\t\t\t--> ";
        fflush( stdin );
        getline( cin, cadena );
    }
    registroARetornar.setIdSolicitud( cadena );

    cout << "\n\n\t\t\t¿Cual es el Problema? : " << "\n\n\t\t\t -- > ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setProblema( cadena );

    cout << "\n\n\t\t\tIngrese la Fecha: " << "\n\n\t\t\t -- > ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setFecha( cadena );

    cout << "\n\n\t\t\t¿Cual es el Estado del producto? : " << "\n\n\t\t\t -- > ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setEstadoActual( cadena );

    return registroARetornar;
}

void SoporteTecnico::genera( void )
{
    SoporteTecnico soport;
    int contador = 0;

    ofstream file( "dispersion.txt", ios::out );
    if( !file )
    {
        cout << "\n\n\t\t\tNo se pudo crear el archivo" << endl;
    }
    else
    {
        for( int i = 0; i < NUMREGISTROS; i++ )
        {
        	// indica cuantos registros hay en el contenedor
        	file.write(( char *) &contador, sizeof( int ) );
        	for( int j = 0; j < CONTENEDOR; j++ )
            {
            	file.write( ( char * ) &soport, sizeof( SoporteTecnico ) );
            }
        }
    }
    file.close();
}

int SoporteTecnico::dispersion( const char llave[ 12 ] )
{
    // llena la el sobrante de la llave con espacios
    char llaveCopia[ 12 ];
    strcpy( llaveCopia, llave );
    if( strlen( llaveCopia ) < 12 )
        for( int i = strlen( llaveCopia ); i < 12; i++ )
            llaveCopia[ i ] = ' ';
    llaveCopia[ 12 ] = '\0';

    // realiza el algoritmo
    long sum = 0;
    int j = 0;
    while( j < 12 )
    {
        sum = ( sum + 100 * llaveCopia[ j ] + llaveCopia[ j + 1 ] )  % 20000;
        j += 2;
    }
    return ( sum % 99 ); // retorna la posición donde se guardará el registros.

}

// retorna la posición donde se encontro el registro
long int SoporteTecnico::buscarId( const string &idABuscar )
{
    SoporteTecnico soport;
    int contador, posIndice;
    long int posByte;

    ifstream file( "dispersion.txt", ios::in );
    if( !file )
    {
        cout << "\n\n\t\t\tEl archivo no existe" << endl;
        file.close();
        return -1;
    }

    posIndice = dispersion( idABuscar.c_str() );
    posByte = posIndice * ( ( sizeof( SoporteTecnico ) * CONTENEDOR ) + sizeof( int ) );
    file.seekg( posByte, ios::beg );
    file.read( ( char * ) &contador, sizeof( int ) );
    if( contador > 0 )
    {
        for( int i = 0; i < CONTENEDOR; i++ )
        {
            file.read( ( char * ) &soport, sizeof( SoporteTecnico ) );
            if( strcmp( soport.idSolicitud, idABuscar.c_str() ) == 0 )
            {
                posByte = ( long )file.tellg() - sizeof( SoporteTecnico );
                file.close();
                return posByte;
            }
        }
    }

    file.close();
    return -1;
}

bool SoporteTecnico::agregar( const SoporteTecnico &nuevoSoport )
{
    SoporteTecnico soport;
    string cadena;
    int posIndice, contador;
    long int posByte;
    string idString = nuevoSoport.idSolicitud;

    if( contiene( idString ) )
    {
        return false;
    }

    fstream file( "dispersion.txt", ios::in | ios::out );
    posIndice = dispersion( nuevoSoport.idSolicitud );
    cout << "\n\n\t\t\tSe guardara en la posicion indice: " << posIndice << endl;
    posByte = posIndice * ( sizeof( SoporteTecnico ) * CONTENEDOR + sizeof( int ) );
    file.seekg( posByte, ios::beg );
    file.read( ( char * ) &contador, sizeof( int ) ); // lee el numero de registros en el contador
    if( contador < CONTENEDOR ) // si el contenedor no esta lleno
    {
        // aumenta el contador y lo escribe
        contador++;
        file.seekg( posByte, ios::beg );
        file.write( ( char * ) &contador, sizeof( int ) );

        // escribe el nuevo registro en el contenedor
        for( int i = 0; i < CONTENEDOR; i++ )
        {
            file.read( ( char * ) &soport, sizeof( SoporteTecnico ) );
            if( soport.idSolicitud[ 0 ] == '\0' )
            {
                file.seekg( ( long )file.tellg() - sizeof( SoporteTecnico ), ios::beg );
                file.write( ( char * ) &nuevoSoport, sizeof( SoporteTecnico ) );
                file.close();
                return true;
            }
        }

    }
    else
        cout << endl << "\n\n\t\t\tNo hay mas espacio para este registro" << endl;

    file.close();
    return false;
}

void SoporteTecnico::mostrar( void )
{
    SoporteTecnico soport;
    int contador;
    long int posByte;

    ifstream file( "dispersion.txt", ios::in );
    if( !file )
    {
        cout << "\n\n\t\t\tNo existe el archivo" << endl;
    }
    else
    {
        cout << endl;
        for( int i = 0; i < NUMREGISTROS; i++ )
        {
            file.read( ( char * ) &contador, sizeof( int ) );
            if( contador > 0 )
            {
                for( int j = 0; j < CONTENEDOR; j++ )
                {
                    cout << " " << j << endl;
                    file.read( ( char * ) &soport, sizeof( SoporteTecnico ) );
                    if( soport.idSolicitud[ 0 ] != '\0' )
                    {
                        cout << soport << endl;
                    }
                }
            }
            else
            {
                file.seekg( sizeof( SoporteTecnico ) * CONTENEDOR, ios::cur );
            }
        }
    }
    file.close();
}

bool SoporteTecnico::buscar( const string &idABuscar, SoporteTecnico &SoporteEncontrada )
{
    long int posByte;

    if( !contiene( idABuscar ) )
        return false;

    ifstream file( "dispersion.txt", ios::in );
    if( !file )
    {
        cout << "\n\n\t\t\tEl archivo no existe" << endl;
        file.close();
        return false;
    }

    posByte = buscarId( idABuscar );
    file.seekg( posByte, ios::beg );
    file.read( ( char * ) &SoporteEncontrada, sizeof( SoporteTecnico ) );
    file.close();
    return true;
}

bool SoporteTecnico::modificar( const string &idAModificar, const SoporteTecnico &SoporteNueva )
{
    SoporteTecnico registroLimpio, soport;
    int posIndiceAntiguo, posIndiceNuevo, contador;
    long int posByteAntiguo, posByteNuevo;

    if( !contiene( idAModificar ) )
        return false;

    fstream file( "dispersion.txt", ios::in | ios::out );
    if( !file )
    {
        cout << "\n\n\t\t\tEl archivo no exite" << endl;
        file.close();
        return false;
    }

    posIndiceAntiguo = dispersion( idAModificar.c_str() );
    posByteAntiguo = buscarId( idAModificar );
    posIndiceNuevo = dispersion( SoporteNueva.idSolicitud );
    posByteNuevo = posIndiceNuevo * ( sizeof( SoporteTecnico ) * CONTENEDOR + sizeof( int ) );

    if( posByteAntiguo == posByteNuevo )
    {
        file.seekg( posByteAntiguo, ios::beg );
        file.write( ( char * ) &SoporteNueva, sizeof(  SoporteTecnico) );
    }
    else
    {
        // quita el registro antiguo y resta uno al contador del contenedor
        file.seekg( posByteAntiguo, ios::beg );
        file.write( ( char * ) &registroLimpio, sizeof( SoporteTecnico ) );
        posByteAntiguo = posIndiceAntiguo * ( sizeof( SoporteTecnico ) * CONTENEDOR + sizeof( int ) );
        file.seekg( posByteAntiguo, ios::beg );
        file.read( ( char * ) &contador, sizeof( int ) );
        contador--;
        file.seekg( posByteAntiguo, ios::beg );
        file.write( ( char * ) &contador, sizeof( int ) );

        // intenta meter el nuevo registro en la nueva posicion
        file.seekg( posByteNuevo, ios::beg );
        file.read( ( char * ) &contador, sizeof( int ) );
        if( contador < CONTENEDOR )
        {
            // aumenta el contador y lo escribe
            contador++;
            file.seekg( posByteNuevo, ios::beg );
            file.write( ( char * ) &contador, sizeof( int ) );

            // escribe el nuevo registro en el contenedor
            for( int i = 0; i < CONTENEDOR; i++ )
            {
                file.read( ( char * ) &soport, sizeof( SoporteTecnico ) );
                if( soport.idSolicitud[ 0 ] == '\0' ) // si el lugar no esta ocupado
                {
                    file.seekg( ( long )file.tellg() - sizeof( SoporteTecnico ), ios::beg );
                    file.write( ( char * ) &SoporteNueva, sizeof( SoporteTecnico ) );
                    file.close();
                    return true;
                }
            }
        }
        else // el contenedor esta lleno
            return false;
    }
} // fin funcion modificar

bool SoporteTecnico::eliminar( const string &idAEliminar, SoporteTecnico &destinoEliminado )
{
    SoporteTecnico soport;
    int posIndice, posByte, contador;

    if( !contiene( idAEliminar ) )
        return false;

    fstream file( "dispersion.txt", ios::in | ios::out );
    if( !file )
    {
        cout << "\n\n\t\t\tEl archivo no exite" << endl;
        file.close();
        return false;
    }

    posIndice = dispersion( idAEliminar.c_str() );
    posByte = buscarId( idAEliminar );

    file.seekg( posByte, ios::beg );
    file.read( ( char * ) &destinoEliminado, sizeof(  SoporteTecnico) );
    file.seekg( posByte, ios::beg );
    file.write( ( char * ) &soport, sizeof(  SoporteTecnico) );

    posByte = posIndice * ( sizeof( SoporteTecnico ) * CONTENEDOR + sizeof( int ) );
    file.seekg( posByte, ios::beg );
    file.read( ( char * ) &contador, sizeof( int ) );
    contador--;
    file.seekg( posByte, ios::beg );
    file.write( ( char * ) &contador, sizeof( int ) );
    file.close();
    return true;
}

/// Main ( el menu de soporte tecnico )

void SoporteTecnico::menuSoporteTecnico()
{
    SoporteTecnico soport, SoporteBuscar, SoporteModificar, SoporteEliminar, SoporteAgregar;
    string idABuscar, idAModificar, idAEliminar;
    char op;
    soport.genera();
    do
    {
        system( "cls" );
        opcionesMenu();
        switch( opcion )
        {
            case 49:
            {
                system( "cls" );
                SoporteAgregar = soport.pedirRegistro();
                if( soport.agregar( SoporteAgregar ) )
                {
                    cout << "\n\n\t\t\tCliente agregado con exito" << endl;
                }
                else
                {
                    cout << "\n\n\t\t\tNo se agrego la soporte" << endl;
                }
                getch();
            }break;
            case 50:
            {
                system( "cls" );
                soport.mostrar();
                getch();
            }break;
            case 51:
            {
                system( "cls" );
                cout << "\n\n\t\t\tIngrese el ID de la soporte a buscar: " << "\n\n\t\t\t--> ";
                fflush( stdin );
                getline( cin, idABuscar );
                if( soport.buscar( idABuscar, SoporteBuscar ) )
                {
                    cout << endl << SoporteBuscar << endl;
                }
                else
                {
                    cout << "\n\n\t\t\tNo existe el registro" << endl;
                }
                getch();
            }break;
            case 52:
            {
                system( "cls" );
                cout << "\n\n\t\t\tIngrese el ID de la soporte a modificar: " << "\n\n\t\t\t--> ";
                fflush( stdin );
                getline( cin, idAModificar );
                if( soport.buscar( idAModificar, SoporteBuscar ) )
                {
                    cout << endl << SoporteBuscar << endl;
                    cout << "\n\n\n\t\t\tDesea modificarlo?" << endl;
                    cout << "\n\n\t\t\t1) Si" << endl;
                    cout << "\n\n\t\t\t2) No" << endl << "\n\n\t\t\t--> ";
                    cin >> op;

                    if( op == '1' )
                    {
                        SoporteModificar = soport.pedirRegistro();
                        if( soport.modificar( idAModificar, SoporteModificar ) )
                        {
                            cout << endl << "\n\n\t\t\tSoporte modificada con exito" << endl;
                        }
                        else
                        {
                            cout << endl << "\n\n\t\t\tNo se pudo modificar" << endl;
                        }
                    }
                }
                else
                {
                    cout << "\n\n\t\t\tNo existe el registro" << endl;
                }
                getch();
            }break;
            case 53:
                {
                    system( "cls" );
                    cout << "\n\n\t\t\tIngrese el ID de la Soporte a eliminar: " << "\n\n\t\t\t--> ";
                    fflush( stdin );
                    getline( cin, idAEliminar );
                    if( soport.buscar( idAEliminar, SoporteBuscar ) )
                    {
                        cout << endl << SoporteBuscar << endl;
                        cout << "\n\n\n\t\t\tDesea eliminarlo?" << endl;
                        cout << "\n\n\t\t\t1) Si" << endl;
                        cout << "\n\n\t\t\t2) No" << endl << "\n\n\t\t\t--> ";
                        cin >> op;

                        if( op == '1' )
                        {
                            if( soport.eliminar( idAEliminar, SoporteEliminar ) )
                            {
                                cout << endl << SoporteEliminar << endl << "\n\n\t\t\tSE ELIMINO CORRECTAMENTE" << endl;
                            }
                            else
                            {
                                cout << "\n\n\t\t\tNO SE PUDO ELIMINAR" << endl;
                            }
                        }
                    }
                    else
                    {
                        cout << "\n\n\t\t\tNo existe el registro" << endl;
                    }
                    getch();
            }break;
            case 54:
            {  }break;
            default:
            {
                cout << "\n\n\n\n\t\t\t El Valor ingresado es Incorrecto pruebe otro.";
                getch();
            }break;
        }
    }while(opcion != 54);
}

void SoporteTecnico::opcionesMenu()
{
    int auxOpcion;
    cout<<"\n\n\t\t\tB I E N V E N I D O     A L    S O P O R T E     T E C N I C O";
    cout<<"\n\n\t\t\t\t\tSeleccione   una   opcion" << endl;
    cout<< "\n\n\n\t\t\t| 1 | Agregar"   << endl;
    cout<< "\n\t\t\t| 2 | Mostrar"   << endl;
    cout<< "\n\t\t\t| 3 | Buscar"    << endl;
    cout<< "\n\t\t\t| 4 | Modificar" << endl;
    cout<< "\n\t\t\t| 5 | Eliminar"  << endl;
    cout<< "\n\t\t\t| 6 | S A L I R"    << endl << "\n\t\t\t--> ";
    auxOpcion = getch();
    setOpcion(auxOpcion);
}

