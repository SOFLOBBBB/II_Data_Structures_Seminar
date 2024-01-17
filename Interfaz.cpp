#include "Interfaz.hpp"

using namespace std;

Lista <Producto> almacen;
Lista <Producto> almacenPedido;
Lista <Producto>::posicion pos;
Producto produc;
Pedido carrito;
Empleado empleado;
Soporte soporteTec;

Interfaz::Interfaz(){}

void Interfaz::Menu()
{
    int op1, con = 0;
    bool acc;
    titulo(5, 8);
    cout << "\n\n\t\t\t\t P  R  E  S  I  O  N  A       U N A      L  E  T  R  A  " << endl;
    getch();
    system("cls");
    cuadroCompleto();
    titulo(50, 5);
    gotoxy(30, 20);cout << "( o ) Delimitados" << endl;
    gotoxy(150, 20);cout << "( p ) Parametrizados" << endl << "\n\t\t\t--> ";
    op1 = getch();
    if(op1 == 111)
    {
        AgregarDesdeArchivoDelim();
        acc = false;
    }
    else
    {
        AgregarDesdeArchivoParam();
        acc = true;
    }
    do
    {
        if(con == 1)
        {
            if(acc == true)
            {
                AgregarDesdeArchivoParam();
            }
            else
            {
                AgregarDesdeArchivoDelim();
            }
        }
        system("cls");
        titulo(50, 5);
        cuadroCompleto();
        Opciones();
        switch(opc)
        {
            case 48:
                {
                    if(acc == true)
                    {
                        AgregarProductoParam();
                    }
                    else
                    {
                         AgregarProductoDelim();
                    }
                }break;
            case 49:
                {
                    ImpresionDeProducto();
                }break;
            case 50:
                {
                    system("cls");
                    cuadroCompleto();
                    BuscarProducto();
                }break;
            case 51:
                {
                    system("cls");
                    cuadroCompleto();
                    ModificarProducto();
                }break;
            case 52:
                {
                    system("cls");
                    cuadroCompleto();
                    EliminarProducto();
                }break;
            case 53:
                {
                    PedidoGeneral();
                }break;
            case 54:
                {
                    soporteTec.menu();
                }break;
            case 55:
                {
                    Proveedor provMenu;
                    provMenu.menuOpciones();
                }break;
            case 56:
                {
                    empleado.menu();
                }break;
            case 117:
                {
                    Usuario provUsuario;
                    provUsuario.MenuOpciones();
                }break;
            case 118:
                {
                    menuVentas auxMenu;
                    auxMenu.Menu();
                }break;
            case 109:
                {
                    new InterfazGrafo(new Graph<MetodoDePago>);
                }
            case 57:
                {
                    cout << "\n\n\t\tH A S T A   L U E G O";
                }break;
            default:
                {
                    cout << "\n\n\n\t\t LA OPCION SELECCIONADA ES INCORRECTA";
                }break;
        }
        almacen.borraTodo();
        con = 1;
    }while(opc != 57);
}

void Interfaz::Opciones()
{
    int x;
    gotoxy(10, 15);cout<< string(193, char(205)) << endl;

    gotoxy(96, 20);cout<<"( 0 ) - Agregar Producto"<<endl;
    gotoxy(95, 22);cout<<"( 1 ) - Impresion Producto" << endl;
    gotoxy(96, 24);cout<<"( 2 ) - Buscar Producto" << endl;
    gotoxy(95, 26);cout<<"( 3 ) - Modificar Producto" << endl;
    gotoxy(96, 28);cout<<"( 4 ) - Eliminar Producto" << endl;
    gotoxy(100, 30);cout<<"( 5 ) - Pedido" << endl;


    gotoxy(176, 36);cout<<"( 6 ) - Soporte Tecnico" << endl;
    gotoxy(10, 38);cout<< string(193, char(205)) << endl;
    gotoxy(15, 40);cout<<"( 7 ) - Proveedores" << endl;
    gotoxy(180, 40);cout<<"( 8 ) - Empleados" << endl;
    gotoxy(10, 42);cout<< string(193, char(205)) << endl;

    gotoxy(15, 17);cout<<"( u ) - Usuario";

    gotoxy(185, 17);cout<<"( v ) - Ventas";

    gotoxy(15, 36);cout<<"( m ) - Metodos de pago";

    gotoxy(100, 44);cout<<"( 9 ) - SALIR" << endl << "\n\t\t\t--> ";

    x = getch();
    setOpc(x);
}

///*************** F U N C I O N E S ********************

void Interfaz::AgregarProductoDelim()
{
    Fecha date;
    string tempo;
    Producto tem;
    char op;
    ofstream file("Productos.txt", ios::app);
    do
    {
        system("cls");
        cuadroCompleto();
        gotoxy(20, 8);
        cout << "Dame el CODIGO:", gotoxy(20, 9);
        cout << " -->";
        gotoxy(25, 9);
        getline(cin,tempo);
        tem.setCodigo(tempo);
        file << "\n" << tempo << "|";

        gotoxy(20, 11);
        cout << "Dame el NOMBRE:", gotoxy(20, 12);
        cout << " -->";
        gotoxy(25, 12);
        getline(cin,tempo);
        tem.setNombre(tempo);
        file << tempo << "|";

        gotoxy(20, 14);
        cout << "Dame el TIPO:", gotoxy(20, 15);
        cout << " -->";
        gotoxy(25, 15);
        getline(cin,tempo);
        tem.setTipo(tempo);
        file << tempo << "|";

        gotoxy(20, 17);
        cout << "Dame el DIA / MES / ANIO: ", gotoxy(20, 18);
        cout << " -->";
        gotoxy(25, 18);
        getline(cin,tempo, '/');
        file << tempo << "/";
        date.setDia(stoi(tempo.c_str()));
        getline(cin,tempo, '/');
        file << tempo << "/";
        date.setMes(stoi(tempo.c_str()));
        getline(cin,tempo);
        file << tempo << "|";
        date.setAnio(stoi(tempo.c_str()));
        tem.setFecha(date);


        gotoxy(20, 20);
        cout << "Dame el PRECIO:", gotoxy(20, 21);
        cout << " -->";
        gotoxy(25, 21);
        getline(cin,tempo);
        tem.setPrecio(stoi(tempo.c_str()));
        file << tempo << "|";

        gotoxy(20, 23);
        cout << "Dame el PROVEEDOR:", gotoxy(20, 24);
        cout << " -->";
        gotoxy(25, 24);
        getline(cin,tempo);
        tem.setProveedor(tempo);
        file << tempo << "|";

        gotoxy(20, 26);
        cout << "Dame la DESCRIPCION:", gotoxy(20, 27);
        cout << " -->";
        gotoxy(25, 27);
        getline(cin, tempo);
        tem.setDescripcion(tempo);
        file << tempo << "|";

        gotoxy(20, 29);
        cout << "Dame las EXISTENCIAS:", gotoxy(20, 30);
        cout << " -->";
        gotoxy(25, 30);
        getline(cin, tempo);
        tem.setExistencias(tempo);
        file << tempo;

        almacen.insertarProducto(almacen.getUltimoPos(),tem);

        gotoxy(20, 32);
        cout << "coloca (s/n) para (continuar/terminar)    --> ";
        cin >> op;
        cin.ignore();

    }while(op == 's');

    file.close();
}

void Interfaz::AgregarProductoParam()
{
    Fecha date;
    Producto tem;
    string tempo;
    char op;
    ofstream file("ProductosParam.txt", ios::app);
    cin.ignore();
    do
    {
        file << "\n";
        system("cls");
        cuadroCompleto();
        gotoxy(20, 8);
        cout << "Dame el CODIGO:";
        gotoxy(20, 9);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setCodigo(tempo);

        gotoxy(20, 11);
        cout << "Dame el NOMBRE:";
        gotoxy(20, 12);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setNombre(tempo);

        gotoxy(20, 14);
        cout << "Dame el TIPO:";
        gotoxy(20, 15);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setTipo(tempo);

        gotoxy(20, 17);
        cout << "Dame el DIA";gotoxy(20, 18);
        cout << " --> ";
        getline(cin,tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        date.setDia(stoi(tempo.c_str()));
        gotoxy(20, 20);
        cout << "Dame el MES"; gotoxy(20, 21);
        cout << " --> ";
        getline(cin,tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        date.setMes(stoi(tempo.c_str()));
        gotoxy(20, 23);
        cout << "Dame el ANIO"; gotoxy(20, 24);
        cout << " --> ";
        getline(cin,tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        date.setAnio(stoi(tempo.c_str()));
        tem.setFecha(date);

        gotoxy(20, 26);
        cout << "Dame el PRECIO:";
        gotoxy(20, 27);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setPrecio(stoi(tempo.c_str()));

        gotoxy(20, 29);
        cout << "Dame el PROVEEDOR:";
        gotoxy(20, 30);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setProveedor(tempo);

        gotoxy(20, 32);
        cout << "Dame la DESCRIPCION:";
        gotoxy(20, 33);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setDescripcion(tempo);

        gotoxy(20, 35);
        cout << "Dame las EXISTENCIAS:";
        gotoxy(20, 36);
        cout << " --> ";
        getline(cin, tempo);
        if(tempo.length() < 10)
        {
            file << "0";
        }
        file << tempo.length() << tempo;
        tem.setExistencias(tempo);

        almacen.insertarProducto(almacen.getUltimoPos(), tem);

        gotoxy(20, 38);
        cout << "Coloca (s/n) para (continuar/terminar) --> ";
        cin >> op;
        cin.ignore();

    } while(op == 's');

    file.close();
}

void Interfaz::AgregarDesdeArchivoDelim()
{
    Fecha date;
    fstream file;
    string temp;
    file.open("Productos.txt", ios::in);

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        getline(file, temp, '|');
        produc.setCodigo(temp);
        getline(file, temp, '|');
        produc.setNombre(temp);
        getline(file, temp, '|');
        produc.setTipo(temp);

        getline(file, temp, '/');
        date.setDia(stoi(temp.c_str()));
        getline(file, temp, '/');
        date.setMes(stoi(temp.c_str()));
        getline(file, temp, '|');
        date.setAnio(stoi(temp.c_str()));
        produc.setFecha(date);

        getline(file, temp, '|');
        produc.setPrecio(stoi(temp.c_str()));
        getline(file, temp, '|');
        produc.setProveedor(temp);
        getline(file, temp, '|');
        produc.setDescripcion(temp);
        getline(file, temp);
        produc.setExistencias(temp);

        almacen.insertarProducto(almacen.getUltimoPos(),produc);
    }
    file.close();
}

void Interfaz::AgregarDesdeArchivoParam()
{
    Fecha date;
    int aux, limit, a = 0, b = 0, accion = 0;
    bool bandera = false, condicion = false;
    char letra;
    ifstream file("ProductosParam.txt", ios::in);
    string temp,auxConec;

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        condicion = false;
        a = 0;
        b = 0;
        while(a < 2)
        {
            letra = file.get();
            auxConec += letra;
            a++;
        }
        limit = stoi(auxConec.c_str());
        auxConec.erase();
        while(b < limit)
        {
            letra = file.get();
            auxConec += letra;
            b++;
        }
        switch(accion)
        {
            case 0:
            {
                produc.setCodigo(auxConec);
            }break;
            case 1:
            {
                produc.setNombre(auxConec);
            }break;
            case 2:
            {
                produc.setTipo(auxConec);
            }break;
            case 3:
            {
                date.setDia(stoi(auxConec.c_str()));
            }break;
            case 4:
            {
                date.setMes(stoi(auxConec.c_str()));
            }break;
            case 5:
            {
                date.setAnio(stoi(auxConec.c_str()));
                produc.setFecha(date);
            }break;
            case 6:
            {
                produc.setPrecio(stoi(auxConec.c_str()));
            }break;
            case 7:
            {
                produc.setProveedor(auxConec);
            }break;
            case 8:
            {
                produc.setDescripcion(auxConec);
            }break;
            case 9:
            {
                produc.setExistencias(auxConec);
                bandera = true;
                getline(file, auxConec);
                condicion = true;
            }break;
        }
        if(condicion == true)
        {
            accion = 0;
            almacen.insertarProducto(almacen.getUltimoPos(),produc);
        }
        else
        {
            accion++;
        }
        auxConec.erase();
    }
    file.close();
}

void Interfaz::ImpresionDeProducto()
{
    int abc, xi = 0, auxcont;
    fstream ped("Pedi2.txt", ios::out);
    fstream ped2("Pedi2.txt", ios::in);
    do
    {
        system("cls");
        cuadroCompleto();
        almacen.print();
        cout << "\n\n\n\n\n\t\t\t\t( s ) Mover hacia abajo\t\t\t( w ) Mover hacia arriba\t\t\t( a )Agregar a carrito\t\t\t( d ) Salir" << endl << "\n\t\t--> ";
        abc = getch();
        switch(abc)
        {
            case 115:
            {
                almacen.moveTo(2);
            }break;
            case 119:
            {
                almacen.moveTo(1);
            }break;
            case 97:
            {
                produc = almacen.anclaProducto();

                if(xi == 0)
                {
                    auxcont = 0;
                    setContPed(auxcont);
                }
                else
                {
                    ped << "\n";
                }
                ped << produc.getCodigo();
                ped << "|";
                ped << produc.getNombre();
                ped << "|";
                ped << produc.getTipo();
                ped << "|";
                ped << produc.getFecha().getDia();
                ped << "/";
                ped << produc.getFecha().getMes();
                ped << "/";
                ped << produc.getFecha().getAnio();
                ped << "|";
                ped << produc.getPrecio();
                ped << "|";
                ped << produc.getProveedor();
                ped << "|";
                ped << produc.getDescripcion();
                ped << "|";
                ped << produc.getExistencias();
                xi++;
                auxcont++;
                setContPed(auxcont);
            }break;
            case 100:
            {
                return;
            }break;
        }
    }while(abc != 100);
    ped.close();
}

void Interfaz::BuscarProducto()
{
    string aux, temp;
    fstream file;
    bool bandera = false, impre = false;
    file.open("Productos.txt", ios::in);
    cout << "\n\n\t\tDIJITE EL CODIGO:" << endl << "\t\t--> ";
    cin >> aux;

    cout << "\n\t\t";
    while(!file.eof() && !bandera)
    {
        int i=0;
        while(i < 7)
        {
            getline(file, temp, '|');
            if(temp == aux)
            {
                impre = true;
            }
            if(impre == true)
            {
                cout << temp << "  |  ";
            }
            i++;
        }
        getline(file, temp);
        if(impre == true)
        {
            cout << temp << "\n";
            bandera = true;
        }
    }
    if(bandera == false)
    {
        cout << "\n\t\tEl Dato no Fue Encontrado";
    }
    file.close();
    getch();
}

void Interfaz::ModificarProducto()
{
    string aux, temp, nuevo;
    fstream file;
    int x = 0;
    bool bandera = false, impre = false, comprob = false;
    file.open("Productos.txt", ios::in);
    ofstream auxiliar("auxiliar.txt", ios::app);
    cout << "\n\n\t\tDIJITE EL CODIGO:" << endl << "\t\t--> ";
    cin >> aux;

    cout << "\n\t\t";
    cin.ignore();
    while(!file.eof() && !bandera)
    {
        if(x >= 1)
        {
            auxiliar << "\n";
        }
        int i=0;
        while(i < 7)
        {
            getline(file, temp, '|');
            if(temp == aux)
            {
                impre = true;
            }
            if(impre == true)
            {
                cout << "\n\t\tDijita el CODIGO nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el NOMBRE nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el TIPO nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el FEHCA nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el PRECIO nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el PROVEEDOR nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                cout << "\n\t\tDijita el DESCRIPCION nuevo: " << "\n\t\t--> ";
                getline (cin, nuevo);
                auxiliar << nuevo << "|";
                comprob = true;
                i = 7;
            }
            else
            {
                auxiliar << temp << "|";
            }
            i++;
        }
        getline(file, temp);
        if(impre == true)
        {
            cout << "\n\t\tDijita las EXISTENCIAS nuevas: " << "\n\t\t-->";
            getline (cin, nuevo);
            auxiliar << nuevo;
            impre = false;
        }
        else
        {
            auxiliar << temp;
        }
        x++;
    }

    file.close();
    auxiliar.close();
    remove("Productos.txt");
    rename("auxiliar.txt", "Productos.txt");
    if(comprob == false)
    {
        cout << "\n\t\tEl Dato no Fue Encontrado";
    }
    else
    {
        cout << "\n\t\tModificado con exito :)";
    }
    getch();
}

void Interfaz::EliminarProducto()
{
    string aux, temp, nuevo;
    fstream file;
    int x = 0;
    bool bandera = false, impre = false, comprob = false, a = false, b = false;
    file.open("Productos.txt", ios::in);
    ofstream auxiliar("auxiliar.txt", ios::app);
    cout << "\n\n\t\tDIJITE EL CODIGO:" << endl << "\t\t--> ";
    cin >> aux;

    cout << "\n\t\t";
    cin.ignore();
    while(!file.eof() && !bandera)
    {
        int i=0;
        while(i < 7)
        {
            getline(file, temp, '|');
            if(temp == aux)
            {
                impre = true;
                comprob = true;
                i = 7;
                a = false;
            }
            if(a == true)
            {
                auxiliar << "\n";
                a = false;
            }
            if(temp != aux)
            {
                auxiliar << temp << "|";
            }
            i++;
        }
        getline(file, temp);
        if(impre == true)
        {
            impre = false;
            if(x >= 1)
            {
                a = true;
            }
        }
        else
        {
            auxiliar << temp;
            a = true;
        }
        x++;
    }

    file.close();
    auxiliar.close();
    remove("Productos.txt");
    rename("auxiliar.txt", "Productos.txt");
    if(comprob == false)
    {
        cout << "\n\t\tEl Dato no Fue Encontrado";
    }
    else
    {
        cout << "\n\t\tELiminado con exito :)";
    }
    getch();
}

///*******************  D I S E Ñ O  ***********************

void Interfaz::cuadroCompleto()
{
    gotoxy(5, 1);
    cout << char(201);
    rectaHorz(6, 1, 202);
    gotoxy(208, 1);
    cout << char(187);
    rectaVert(5, 2, 46);
    gotoxy(5, 48);
    cout << char(200);
    rectaHorz(6, 48, 202);
    gotoxy(208, 48);
    cout << char(188);
    rectaVert(208, 2, 46);
    gotoxy(7, 3);
}

void Interfaz::rectaHorz(const int& x, const int& y, const int& lim)
{
    int temp(0), cop = x;
    while(temp < lim)
    {
        gotoxy(cop, y);
        cout << char(205);
        cop++;
        temp++;
    }
}

void Interfaz::rectaVert(const int& x, const int& y, const int& lim)
{
    int temp(0), cop = y;
    while(temp < lim)
    {
        gotoxy(x, cop);
        cout << char(186);
        cop++;
        temp++;
    }
}

void Interfaz::titulo(int x, int y)
{
gotoxy(x, y);  cout <<  "  ,ad8888ba,       88        88       ad88888ba       88        88      88888888888      88      888b      88\n";
gotoxy(x, y+1);cout <<  " d8'     `'8b      88        88      d8'     '8b      88        88      88               88      8888b     88\n";
gotoxy(x, y+2);cout <<  "d8'                88        88      Y8,              88        88      88               88      88 `8b    88\n";
gotoxy(x, y+3);cout <<  "88                 88        88      `Y8aaaaa,        88aaaaaaaa88      88aaaaa          88      88  `8b   88\n";
gotoxy(x, y+4);cout <<  "88                 88        88        `'''''8b,      88''''''''88      88'''''          88      88   `8b  88\n";
gotoxy(x, y+5);cout <<  "Y8,                88        88              `8b      88        88      88               88      88    `8b 88\n";
gotoxy(x, y+6);cout <<  " Y8a.    .a8P      Y8a.    .a8P      Y8a     a8P      88        88      88               88      88     `8888\n";
gotoxy(x, y+7);cout <<  "  '`Y8888Y*'        `*Y8888Y*'        'Y88888P'       88        88      88888888888      88      88      `888\n";
}

///******************* P E D I D O ***********************

void Interfaz::PedidoGeneral()
{
    Cancelacion can1;
    Devolucion dev1;
    int cpo;
    do
    {
        system("cls");
        cuadroCompleto();
        cout << "\n\n\t\t\t\t\t P E D I D O" << endl;
        cout << "\n\t\t\t( 1 ) Agregar ( Direccion / Codigo /  Fecha )Pedido" << endl;
        cout << "\n\t\t\t( 2 ) Consultar Pedido" << endl;
        cout << "\n\t\t\t( 3 ) Buscar Pedido" << endl;
        cout << "\n\t\t\t( 4 ) Modificar Pedido" << endl;
        cout << "\n\t\t\t*******************************************************" << endl;
        cout << "\n\t\t\t( 5 ) D E V O L U C I O N " << endl;
        cout << "\n\t\t\t( 6 ) C A N C E L A C I O N " << endl;
        cout << "\n\t\t\t*******************************************************" << endl;
        cout << "\n\t\t\t( 7 ) A T R A S" << endl << "\n\t\t\t--> ";
        cpo = getch();
        switch(cpo)
        {
        case 49:
            {
                PedidoAgregar();
                PedidoImprimir();
                getch();
            }break;
        case 50:
            {
                if(almacenPedido.isEmpty())
                {
                    cout << "\n\n\n\t\t\t NO HAY PEDIDO REALIZADO";
                    getch();
                }
                else
                {
                    PedidoImprimir();
                    getch();
                }
            }break;
        case 51:
            {
                PedidoBuscar();
            }break;
        case 52:
            {
                system("cls");
                PedidoModificar();
            }break;
        case 53:
            {
                ///Devoluciones
                dev1.menuDevoluciones();

            }break;
        case 54:
            {
                ///Cancelaciones
                can1.menuOpciones();
                PedidoEliminar();
                system("cls");
                cout << "\n\n\t\t\t\t P E D D I D O   C A N C E L A D O" <<endl;
                getch();
            }break;
        case 55:
            {

            }break;
        default:
            {
                cout << "\n\n\n\t\t\tO P C I O N   I N V A L I D A";
                getch();
            }break;
        }
    }while(cpo != 55);
}

void Interfaz::PedidoAgregar()
{
    Fecha date;
    string tempo;
    Producto tem;
    ofstream file("Pedi2.txt", ios::app);

    system("cls");
    cuadroCompleto();
    gotoxy(20, 8);
    cout << "Dame la DIRECCION:", gotoxy(20, 9);
    cout << " -->";
    gotoxy(25, 9);
    getline(cin,tempo);
    carrito.setDireccion(tempo);
    file << "\n" << tempo;

    gotoxy(20, 11);
    cout << "Dame el Codigo:", gotoxy(20, 12);
    cout << " -->";
    gotoxy(25, 12);
    getline(cin,tempo);
    carrito.setCodigo(tempo);
    file << "\n" << tempo;

    gotoxy(20, 14);
    cout << "Dame el DIA / MES / ANIO: ", gotoxy(20, 15);
    cout << " -->";
    gotoxy(25, 15);
    getline(cin,tempo, '/');
    file << "\n" << tempo << "/";
    date.setDia(stoi(tempo.c_str()));
    getline(cin,tempo, '/');
    file << tempo << "/";
    date.setMes(stoi(tempo.c_str()));
    getline(cin,tempo);
    file << tempo;
    date.setAnio(stoi(tempo.c_str()));
    carrito.setFecha(date);

    file.close();
}

void Interfaz::PedidoModificar()
{
    Fecha date;
    bool comprob = false;
    string temp, aux, aux2;
    fstream file;
    Producto tem;
    int xc = 0;
    file.open("Pedi2.txt", ios::in);
    ofstream auxiliar("Pedi2Auxiliar.txt", ios::app);

    cout << "\n\n\t\t\tDame la D I R E C C I O N del pedido:" << endl << "\n\t\t\t--> ";
    getline (cin,aux);

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        if(xc < contPed)
        {
            if(xc > 0)
            {
                auxiliar << "\n";
            }
            else
            {

            }
            getline(file, temp);
            auxiliar << temp;
        }
        else
        {
            getline(file, temp);
            if(aux == temp)
            {
                cout << "\n\n\t\t\tDijita la nueva D I R E C C I O N:" << endl << "\n\t\t\t--> ";
                getline(cin, aux2);
                auxiliar << "\n";
                auxiliar << aux2;
                comprob = true;
            }
            else
            {
                auxiliar << "\n";
                auxiliar << temp;
            }
        }
        xc++;
    }
    file.close();
    auxiliar.close();
    remove("Pedi2.txt");
    rename("Pedi2Auxiliar.txt", "Pedi2.txt");
    if(comprob == false)
    {
        cout << "\n\t\tEl Dato no Fue Encontrado";
    }
    else
    {
        cout << "\n\t\tModificado con exito :)";
    }
    getch();
}

void Interfaz::PedidoBuscar()
{
    Fecha date;
    bool comprob = false;
    string temp, aux, aux2;
    fstream file;
    Producto tem;
    int xc = 0;
    file.open("Pedi2.txt", ios::in);

    cout << "\n\n\t\t\tDame el C O D I G O a buscar:" << endl << "\n\t\t\t--> ";
    cin >> aux;

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        if(xc < contPed)
        {
            getline(file, temp);
        }
        else
        {
            getline(file, temp);
            if(aux == temp)
            {
                PedidoImprimir();
                comprob = true;
            }
        }
        xc++;
    }
    file.close();
    if(comprob == false)
    {
        cout << "\n\t\tEl P E D I D O  no Fue Encontrado";
    }
    getch();
}

void Interfaz::PedidoEliminar()
{
    Fecha date;
    bool comprob = false;
    string temp, aux, aux2;
    fstream file;
    Producto tem;
    int xc = 0;
    file.open("Pedi2.txt", ios::in);
    ifstream auxiliar("Pedi2Auxiliar.txt", ios::app);

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        if(xc < contPed)
        {
            getline(file, temp);
        }
        else
        {
            getline(file, temp);
        }
        xc++;
    }
    file.close();
    auxiliar.close();

    almacenPedido.borraTodo();
    remove("Pedi2.txt");
    rename("Pedi2Auxiliar.txt", "Pedi2.txt");
}

void Interfaz::PedidoImprimir()
{
    almacenPedido.borraTodo();
    system("cls");
    cuadroCompleto();
    Fecha date;
    fstream file;
    string temp;
    int x = 50, xc = 0;
    carrito.setPrecioTotalReinicio(xc);
    file.open("Pedi2.txt", ios::in);

    gotoxy(100, 2);
    cout << "P E D I D O";

    if(file.fail())
    {
        return;
    }
    while (!file.eof())
    {
        if(xc < contPed)
        {
            getline(file, temp, '|');
            produc.setCodigo(temp);
            getline(file, temp, '|');
            produc.setNombre(temp);
            getline(file, temp, '|');
            produc.setTipo(temp);

            getline(file, temp, '/');
            date.setDia(stoi(temp.c_str()));
            getline(file, temp, '/');
            date.setMes(stoi(temp.c_str()));
            getline(file, temp, '|');
            date.setAnio(stoi(temp.c_str()));
            produc.setFecha(date);

            getline(file, temp, '|');
            produc.setPrecio(stoi(temp.c_str()));
            carrito.setPrecioTotal(stoi(temp.c_str()));

            getline(file, temp, '|');
            produc.setProveedor(temp);
            getline(file, temp, '|');
            produc.setDescripcion(temp);
            getline(file, temp);
            produc.setExistencias(temp);

            almacenPedido.insertarProducto(almacenPedido.getUltimoPos(),produc);
        }
        else if(xc == contPed)
        {
            almacenPedido.print();
        }
        else if(xc >= contPed)
        {
            getline(file, temp);
            gotoxy(x, 45);
            cout << temp;
            x += 35;
        }
        xc++;
    }
    gotoxy(50, 43);
    cout << "D I R E C C I O N";
    gotoxy(85,43);
    cout << "C O D I G O";
    gotoxy(120,43);
    cout << "F E C H A";
    gotoxy(155,43);
    cout << "T O T A L";

    gotoxy(155,45);
    cout << carrito.getPrecioTotal();

    file.close();
}

///**************** A T R I B U T O S ********************

int Interfaz::getOpc()
{
    return opc;
}

void Interfaz::setOpc(int& aux)
{
    opc = aux;
}

int Interfaz::getContPed()
{
    return contPed;
}

void Interfaz::setContPed(int& aux)
{
    contPed = aux;
}

///*****************************************************

void gotoxy(const int& x, const int& y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}
