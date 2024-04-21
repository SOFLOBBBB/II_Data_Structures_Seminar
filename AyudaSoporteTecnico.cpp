#include "AyudaSoporteTecnico.hpp"

using namespace std;

// constructor
Soporte::Soporte( void )
{
    for( int i = 0; i < sizeof( id ); id[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( problema ); problema[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( fecha ); fecha[ i++ ] = '\0' );
    for( int i = 0; i < sizeof( estado ); estado[ i++ ] = '\0' );
}


bool Soporte::contiene( const string &idABuscar )
{
    if( buscarId( idABuscar ) == -1 )
        return false;
    return true;
}


Soporte Soporte::pedirRegistro( void )
{
    Soporte registroARetornar;
    string cadena;

    cout << endl << "ID: ";
    fflush( stdin );
    getline( cin, cadena );
    while( contiene( cadena ) || cadena.size() == 0 )
    {
        cout << "Ese ID ya existe o la cadena es invalida: ";
        fflush( stdin );
        getline( cin, cadena );
    }
    registroARetornar.setId( cadena );

    cout << "Problema: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setProblema( cadena );

    cout << "Fecha: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setFecha( cadena );

    cout << "Estado: ";
    fflush( stdin );
    getline( cin, cadena );
    registroARetornar.setEstado( cadena );

    return registroARetornar;
}



void Soporte::genera( void )
{
    Soporte promo;
    int contador = 0;
    ofstream archivo( "dispersion2.txt", ios::out );
    if( !archivo )
        cout << "No se pudo crear el archivo" << endl;
    else
        for( int i = 0; i < NUMREGISTROS; i++ )
        {
        	// indica cuantos registros hay en el contenedor
        	archivo.write( ( char * ) &contador, sizeof( int ) );
        	for( int j = 0; j < CONTENEDOR; j++ )
            	archivo.write( ( char * ) &promo, sizeof( Soporte ) );
        }
    archivo.close();
}

int Soporte::dispersion( const char llave[ 12 ] )
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
long int Soporte::buscarId( const string &idABuscar )
{
    Soporte promo;
    int contador, posIndice;
    long int posByte;

    ifstream archivo( "dispersion2.txt", ios::in );
    if( !archivo )
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return -1;
    }

    posIndice = dispersion( idABuscar.c_str() );
    posByte = posIndice * ( ( sizeof( Soporte ) * CONTENEDOR ) + sizeof( int ) );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &contador, sizeof( int ) );
    if( contador > 0 )
    {
        for( int i = 0; i < CONTENEDOR; i++ )
        {
            archivo.read( ( char * ) &promo, sizeof( Soporte ) );
            if( strcmp( promo.id, idABuscar.c_str() ) == 0 )
            {
                posByte = ( long )archivo.tellg() - sizeof( Soporte );
                archivo.close();
                return posByte;
            }
        }
    }

    archivo.close();
    return -1;
}

void Soporte::setId( const string &valorId )
{
    int longitud = valorId.size();
    longitud = ( longitud < 12 ? longitud : 11 );
    valorId.copy( id, longitud );
    id[ longitud ] = '\0';
}

void Soporte::setProblema( const string &valorproblema )
{
    int longitud = valorproblema.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorproblema.copy( problema, longitud );
    problema[ longitud ] = '\0';
}

void Soporte::setFecha( const string &valorfecha )
{
    int longitud = valorfecha.size();
    longitud = ( longitud < 35 ? longitud : 34 );
    valorfecha.copy( fecha, longitud );
    fecha[ longitud ] = '\0';
}

void Soporte::setEstado( const string &valorEstado )
{
    int longitud = valorEstado.size();
    longitud = ( longitud < 12 ? longitud : 11 );
    valorEstado.copy( estado, longitud );
    estado[ longitud ] = '\0';
}

ostream &operator<<( ostream &salida, const Soporte &soporte )
{
    salida << "ID:        " << soporte.id << endl
            << "Producto:  " << soporte.problema << endl
            << "Fecha: " << soporte.fecha << endl
            << "Estado:    " << soporte.estado << endl;

    return salida;
}

bool Soporte::agregar( const Soporte &nuevaSoporte )
{
    Soporte promo;
    string cadena;
    int posIndice, contador;
    long int posByte;
    string idString = nuevaSoporte.id;

    if( contiene( idString ) )
        return false;

    fstream archivo( "dispersion2.txt", ios::in | ios::out );
    posIndice = dispersion( nuevaSoporte.id );
    cout << "Se guardara en la posicion indice: " << posIndice << endl;
    posByte = posIndice * ( sizeof( Soporte ) * CONTENEDOR + sizeof( int ) );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &contador, sizeof( int ) ); // lee el numero de registros en el contador
    if( contador < CONTENEDOR ) // si el contenedor no esta lleno
    {
        // aumenta el contador y lo escribe
        contador++;
        archivo.seekg( posByte, ios::beg );
        archivo.write( ( char * ) &contador, sizeof( int ) );

        // escribe el nuevo registro en el contenedor
        for( int i = 0; i < CONTENEDOR; i++ )
        {
            archivo.read( ( char * ) &promo, sizeof( Soporte ) );
            if( promo.id[ 0 ] == '\0' )
            {
                archivo.seekg( ( long )archivo.tellg() - sizeof( Soporte ), ios::beg );
                archivo.write( ( char * ) &nuevaSoporte, sizeof( Soporte ) );
                archivo.close();
                return true;
            }
        }

    }
    else
        cout << endl << "No hay mas espacio para este registro" << endl;
    archivo.close();
    return false;
}

void Soporte::mostrar( void )
{
    Soporte promo;
    int contador;
    long int posByte;

    ifstream archivo( "dispersion2.txt", ios::in );
    if( !archivo )
        cout << "No existe el archivo" << endl;
    else
    {
        cout << endl;
        for( int i = 0; i < NUMREGISTROS; i++ )
        {
            archivo.read( ( char * ) &contador, sizeof( int ) );
            if( contador > 0 )
            {
                for( int j = 0; j < CONTENEDOR; j++ )
                {
                    archivo.read( ( char * ) &promo, sizeof( Soporte ) );
                    if( promo.id[ 0 ] != '\0' )
                        cout << promo << endl;
                }
            }
            else
                archivo.seekg( sizeof( Soporte ) * CONTENEDOR, ios::cur );
        }
    }
    archivo.close();
}

bool Soporte::buscar( const string &idABuscar, Soporte &SoporteEncontrada )
{
    long int posByte;

    if( !contiene( idABuscar ) )
        return false;

    ifstream archivo( "dispersion2.txt", ios::in );
    if( !archivo )
    {
        cout << "El archivo no existe" << endl;
        archivo.close();
        return false;
    }

    posByte = buscarId( idABuscar );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &SoporteEncontrada, sizeof( Soporte ) );
    archivo.close();
    return true;
}

bool Soporte::modificar( const string &idAModificar, const Soporte &SoporteNueva )
{
    Soporte registroLimpio, promo;
    int posIndiceAntiguo, posIndiceNuevo, contador;
    long int posByteAntiguo, posByteNuevo;

    if( !contiene( idAModificar ) )
        return false;

    fstream archivo( "dispersion2.txt", ios::in | ios::out );
    if( !archivo )
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndiceAntiguo = dispersion( idAModificar.c_str() );
    posByteAntiguo = buscarId( idAModificar );
    posIndiceNuevo = dispersion( SoporteNueva.id );
    posByteNuevo = posIndiceNuevo * ( sizeof( Soporte ) * CONTENEDOR + sizeof( int ) );

    if( posByteAntiguo == posByteNuevo )
    {
        archivo.seekg( posByteAntiguo, ios::beg );
        archivo.write( ( char * ) &SoporteNueva, sizeof(  Soporte) );
    }
    else
    {
        // quita el registro antiguo y resta uno al contador del contenedor
        archivo.seekg( posByteAntiguo, ios::beg );
        archivo.write( ( char * ) &registroLimpio, sizeof( Soporte ) );
        posByteAntiguo = posIndiceAntiguo * ( sizeof( Soporte ) * CONTENEDOR + sizeof( int ) );
        archivo.seekg( posByteAntiguo, ios::beg );
        archivo.read( ( char * ) &contador, sizeof( int ) );
        contador--;
        archivo.seekg( posByteAntiguo, ios::beg );
        archivo.write( ( char * ) &contador, sizeof( int ) );

        // intenta meter el nuevo registro en la nueva posicion
        archivo.seekg( posByteNuevo, ios::beg );
        archivo.read( ( char * ) &contador, sizeof( int ) );
        if( contador < CONTENEDOR )
        {
            // aumenta el contador y lo escribe
            contador++;
            archivo.seekg( posByteNuevo, ios::beg );
            archivo.write( ( char * ) &contador, sizeof( int ) );

            // escribe el nuevo registro en el contenedor
            for( int i = 0; i < CONTENEDOR; i++ )
            {
                archivo.read( ( char * ) &promo, sizeof( Soporte ) );
                if( promo.id[ 0 ] == '\0' ) // si el lugar no esta ocupado
                {
                    archivo.seekg( ( long )archivo.tellg() - sizeof( Soporte ), ios::beg );
                    archivo.write( ( char * ) &SoporteNueva, sizeof( Soporte ) );
                    archivo.close();
                    return true;
                }
            }
        }
        else // el contenedor esta lleno
            return false;
    }
} // fin funcion modificar

bool Soporte::eliminar( const string &idAEliminar, Soporte &destinoEliminado )
{
    Soporte promo;
    int posIndice, posByte, contador;

    if( !contiene( idAEliminar ) )
        return false;

    fstream archivo( "dispersion2.txt", ios::in | ios::out );
    if( !archivo )
    {
        cout << "El archivo no exite" << endl;
        archivo.close();
        return false;
    }

    posIndice = dispersion( idAEliminar.c_str() );
    posByte = buscarId( idAEliminar );

    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &destinoEliminado, sizeof(  Soporte) );
    archivo.seekg( posByte, ios::beg );
    archivo.write( ( char * ) &promo, sizeof(  Soporte) );

    posByte = posIndice * ( sizeof( Soporte ) * CONTENEDOR + sizeof( int ) );
    archivo.seekg( posByte, ios::beg );
    archivo.read( ( char * ) &contador, sizeof( int ) );
    contador--;
    archivo.seekg( posByte, ios::beg );
    archivo.write( ( char * ) &contador, sizeof( int ) );
    archivo.close();
    return true;
}

void Soporte::menu()
{
    Soporte soporte, SoporteBuscar, SoporteModificar, SoporteEliminar, SoporteAgregar;
    string idABuscar, idAModificar, idAEliminar;
    char opcion, op;

    soporte.genera();
    system( "cls" );

    do{
        cout<<"\n\n\t\tBienvenido al menu Soportees\n\n";
        cout<<"Seleccione una opcion" << endl
            << "1. Agregar"   << endl
            << "2. Mostrar"   << endl
            << "3. Buscar"    << endl
            << "4. Modificar" << endl
            << "5. Eliminar"  << endl
            << "6. Salir"     << endl
            << endl;
        cin >> opcion;
        switch( opcion )
        {
          case '1':
            SoporteAgregar = soporte.pedirRegistro();
            if( soporte.agregar( SoporteAgregar ) )
                cout << "Cliente agregado con exito" << endl;
            else
                cout << "No se agrego la soporte" << endl;
            break;

          case '2':
            system( "cls" );
            soporte.mostrar();
            break;

          case '3':
            cout << "Ingrese el ID de la soporte a buscar: ";
            fflush( stdin );
            getline( cin, idABuscar );
            if( soporte.buscar( idABuscar, SoporteBuscar ) )
                cout << endl << SoporteBuscar << endl;
            else
                cout << "No existe el registro" << endl;
            break;

          case '4':
            cout << "Ingrese el ID de la soporte a modificar: ";
            fflush( stdin );
            getline( cin, idAModificar );
            if( soporte.buscar( idAModificar, SoporteBuscar ) )
            {
                cout << endl << SoporteBuscar << endl;
                cout << "Desea modificarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if( op == '1' )
                {
                    SoporteModificar = soporte.pedirRegistro();
                    if( soporte.modificar( idAModificar, SoporteModificar ) )
                        cout << endl << "Soporte modificada con exito" << endl;
                    else
                        cout << endl << "No se pudo modificar" << endl;
                }
            }
            else
                cout << "No existe el registro" << endl;
            break;

          case '5':
            cout << "Ingrese el ID de la Soporte a eliminar: ";
            fflush( stdin );
            getline( cin, idAEliminar );
            if( soporte.buscar( idAEliminar, SoporteBuscar ) )
            {
                cout << endl << SoporteBuscar << endl;
                cout << "Desea eliminarlo?" << endl;
                cout << "1) Si" << endl;
                cout << "2) No" << endl;
                cin >> op;

                if( op == '1' )
                    if( soporte.eliminar( idAEliminar, SoporteEliminar ) )
                        cout << endl << SoporteEliminar << endl << "SE ELIMINO CORRECTAMENTE" << endl;
                    else
                        cout << "NO SE PUDO ELIMINAR" << endl;
            }
            else
                cout << "No existe el registro" << endl;
            break;
        }
        cout << endl;
        system("Pause");
        system( "cls" );
    }while(opcion != '6');
}
