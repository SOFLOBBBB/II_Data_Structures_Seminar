#include "menuVentas.hpp"

menuVentas::menuVentas(){ }

void menuVentas::Menu()
{
    string op;
    Ventas venta;
    coding();
    while (true) {
            system("cls");
        cout << "\n\n\t\t\t" << string (30, char(205)) ;
        cout <<"\n\n\t\t\t|         MENU VENTAS         |";
        cout << "\n\n\t\t\t" << string (30, char(205));
        cout <<"\n\n\t\t\t| 1 | Agregar Venta ";
        cout <<"\n\n\t\t\t| 2 | Mostrar Venta";
        cout <<"\n\n\t\t\t| 3 | Buscar Venta";
        cout <<"\n\n\t\t\t| 4 | Modificar Venta";
        cout <<"\n\n\t\t\t| 5 | Eliminacion Venta Fisica";
        cout <<"\n\n\t\t\t| 6 | Eliminacion Venta Logica";
        cout <<"\n\n\t\t\t| 7 | Activar Ventas";
        cout <<"\n\n\t\t\t| 8 | Cifrado Huffman";
        cout <<"\n\n\t\t\t| 9 | Descifrado Huffman";
        cout <<"\n\n\t\t\t| 0 | Atras";
        cout <<"\n\n\t\t\t" << string (30, char(205));
        cout <<"\n\n\t\t\tSeleccione una opcion: ";
        getline(cin,op);

        if(op == "1"){
            system("cls");
            crearVenta(venta);
            escribir(venta);

        }
        else if(op == "2"){
            system("cls");
            MostrarVenta();

        }
        else if (op == "3") {
            system("cls");
            BuscarVenta();

        }
        else if (op == "4") {
            system("cls");
            ModificarVenta();

        }
        else if (op == "5") {
            system("cls");
            Eliminar_F_P();
        }
        else if (op == "6") {
            system("cls");
            Eliminar_L_P();

        }
        else if (op == "7") {
            ActivarVenta();

        }
        else if (op == "8"){
            system("cls");
            Huffman();

        }
        else if (op == "9"){
            system("cls");
            descifrado();

        }
        else if (op == "0"){
            break;
        }
        else
        {
            cout<<"\n\n\t\t\tOpcion NO Valida"<<endl;
        }
        getch();
    }
}

void menuVentas::crearVenta(Ventas &p)
{
    string temporal, a="1";

    cout<< "\n\n\t\t\t" << string (30, char(205))
        << "\n\n\t\t\t|         NUEVA VENTA         |"
        << "\n\n\t\t\t" <<string (30, char(205)) <<endl;

    cout<<"\n\n\t\t\tIngrese el Producto: " << "\n\n\t\t\t--> ";
    getline(cin, temporal);
    p.setProducto(temporal);

    cout<<"\n\n\t\t\tIngrese la Fecha: " << "\n\n\t\t\t--> ";
    getline(cin, temporal);
    p.setFecha(temporal);

    cout<<"\n\n\t\t\tIngrese el Precio: " << "\n\n\t\t\t--> ";
    getline(cin, temporal);
    p.setPrecio(temporal);

    int i = getCont();
    i++;
    string cod = to_string(i);
    p.setCodigo(cod);
    setCont(i);

    p.setBandera(a);
    cout<<"\n\n\t\t\tVenta Agregada"<<endl;
}
void menuVentas::escribir(const Ventas &p)
{
    ofstream escribir("Ventas.txt", ios::app);
    if(!escribir.is_open()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    escribir<<p;
    escribir.close();
}
void menuVentas::mostrar(Ventas &p)
{
    cout<<"\n\n\t\t\tProducto:   "      <<p.getProducto()
        <<"\n\n\t\t\tFechacion:  " <<p.getFecha()
        <<"\n\n\t\t\tPrecio:     "      <<p.getPrecio()
        <<"\n\n\t\t\tCodigo:     "      <<p.getCodigo()
        << "\n\n\t\t\t" << string(30,char(205));
}
void menuVentas::MostrarVenta()
{
    Ventas p_temp;
    ifstream leer("Ventas.txt");
    string temporal;
    if(!leer.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
    }
    else{
        cout<<"\n\n\t\t\t" << string(30,char(205))
            <<"\n\n\t\t\t|           VENTAS            |"
            <<"\n\n\t\t\t" << string(30,char(205))<<endl;

        while (!leer.eof()) {
            getline(leer,temporal,',');
            p_temp.setProducto(temporal);

            getline(leer,temporal,',');
            p_temp.setFecha(temporal);

            getline(leer,temporal,',');
            p_temp.setPrecio(temporal);

            getline(leer,temporal,',');
            p_temp.setCodigo(temporal);

            getline(leer,temporal,',');
            p_temp.setBandera(temporal);
            if (leer.eof()) {
                break;
            }
            if (p_temp.getBandera() == "1") {
                mostrar(p_temp);
            }

        }
        leer.close();
    }

}
void menuVentas::coding()
{
    ifstream c("Ventas.txt");
    string temporal,temporal2;
    int i;
    if(!c.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        while(!c.eof()){
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal,',');
            getline(c,temporal2,',');
            if(c.eof()){
                break;
            }
            i=stoi(temporal);
            setCont(i);
        }
    }
    c.close();
}
void menuVentas::BuscarVenta()
{
    ifstream busqueda("Ventas.txt");
    string temporal;
    Ventas p_temp;
    if(!busqueda.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        string code;
        bool band = false;

        cout<<"\n\n\t\t\t+" << string(28,char(205)) << "+"
            <<"\n\n\t\t\t|         BUSCAR VENTA         |"
            <<"\n\n\t\t\t+" << string(28,char(205)) << "+"<<endl;

        cout<<"\n\n\t\t\tDigite el Codigo: "  << "\n\n\t\t\t--> ";
        getline(cin,code);

        while(!busqueda.eof()){
            getline(busqueda,temporal,',');
            p_temp.setProducto(temporal);

            getline(busqueda,temporal,',');
            p_temp.setFecha(temporal);

            getline(busqueda,temporal,',');
            p_temp.setPrecio(temporal);

            getline(busqueda,temporal,',');
            p_temp.setCodigo(temporal);

            getline(busqueda,temporal,',');
            p_temp.setBandera(temporal);

            if (code == p_temp.getCodigo() && p_temp.getBandera() == "1") {

                cout<<"\n\n\t\t\tVenta Encontrado\n"<<endl;
                mostrar(p_temp);
                band = true;
                break;
            }
            if(busqueda.eof()){
                break;
            }
        }
        if (band == false) {
            cout<<"\n\n\t\t\tVenta NO Encontrado"<<endl;
        }
        busqueda.close();
    }
}
void menuVentas::ModificarVenta()
{
    ifstream old("Ventas.txt");
    ofstream copia("copia.txt", ios::app);
    Ventas p;
    bool band= false;
    string temporal, temp2;
    if(!old.good()){
        cout<<"\nError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"\n\n\t\t\t+" << string(28,char(205)) << "+"
            <<"\n\n\t\t\t|        MODIFICAR VENTAS     |"
            <<"\n\n\t\t\t+" << string(28,char(205)) << "+"<<endl;

        cout<<"\n\n\t\t\tDigite el Codigo: " << "\n\n\t\t\t--> ";
        string code;
        getline(cin,code);

        while(!old.eof()){
            getline(old,temporal,',');
            p.setProducto(temporal);

            getline(old,temporal,',');
            p.setFecha(temporal);

            getline(old,temporal,',');
            p.setPrecio(temporal);

            getline(old,temporal,',');
            p.setCodigo(temporal);

            getline(old,temporal,',');
            p.setBandera(temporal);
            if(old.eof()){
                break;
            }
            if (code == p.getCodigo() && p.getBandera() == "1") {
                cout<<"\n\n\t\t\tIngrese los NUEVOS Datos\n"<<endl;

                cout<<"\n\n\t\t\tProducto: " << "\n\n\t\t\t--> ";
                getline(cin, temp2);
                p.setProducto(temp2);

                cout<<"\n\n\t\t\tFecha: "  << "\n\n\t\t\t--> ";
                getline(cin, temp2);
                p.setFecha(temp2);

                cout<<"\n\n\t\t\tPrecio: "  << "\n\n\t\t\t--> ";
                getline(cin, temp2);
                p.setPrecio(temp2);

                temp2 = "1";
                p.setBandera(temp2);
                cout<<"\n\n\t\t\tVenta Modificada"<<endl;
                band = true;

            }
            copia<<p;
        }
        if (band==false) {
            cout<<"\n\n\t\t\tVenta NO Encontrado"<<endl;
        }
        old.close();
        copia.close();
        remove("Ventas.txt");
        rename("copia.txt","Ventas.txt");
    }
}
void menuVentas::Eliminar_F_P()
{
    ifstream eliminar("Ventas.txt");
    bool band = false;
    Ventas p;
    string temporal;

    if(!eliminar.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"\n\n\t\t\t+" << string(28,char(205)) << "+"
            <<"\n\n\t\t\t|       ELIMINAR VENTA         |"
            <<"\n\n\t\t\t+" << string(28,char(205)) << "+"<<endl;

        cout<<"\n\n\t\t\tDigite el Codigo: " << "\n\n\t\t\t--> ";
        string code;
        getline(cin,code);

        ofstream copia("copia.txt");
        while(!eliminar.eof()){
            getline(eliminar,temporal,',');
            p.setProducto(temporal);

            getline(eliminar,temporal,',');
            p.setFecha(temporal);

            getline(eliminar,temporal,',');
            p.setPrecio(temporal);

            getline(eliminar,temporal,',');
            p.setCodigo(temporal);

            getline(eliminar,temporal,',');
            p.setBandera(temporal);

            if(eliminar.eof()){
                break;
            }
            if (code != p.getCodigo()){
                band=true;
                copia<<p;
            }
            if(p.getBandera() == "0"){
                band=true;
                copia<<p;

            }
        }
        if (band == false) {
            cout<<"\n\n\t\t\tVenta NO Encontrado"<<endl;
        }
        else{
            cout<<"\n\n\t\t\tVenta Eliminada"<<endl;
        }
        eliminar.close();
        copia.close();
        remove("Ventas.txt");
        rename("copia.txt","Ventas.txt");

    }

}
void menuVentas::Eliminar_L_P()
{
    ifstream eliminar("Ventas.txt");
    ofstream copia("copia.txt");
    Ventas p;
    string temporal;

    cout<<"\n\n\t\t\t+" << string(28,char(205)) << "+"
        <<"\n\n\t\t\t|          ELIMINAR PLATILLO          |"
        <<"\n\n\t\t\t+" << string(28,char(205)) << "+"<<endl;

    cout<<"\n\n\t\t\tDigite el Codigo: " << "\n\n\t\t\t--> ";
    string code;

    bool band = false;
    getline(cin,code);

    if(!eliminar.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{
        while(!eliminar.eof()){

            getline(eliminar,temporal,',');
            p.setProducto(temporal);

            getline(eliminar,temporal,',');
            p.setFecha(temporal);

            getline(eliminar,temporal,',');
            p.setPrecio(temporal);

            getline(eliminar,temporal,',');
            p.setCodigo(temporal);

            getline(eliminar,temporal,',');
            p.setBandera(temporal);

            if(eliminar.eof()){
                break;
            }
            if (code == p.getCodigo()){
                temporal = "0";
                p.setBandera(temporal);
                band =true;

            }
            copia<<p;
        }
        if (band==true) {
            cout<<"\n\n\t\t\tVenta Eliminado"<<endl;
        }
        else {
            cout<<"\n\n\t\t\tVenta NO Encontrado"<<endl;
        }
        eliminar.close();
        copia.close();
        remove("Ventas.txt");
        rename("copia.txt","Ventas.txt");
    }
}
void menuVentas::ActivarVenta()
{
    ifstream activar("Ventas.txt");
    ofstream copia("copia.txt");
    Ventas p;
    string temporal;

    bool band = false;

    if(!activar.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        cout<<"\n\n\t\t\t+" << string(28,char(205)) << "+"
            <<"\n\n\t\t\t|        ACTIVAR VENTAS         |"
            <<"\n\n\t\t\t+" << string(28,char(205)) << "+" <<endl;

        cout<<"\n\n\t\t\tDigite el Codigo: " << "\n\n\t\t\t--> ";
        string code;
        getline(cin,code);

        while(!activar.eof()){
            getline(activar,temporal,',');
            p.setProducto(temporal);

            getline(activar,temporal,',');
            p.setFecha(temporal);

            getline(activar,temporal,',');
            p.setPrecio(temporal);

            getline(activar,temporal,',');
            p.setCodigo(temporal);

            getline(activar,temporal,',');
            p.setBandera(temporal);
            if(activar.eof()){
                break;
            }
            if (code == p.getCodigo() && p.getBandera()=="0"){
                temporal = "1";
                p.setBandera(temporal);
                band =true;
            }
            copia<<p;
        }
        if (band==true) {
            cout<<"\n\n\t\t\tVenta Restaurado"<<endl;
        }
        else {
            cout<<"\n\n\t\t\tVenta NO Encontrado"<<endl;
        }
        activar.close();
        copia.close();
        remove("Ventas.txt");
        rename("copia.txt","Ventas.txt");
    }
}

void menuVentas::Huffman()
{
    cargarFrase();
    mostrarLista();
    listaOrdenada();
    mostrarListaArbol();
    mostrarDiccionario();
}

void menuVentas::cargarFrase()
{
    ifstream archivo("Ventas.txt");

    string aux;
    string frase;

    if(!archivo.good()){
        cout<<"\n\n\t\t\tError Al Abrir El Archivo"<<endl;
        return;
    }
    else{

        lista.clear();

        while(!archivo.eof()){
            getline(archivo,aux);
            frase += aux;
            if(archivo.eof()){
                break;
            }
        }
        cout<<frase<<endl;

        int tam = frase.length();

        for(int i = 0; i < tam; i++){
            NodoL* nodo = lista.findDataChar(frase[i]);

            if(nodo == nullptr){
                lista.insertData(lista.getLast(), 1, frase[i]);
            }
            else{
                nodo->aumentarFrecuencia();
            }
        }
    }
    archivo.close();
    texto = frase;
    getchar();
}

void menuVentas::mostrarLista()
{
//    system("cls");
    cout<<"+--------------------------------+"<<endl
        <<"|\tLISTA DE CARACTERES      |"     <<endl
        <<"+--------------------------------+\n"<<endl;

//    cout<<"Frase: " << texto<<endl;
    cout<<"\nLista de Caracteres: \n"<<endl;
//    lista.imprimirLista();
//    getchar();
}

void menuVentas::listaOrdenada()
{
//    system("cls");
    cout<<"\n+--------------------------------+"<<endl
        <<"|\t  LISTA ORDENADA           |"     <<endl
        <<"+--------------------------------+\n"<<endl;

    cout<<"\nLista Ordenada Ascendetemente: \n"<< endl;
    lista.ordenarLista();
//    lista.imprimirLista();
//    getchar();
}

void menuVentas::mostrarListaArbol()
{
//    system("cls");
    cout<<"\n+--------------------------------+"<<endl
        <<"|\t  LISTA A ARBOL          |"       <<endl
        <<"+--------------------------------+\n"<<endl;

    lista.convertirToArbol();
//    lista.mostrarArbol(lista.getFirst(), 0);

//    string a = lista.stringTotal;

//    system("cls");
//    int x,y;
//    x=60;
//    y=10;

//    lista.mostrarArbol2(lista.getFirst(),x,y);
//    getchar();

//    system("cls");
//    lista.mostrarArbol3(lista.getFirst(),0);
    //    getchar();
}

void menuVentas::mostrarDiccionario()
{
    cout<<"\n+--------------------------------+"<<endl
        <<"|      DICCIONARIO DE DATOS      |"<<endl
        <<"+--------------------------------+\n"<<endl;

    lista.diccionario(lista.getFirst(),0);

    cout<<"\n+--------------------------------+"<<endl
        <<"|     TRADUCCION DE CADENA       |"<<endl
        <<"+--------------------------------+\n"<<endl;

    lista.transformarConDiccionario(texto);
    lista.empaquetar();
    string a = lista.cifrado;

    cout<<"C: "<<a<<endl;
    lista.guardarDiccionario();
}

void menuVentas::descifrado()
{
    lista.leerArchivo();
}

int menuVentas::getCont() const
{
    return cont;
}

void menuVentas::setCont(int value)
{
    cont = value;
}

string menuVentas::getTexto() const
{
    return texto;
}

void menuVentas::setTexto(const string &value)
{
    texto = value;
}
