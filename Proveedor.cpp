#include "Proveedor.hpp"

using namespace std;

Proveedor::Proveedor() {}

Proveedor::~Proveedor()
{

}

void Proveedor::Agregar()
{
    cin.ignore();

    cout << "\n\n\t\t\t - Dame el CODIGO" << endl << "\n\t\t--> ";
    cin.getline(codigo,10);

    cout << "\n\n\t\t\t - Dame el PROVEEDOR" << endl << "\n\t\t--> ";
    cin.getline(nombre,20);

    cout << "\n\n\t\t\t - Dame el TELEFONO" << endl << "\n\t\t--> ";
    cin.getline(telefono,12);

    cout << "\n\n\t\t\t - Dame el CORREO" << endl << "\n\t\t--> ";
    cin.getline(correo,25);

    cout << "\n\n\t\t\t - Dame el CONTRASENA:"<< endl << "\n\t\t--> ";
    cin.getline(contrasena,12);

    ofstream file("ProveedoreShein.txt",ios::app);
    file.write((char*)this,sizeof(Proveedor));
    file.close();
}

void Proveedor::Mostrar()
{
    ifstream file("ProveedoreShein.txt");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout<<"\n\n\t\t\t\tP R O V E E D O R E S"<<endl;
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Proveedor));
            if(file.eof())
            {
                break;
            }
            cout <<  "\n\t\t****************************************************** " <<endl;
            cout <<  "\n\t\t - CODIGO :  "<< codigo <<endl;
            cout <<  "\n\t\t - PROVEEDOR :  "<< nombre <<endl;
            cout <<  "\n\t\t - TELEFONO :  "<< telefono <<endl;
            cout <<  "\n\t\t - CORREO :  "<< correo <<endl;
            cout <<  "\n\t\t - CONTRASENA :  "<<contrasena <<endl;
        }
    }
    file.close();
}

void Proveedor::Modificar()
{
    char auxil[10];
    ifstream file("ProveedoreShein.txt");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout << "\n\n\t\tM O D I F I C A R     P R O V E E D O R"<<endl;
        cout << "\n\n\t\tIngresa el codigo: " << "\n\n\t\t--> ";
        cin.getline(auxil,10);
        ofstream file2("temporalProv.txt",ios::app);
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Proveedor));
            if(file.eof())
            {
                break;
            }
            if(strcmp(codigo,auxil)==0)
            {
                cout << ""<<endl;
                cout << "\n\n\t\tDame el nuevo CODIGO: ";
                cin.getline(codigo,10);
                cout << "\n\n\t\tDame el nuevo PROVEEDOR: ";
                cin.getline(nombre,20);
                cout << "\n\n\t\tDame el nuevo TELEFONO: ";
                cin.getline(telefono,12);
                cout << "\n\n\t\tDame el nuevo CORREO: ";
                cin.getline(correo,25);
                cout << "\n\n\t\tDame el nuevo CONTRASENA: ";
                cin.getline(contrasena,12);

                //ofstream file("ProveedoreShein.txt",ios::app);
                file2.write((char*)this,sizeof(Proveedor));
            }
            else
            {
                file2.write((char*)this,sizeof(Proveedor));
            }

        }
        file.close();
        file2.close();
        remove("ProveedoreShein.txt");
        char oldname[] ="temporalProv.txt";
        char newname[] ="ProveedoreShein.txt";
        rename(oldname,newname);
    }
    file.close();
}

void Proveedor::Eliminar()
{
    char auxil[10];
    int opcion=0;
    ifstream file("ProveedoreShein.txt");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout << "\n\n\t\tE L I M I N A R     P R O V E E D O R"<<endl;
        cout << "\n\n\t\tIngresa el codigo: " << "\n\n\t\t--> ";
        cin.getline(auxil,10);
        ofstream file2("temporalProv.txt",ios::app);
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Proveedor));
            if(file.eof())
            {
                break;
            }
            if(strcmp(codigo,auxil)==0)
            {
                cout << "\n\n\t\tP R O V E E D O R    E N C O N T R A D O"<<endl;
                cout << "\n\t\tCodigo: " << codigo << endl;
                cout << "\n\t\tProveedores: " << nombre <<endl;
                cout << "\n\t\tTelefono: " << telefono << endl;
                cout << "\n\t\tCorrreo: " << correo << endl;
                cout << "\n\t\tContrasena: " << contrasena << endl;

                cout << "\n\t\tDESEAS   ELIMINARLO ?\n\n\t\t1 - SI\t\t\t0 - NO\n\n\t\t--> ";
                cin >> opcion;
                if(opcion==1)
                {

                }
                else
                {
                    file2.write((char*)this,sizeof(Proveedor));
                }
            }
            else
            {
                file2.write((char*)this,sizeof(Proveedor));
            }
        }
        file.close();
        file2.close();
        remove("ProveedoreShein.txt");
        char oldname[] ="temporalProv.txt";
        char newname[] ="ProveedoreShein.txt";
        rename(oldname,newname);
    }
    file.close();
}

void Proveedor::Buscar()
{
    char auxil[10];
    ifstream file("ProveedoreShein.txt");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout << "\n\n\t\tB U S C A R    P R O V E E D O R"<<endl;
        cout << "\n\n\t\tIngresa el codigo: " << "\n\n\t\t--> ";
        cin.getline(auxil,10);
        file.read((char*)this,sizeof(Proveedor));
        if(strcmp(codigo,auxil)==0)
        {
            cout << "\n\n\t\tP R O V E E D O R    E N C O N T R A D O"<<endl;
            cout << "\n\t\tCodigo: " << codigo << endl;
            cout << "\n\t\tProveedores: " << nombre <<endl;
            cout << "\n\t\tTelefono: " << telefono << endl;
            cout << "\n\t\tCorrreo: " << correo << endl;
            cout << "\n\t\tContrasena: " << contrasena << endl;
        }
        else
        {
            cout << "\n\n\t\tProveedor no encontrada..." << endl;
        }
    }
    file.close();
}

void Proveedor::menuOpciones()
{
    int op;
    do
    {
        system("cls");

        cout<<"\n\n\t\tM E N U    P R O V E E D O R E S"<<endl;
        cout<<"\n\t\t| 1 |  Agregar" <<endl;
        cout<<"\n\t\t| 2 |  Mostrar" <<endl;
        cout<<"\n\t\t| 3 |  Modificar "<<endl;
        cout<<"\n\t\t| 4 |  Eliminar" <<endl;
        cout<<"\n\t\t| 5 |  Buscar "<<endl;
        cout<<"\n\t\t| 6 |  Salir "<<endl << "\n\t\t--> ";
        op = getch();
        switch(op)
        {
        case 49:
            {
                system("cls");
                Agregar();
            }break;
        case 50:
            {
                system("cls");
                Mostrar();
                getch();
            }break;
        case 51:
            {
                system("cls");
                Modificar();
                getch();
            }break;
        case 52:
            {
                system("cls");
                Eliminar();
                getch();
            }break;
        case 53:
            {
                system("cls");
                Buscar();
                getch();
            }break;
        case 54:
            {
            }break;
        }
    }
    while(op!=54);
}
