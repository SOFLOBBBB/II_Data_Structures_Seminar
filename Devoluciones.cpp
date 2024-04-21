#include "Devoluciones.hpp"

using namespace std;

ListaLigada< string > arregloIndices;
ListaLigada< int > nrrs;
ListaLigada< int > listaLigada;

///*********************  I M P L E M E N T A C I O N  ***********************-
//Metodos  **PRIVADOS**

int Devolucion::existeId( const int idABuscar )
{
	nrrs.irAlInicio();
	for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
		if( nrrs.obtenerDato() == idABuscar )
			return nrrs.obtenerEnlace();
		else
			nrrs.next();
	return -1;
}

//******************** BUSQUEDAS ********************

int Devolucion::buscarEnIndice( const string &nombreABuscar )
{
	arregloIndices.irAlInicio();
	for( int i = 0; i < arregloIndices.obtenerTamanio(); i++ )
		if( arregloIndices.obtenerDato() == nombreABuscar )
			return arregloIndices.posicionActual();
		else
			arregloIndices.next();
	return -1;
}

int Devolucion::buscarEnLigado( const int idABuscar )
{
	listaLigada.irAlInicio();
	for( int i = 0; i < listaLigada.obtenerTamanio(); i++ )
		if( listaLigada.obtenerDato() == idABuscar )
			return listaLigada.posicionActual();
		else
			listaLigada.next();
	return -1;
}

//******************** ELIMINACIONES ********************

Devolucion Devolucion::eliminarEnArchDatos( const int idAEliminar )
{
	ifstream datos( "devolucion.txt");
	ofstream temporal( "temporal.txt", ios::app);
	Devolucion registro;
	Devolucion registroARetornar;

	while( !datos.eof() )
	{
		datos.read( ( char * ) &registro, sizeof( Devolucion ) );
		if( atoi( registro.id ) != idAEliminar  && !datos.eof() )
        {
			temporal.write( ( char * ) &registro, sizeof( Devolucion ) );
        }
		else if(!datos.eof())
        {
			registroARetornar = registro;
        }
	}
	datos.close();
	temporal.close();
	remove( "devolucion.txt" );
	rename( "temporal.txt", "devolucion.txt" );

	return registroARetornar;
}

void Devolucion::eliminarEnNrrs( const int idAEliminar )
{
	int posicion = existeId( idAEliminar );
	nrrs.irAPosicion( posicion );
	//cout << "posicion = " << posicion << endl;
	nrrs.eliminar();
	for( int i = posicion; i < nrrs.obtenerTamanio(); i++ )
	{
		nrrs.modificar( nrrs.obtenerDato(), nrrs.obtenerEnlace() - 1 );
		nrrs.next();
	}
	//mostrar( nrrs );
}

void Devolucion::eliminarEnIndiceDevolucions( const string &nombreAEliminar )
{
	int posicion = buscarEnIndice( nombreAEliminar );
	arregloIndices.irAPosicion( posicion );
	listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
	if( listaLigada.obtenerEnlace() == -1 )
		arregloIndices.eliminar();
}

void Devolucion::eliminarEnIndiceLigado( const int idAEliminar, const int posDeRegistro )
{
	int posicion = buscarEnLigado( idAEliminar );
	listaLigada.irAPosicion( posicion );
	int aux = listaLigada.posicionActual();
	int posNueva = listaLigada.obtenerEnlace();
	arregloIndices.irAPosicion( posDeRegistro );
	if( listaLigada.obtenerEnlace() == -1 )
    {
		listaLigada.modificar( -1, -1 );
    }
	else
	{
		if( arregloIndices.obtenerEnlace() == listaLigada.posicionActual() )
		{
			arregloIndices.modificar( arregloIndices.obtenerDato(), listaLigada.obtenerEnlace() );
			listaLigada.modificar( -1, -1 );
		}
		else
		{
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			while( listaLigada.obtenerEnlace() != aux )
				listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			listaLigada.modificar( listaLigada.obtenerDato(), posNueva );
			listaLigada.irAPosicion( posicion );
			listaLigada.modificar( -1, -1 );
		}
	}
}

// ********************* MODIFICACIONES ************************

Devolucion Devolucion::modificarEnArchDatos( const int idAModificar, const Devolucion &registroReemplazo )
{
	Devolucion registroARetornar;
	fstream datos( "devolucion.txt", ios::in | ios::out );
	if( datos )
	{
		int posDeRegistro = existeId( idAModificar );
		int posByte = posDeRegistro * sizeof( Devolucion );
		datos.seekg( posByte, ios::beg );
		datos.read( ( char * ) &registroARetornar, sizeof( Devolucion ) );
		datos.seekg( (long)datos.tellg() - sizeof( Devolucion ), ios::beg );
		datos.write( ( char * ) &registroReemplazo, sizeof( Devolucion ) );
	}
	else
		cout << "No existe el archivo" << endl;
	datos.close();
	return registroARetornar;
}

void Devolucion::modificarEnNrrs( const int idAModificar, const int nuevoID )
{
	int posicion = existeId( idAModificar );
	nrrs.irAPosicion( posicion );
	nrrs.modificar( nuevoID, nrrs.obtenerEnlace() );
}

void Devolucion::modificarEnIndiceLigado( const string &nombreAModificar, const int idViejo )
{
	int posicion = buscarEnIndice( nombreAModificar );
	int a, b, c;
	bool bandera = false;
	arregloIndices.irAPosicion( posicion );
	listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
	a = c = listaLigada.posicionActual();
	if( listaLigada.obtenerDato() == idViejo && listaLigada.obtenerEnlace() == -1 )
	{
		arregloIndices.eliminar();
		listaLigada.modificar( -1, -1 );
	}
	else
	{
		while( listaLigada.obtenerDato() != idViejo )
		{
			a = listaLigada.posicionActual();
			listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			c = listaLigada.posicionActual();
			bandera = true;
		}
		b = listaLigada.obtenerEnlace();
		if( bandera == true )
			arregloIndices.modificar( arregloIndices.obtenerDato(), a );

		else
			arregloIndices.modificar( arregloIndices.obtenerDato(), b );

		listaLigada.irAPosicion( a );
		listaLigada.modificar( listaLigada.obtenerDato(), b );
		listaLigada.irAPosicion( c );
		listaLigada.modificar( -1, -1 );
	}
}

void Devolucion::modificarEnIndiceDevolucions( const string &nombreAnterior, const string &nuevoNombre, const int idViejo, const int nuevoId )
{
	int posicion = buscarEnIndice( nuevoNombre );
	if( posicion == -1 ) // si nuevoNombre NO existe en el archivo
	{
		listaLigada.insertarAlFinal( nuevoId, -1 );
	    arregloIndices.insertarAlFinal( nuevoNombre, listaLigada.obtenerTamanio() - 1 );
	}
	else // si nuevoNombre YA existe
	{
		if( nombreAnterior == nuevoNombre )
		{
			arregloIndices.irAPosicion( posicion );
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			while( listaLigada.obtenerDato() != idViejo )
            {
				listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
            }
			listaLigada.modificar( nuevoId, listaLigada.obtenerEnlace() );
		}
		else
		{
			arregloIndices.irAPosicion( posicion );
	    	listaLigada.insertarAlFinal( nuevoId, arregloIndices.obtenerEnlace() );
	    	arregloIndices.modificar( arregloIndices.obtenerDato(), listaLigada.obtenerTamanio() - 1 );
	    }
	}
}

//FUNCIONES (METODOS)  **PUBLICOS**

// **************** Constructor y Destructor ****************

Devolucion::Devolucion( const Devolucion &origen )
{
	strcpy( id, origen.id );
	strcpy( nombre, origen.nombre );
	strcpy( fecha, origen.fecha );
	strcpy( motivo, origen.motivo );
	strcpy( cantidad, origen.cantidad );
}

// ************** Getter y Setters **************

char Devolucion::getNombre()
{
    return *nombre;
}

void Devolucion::setNombre( const string &valorNombre )
{
	int longitud = valorNombre.size();
	longitud = ( longitud < 35 ? longitud : 34 );
	valorNombre.copy( nombre, longitud );
	nombre[ longitud ] = '\0';
}

char Devolucion::getFecha()
{
    return *fecha;
}

void Devolucion::setFecha( const string &valorFecha )
{
	int longitud = valorFecha.size();
	longitud = ( longitud < 20 ? longitud : 19 );
	valorFecha.copy( fecha, longitud );
	fecha[ longitud ] = '\0';
}

char Devolucion::getMotivo()
{
    return *motivo;
}

void Devolucion::setMotivo( const string &valorMotivo )
{
	int longitud = valorMotivo.size();
	longitud = ( longitud < 40 ? longitud : 39 );
	valorMotivo.copy( motivo, longitud );
	motivo[ longitud ] = '\0';
}

char Devolucion::getCantidad()
{
    return *cantidad;
}

void Devolucion::setCantidad( const string &valorCantidad )
{
	int longitud = valorCantidad.size();
	longitud = ( longitud < 10 ? longitud : 9 );
	valorCantidad.copy( cantidad, longitud );
	cantidad[ longitud ] = '\0';
}

char Devolucion::getId()
{
    return *id;
}

void Devolucion::setId( const string &valorId )
{
	int longitud = valorId.size();
	longitud = ( longitud < 10 ? longitud : 9 );
	valorId.copy( id, longitud );
	id[ longitud ] = '\0';
}

// ********************* FUNCIONES (METODOS) *************************

void Devolucion::inicializar( void )
{
	IndiceSecundario indiSecundario;
	Ligada liga;
	string cadenaNombre;
	ifstream indice( "indiceDevolucions.txt", ios::app );
	ifstream indiceLigado( "ligadoDevolucions.txt", ios::app );
	ifstream indiceNrr( "indiceNrr.txt", ios::app );



	if( !indice || !indiceLigado || !indiceNrr ) // si los archivos no existen los crea
	{
		ofstream indice( "indiceDevolucions.txt", ios::app );
		ofstream indiceLigado( "ligadoDevolucions.txt", ios::app );
		ofstream indiceNrr( "indiceNrr.txt", ios::app );
	}
	else
	{
		// archivo de índices para el nombre
		arregloIndices.irAlInicio();
		while( !indice.eof() )
		{
			indice.read( ( char * ) &indiSecundario, sizeof( IndiceSecundario ) );
			if( !indice.eof() )
			{
				cadenaNombre = indiSecundario.nombre;
				arregloIndices.insertarAlFinal( cadenaNombre, indiSecundario.enlace );
			}
			cadenaNombre.clear();
		}

		// archivo de indice ligado para nombre
		listaLigada.irAlInicio();
		while( !indiceLigado.eof() )
		{
			indiceLigado.read( ( char * ) &liga, sizeof( Ligada ) );
			if( !indiceLigado.eof() )
				listaLigada.insertarAlFinal( liga.id, liga.enlace );
		}
		// archivo de inidice de nrr's para los datos de devolucion
		nrrs.irAlInicio();
		while( !indiceNrr.eof() )
		{
			indiceNrr.read( ( char * ) &liga, sizeof( Ligada ) );
			if( !indiceNrr.eof() )
				nrrs.insertarAlFinal( liga.id, liga.enlace );
		}
	}

	indice.close();
	indiceLigado.close();
	indiceNrr.close();
}

void Devolucion::guardar( void )
{
	ofstream indice( "indiceDevolucions.txt", ios::app );
	ofstream indiceLigado( "ligadoDevolucions.txt", ios::app );
	ofstream indiceNrr( "indiceNrr.txt", ios::app );

	IndiceSecundario contenedor;
	arregloIndices.irAlInicio();
	for( int i = 0; i < arregloIndices.obtenerTamanio(); i++ )
	{
		for( int j = 0; j < sizeof( contenedor.nombre ); contenedor.nombre[ j++ ] = '\0' );
		strcpy( contenedor.nombre, arregloIndices.obtenerDato().c_str() );
		contenedor.enlace = arregloIndices.obtenerEnlace();
		indice.write( ( char * ) &contenedor, sizeof( IndiceSecundario ) );
		arregloIndices.next();
	}

	Ligada liga;
	listaLigada.irAlInicio();
	for( int i = 0; i < listaLigada.obtenerTamanio(); i++ )
	{
		liga.id = listaLigada.obtenerDato();
		liga.enlace = listaLigada.obtenerEnlace();
		indiceLigado.write( ( char * ) &liga, sizeof( Ligada ) );
		listaLigada.next();
	}

	nrrs.irAlInicio();
	for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
	{
		liga.id = nrrs.obtenerDato();
		liga.enlace = nrrs.obtenerEnlace();
		indiceNrr.write( ( char * ) &liga, sizeof( Ligada ) );
		nrrs.next();
	}

	indice.close();
	indiceLigado.close();
	indiceNrr.close();
}

// ********************** Funciones Basicas ************************

Devolucion Devolucion::pedirRegistro( void )
{
	string cadena;
	Devolucion objetoRegresar;

	cout << "\n\n\t\t\tIngresa el ID del Producto: " << "\n\n\t\t\t--> ";
	fflush( stdin );
	getline( cin, cadena );
	while( existeId( atoi( cadena.c_str() ) ) != -1 )
	{
		cout << "\n\n\t\t\tEse ID ya existe Ingresa otro: " << "\n\n\t\t\t--> ";
		fflush( stdin );
		getline( cin, cadena );
	}
	objetoRegresar.setId( cadena );

	cout << "\n\n\t\t\tIngrese el nombre del Producto a devolver: " << "\n\n\t\t\t--> ";
    fflush( stdin );
    getline( cin, cadena );
    objetoRegresar.setNombre( cadena );

    cout << "\n\n\t\t\tIngrese la Fecha: " << "\n\n\t\t\t--> ";
    fflush( stdin );
    getline( cin, cadena );
    objetoRegresar.setFecha( cadena );

    cout << "\n\n\t\t\tIngrese el motivo: " << "\n\n\t\t\t--> ";
    fflush( stdin );
    getline( cin, cadena );
    objetoRegresar.setMotivo( cadena );

    cout << "\n\n\t\t\tIngrese el dinero a devolver: " << "\n\n\t\t\t--> ";
    fflush( stdin );
    getline( cin, cadena );
    objetoRegresar.setCantidad( cadena );

    return objetoRegresar;
}

void Devolucion::agregar( const Devolucion &nuevoValor )
{
	string cadenaNombre;

    ofstream file( "devolucion.txt", ios::app );
    if( existeId( atoi( nuevoValor.id ) ) == -1 )
    {
	    file.write( ( char * ) &nuevoValor, sizeof( Devolucion ) );
	    nrrs.insertarAlFinal( atoi( nuevoValor.id ), nrrs.obtenerTamanio() );

	    cadenaNombre = nuevoValor.nombre;
	    int posEncontrado = buscarEnIndice( cadenaNombre );
	    if( posEncontrado != -1 ) // si ya existe el nombre
	    {
	    	arregloIndices.irAPosicion( posEncontrado );
	    	listaLigada.insertarAlFinal( atoi( nuevoValor.id ), arregloIndices.obtenerEnlace() );
	    	arregloIndices.modificar( arregloIndices.obtenerDato(), listaLigada.obtenerTamanio() - 1 );
	    }
	    else // si no existe el nombre
	    {
	    	listaLigada.insertarAlFinal( atoi( nuevoValor.id ), -1 );
	    	arregloIndices.insertarAlFinal( cadenaNombre, listaLigada.obtenerTamanio() - 1 );
	    }
	    mostrar( listaLigada );
	    mostrar( nrrs );
	    mostrar( arregloIndices );
	}
	else
		cout << "\n\n\t\t\tNo se agrego, el ID ya existe" << endl;
    file.close();
}

bool Devolucion::eliminar( const int idAEliminar, Devolucion &valor )
{
	string cadenaNombre;
	if( existeId( idAEliminar ) != -1 )
	{
		valor = eliminarEnArchDatos( idAEliminar );
		eliminarEnNrrs( idAEliminar );
		cadenaNombre = valor.nombre;
		eliminarEnIndiceDevolucions( cadenaNombre ); // debe ir antes que eliminarEnIndiceLigado
		eliminarEnIndiceLigado( idAEliminar, arregloIndices.posicionActual() );
		return true;
	}
	else
		cout << "\n\n\t\t\tEL id no existe" << endl;

	return false;
}

void Devolucion::modificar( const int idAModificar, const Devolucion &reemplazo )
{
	string cadenaNombre, cad;
	Devolucion devolucionModificado;
	if( existeId( idAModificar ) != -1 && existeId( atoi( reemplazo.id ) ) == -1 ) // significa que si existe el id
	{
		devolucionModificado = modificarEnArchDatos( idAModificar, reemplazo );
		modificarEnNrrs( idAModificar, atoi( reemplazo.id ) );
		cadenaNombre = reemplazo.nombre;
		cad = devolucionModificado.nombre;
		modificarEnIndiceDevolucions( cad, cadenaNombre, atoi( devolucionModificado.id ), atoi( reemplazo.id ) );
		cadenaNombre = devolucionModificado.nombre;
		if( !( strcmp( devolucionModificado.nombre, reemplazo.nombre ) == 0 ) )
			modificarEnIndiceLigado( cadenaNombre, atoi( devolucionModificado.id ) );
	}
	else
		cout << "\n\n\t\t\tEl registro no existe o el id ya existe" << endl;

	mostrar( listaLigada );
	mostrar( nrrs );
	mostrar( arregloIndices );
}

//****************** Busqueda ***********************

bool Devolucion::buscarId( const int idABuscar, Devolucion &resultado )
{
	long int posByte;
	ifstream datos( "devolucion.txt" );

	if( !datos.good() )
		cout << "\n\n\t\t\tNo existe el archivo" << endl;
	else
	{
		nrrs.irAlInicio();
		for( int i = 0; i < nrrs.obtenerTamanio(); i++ )
		{
			if( nrrs.obtenerDato() == idABuscar )
			{
				posByte = nrrs.obtenerEnlace() * sizeof( Devolucion );
				datos.seekg( posByte, ios::beg );
				cout << endl << endl;
				cout << string (100, char(205));
				cout << endl << endl;
				datos.read( ( char * ) &resultado, sizeof( Devolucion ) );
				datos.close();
				return true;
			}
			nrrs.next();
		}
	}
	datos.close();
	return false;
}

void Devolucion::buscarPorNombre( const string & nombreABuscar )
{
	ifstream datos( "devolucion.txt" );
	int indiceRegistro;
	long int posByte;
	Devolucion temporal;
	bool yaTermino = false;

	if( !datos.good() )
		cout << "\n\n\t\t\tNo existe el archivo" << endl;
	else
	{
		int posEncontrado = buscarEnIndice( nombreABuscar );
		if( !( posEncontrado == -1 ) )
		{
			cout << endl;
			arregloIndices.irAPosicion( posEncontrado );
			listaLigada.irAPosicion( arregloIndices.obtenerEnlace() );
			do
			{
				indiceRegistro = existeId( listaLigada.obtenerDato() );
				posByte = indiceRegistro * sizeof( Devolucion );
				datos.seekg( posByte, ios::beg );
				datos.read( ( char * ) &temporal, sizeof( temporal ) );
				cout << endl << endl;
				cout << string (100, char(205));
				cout << endl << endl;
				cout << temporal;
				if( listaLigada.obtenerEnlace() == -1  )
					yaTermino = true;
				else
					listaLigada.irAPosicion( listaLigada.obtenerEnlace() );
			}while( yaTermino == false );
		}
		else
			cout << "\n\n\t\t\tNo se encontraron resultados" << endl;
	}
	datos.close();
}

//****************** Mostrado **********************

void Devolucion::mostrarTodo( void )
{
	Devolucion devolucion;
	ifstream file( "devolucion.txt" );
	if( !file )
		cout << "\n\n\t\t\tNo existe el archivo" << endl;
	else
	{
		cout << endl;
		while( !file.eof() )
		{
			file.read( ( char * ) &devolucion, sizeof( Devolucion ) );
			if( !file.eof() )
			{
                cout << endl << endl;
				cout << string (100, char(205));
				cout << endl << endl;
				cout << devolucion;
			}
		}
	}
	file.close();
}

void Devolucion::mostrarLista( void )
{
	mostrar( listaLigada );
	mostrar( nrrs );
	mostrar( arregloIndices );
}

// ******************** Metodo friend ****************************

ostream &operator<<( ostream &salida, const Devolucion &devolucion )
{
    salida << "ID:        "  << devolucion.id << endl
           << "Nombre:    "  << devolucion.nombre << endl
           << "Fecha: "  << devolucion.fecha << endl
           << "Motivo:    "  << devolucion.motivo << endl
           << "Cantidad:    "  << devolucion.cantidad << endl;

    return salida;
}

//******************* M A I N ********************

void Devolucion::menuDevoluciones()
{
	Devolucion devolucion, nuevo, devolucionBuscar, devolucionEliminado;
	string respuesta;
	char opcion;
	devolucion.inicializar();
	do
    {
	    system("cls");
	    cout << "\n\n\n\t\t\tS E L E C C I O N E   O P C I O N" << endl;
	    cout << "\n\t\t\t| 1 |  Agregar devolucion." << endl;
	    cout << "\n\t\t\t| 2 |  Mostrar todas las devoluciones." << endl;
	    cout << "\n\t\t\t| 3 |  Buscar devolucion por ID." << endl;
	    cout << "\n\t\t\t| 4 |  Buscar devolucion por Nombre" << endl;
        cout << "\n\t\t\t| 5 |  Modificar devolucion." << endl;
        cout << "\n\t\t\t| 6 |  Eliminar devolucion." << endl;
        cout << "\n\t\t\t| 7 |  Mostrar Lista Ligada" << endl;
        cout << "\n\t\t\t| 8 |  A T R A S" << endl;
	    opcion = getch();

	    switch( opcion )
	    {
	    	case 49: // agregar
	    	    system("cls");
	    		nuevo = devolucion.pedirRegistro();
	    		devolucion.agregar( nuevo );
                getch();
	    		break;

	    	case 50: // mostrar
                system("cls");
	    		devolucion.mostrarTodo();
	    		getch();
	    		break;

            case 51: // buscar
                system("cls");
                cout << "\n\n\t\t\tIngrese el ID a buscar: " << "\n\n\t\t\t--> ";
                fflush( stdin );
                cin >> respuesta;
                if( devolucion.buscarId( atoi( respuesta.c_str() ), devolucionBuscar ) )
                    cout << devolucionBuscar << endl << endl;

                else
                    cout << "\n\n\t\t\tEl registro no existe" << endl;

                getch();
                break;
            case 52:
                system("cls");
            	cout << "\n\n\t\t\tIngresa el nombre a buscar: " << "\n\n\t\t\t--> ";;
            	fflush( stdin );
            	getline( cin, respuesta );
            	devolucion.buscarPorNombre( respuesta );

            	getch();
            	break;

            case 53: // modificar
                system("cls");
                cout << "\n\n\t\t\tIngrese el ID de la devolucion a modificar: " << "\n\n\t\t\t--> ";;
                fflush( stdin );
                cin >> respuesta;
                if( devolucion.buscarId( atoi( respuesta.c_str() ), devolucionBuscar ) )
                {
                	nuevo = devolucion.pedirRegistro();
                	devolucion.modificar( atoi( respuesta.c_str() ), nuevo );
                }
                else
                    cout << "\n\n\t\t\tNo Existe la devolucion" << endl;

                getch();
                break;

            case 54: // eliminar
                system("cls");
                cout << "\n\n\t\t\tIngrese el ID de la devolucion a eliminar: " << "\n\n\t\t\t--> ";;
                fflush( stdin );
                cin >> respuesta;
                if( devolucion.buscarId( atoi( respuesta.c_str() ), devolucionBuscar ) )
                {
	                if( devolucion.eliminar( atoi( respuesta.c_str() ), devolucionEliminado ) )
	                {
	                	cout << devolucionEliminado << endl;
	                	cout << "\n\n\t\t\tDEVOLUCION ELIMINADO CON EXITO" << endl;
	                }
	                else
                    {
	                    cout << "\n\n\t\t\tNO se elimino LA DEVOLUCION" << endl;
                    }
	            }
	            else
                {
	            	cout << "\n\n\t\t\tNo existe LA DEVOLUCION" << endl;
                }

                getch();
                break;
            case 55:
                devolucion.mostrarLista();

                getch();
            	break;
            case 56:

                break;
            default:
                    cout << "\n\n\t\t\tOpcion INVALIDA";
                    getch();
                break;
	    }
    }while( opcion != 56 );
	devolucion.guardar();
}


// *********** METODO DEFINIDO ANTES DE LA CLASE ************************

template < typename T >
void mostrar( ListaLigada< T > &L )
{
	int posOriginal = L.posicionActual();
	L.irAlInicio();

	cout << "\n\n\t\t\t | ";
	for( int i = 0; i < L.obtenerTamanio(); i++ )
	{
		cout << L.obtenerDato() << " -> " << L.obtenerEnlace();
		if( !( i == ( L.obtenerTamanio() - 1 ) ) )
		{
			cout << ", ";
			L.next();
		}
	}
	cout << " | ";

	//L.irAPosicion( posOriginal );
}
