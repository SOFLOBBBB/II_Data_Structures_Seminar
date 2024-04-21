#include "Cancelacion.hpp"

using namespace std;

void Cancelacion::Agregar()
{
    cin.ignore();

    cout << "\n\n\t\t\t - codigo de CANCELACION:" << endl << "\n\t\t--> ";
    cin.getline(codigo,10);

    cout << "\n\n\t\t\t - Cual es el motivo de su CANCELACION:" << endl << "\n\t\t--> ";
    cin.getline(Motivo,50);

    cout << "\n\n\t\t\t - ¿Que podriamos hacer para que no se vuelva a repetir?" << endl << "\n\t\t--> ";
    cin.getline(Sugerencia,50);

    cout << "\n\n\t\t\t - proporciona un CORREO" << endl << "\n\t\t--> ";
    cin.getline(correo,25);

    cout << "\n\n\t\t\t - FECHA de cancelacion:"<< endl << "\n\t\t--> ";
    cin.getline(Fecha,10);

    ofstream file("CancelacioneShein.bin",ios::app);
    file.write((char*)this,sizeof(Cancelacion));
    file.close();
}

void Cancelacion::Mostrar()
{
    ifstream file("CancelacioneShein.bin");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Cancelacion));
            if(file.eof())
            {
                break;
            }
            cout <<  "\n\t\t****************************************************** " <<endl;
            cout <<  "\n\t\t - CODIGO :  "<< codigo <<endl;
            cout <<  "\n\t\t - MOTIVO :  "<< Motivo <<endl;
            cout <<  "\n\t\t - SUGERENCIA :  "<< Sugerencia <<endl;
            cout <<  "\n\t\t - CORREO :  "<< correo <<endl;
            cout <<  "\n\t\t - FECHA :  "<< Fecha <<endl;
        }
    }
    file.close();
}

void Cancelacion::Modificar()
{
    char auxil[10];
    ifstream file("CancelacioneShein.bin", ios::app);
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout << "\n\n\t\tM O D I F I C A R     F E C H A"<<endl;

        ofstream file2("temporalCancel.bin",ios::app);
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Cancelacion));
            if(file.eof())
            {
                break;
            }
            else
            {
                cout << "\n\n\t\tDame la nueva Fecha: ";
                cin.getline(Fecha,10);
                file2.write((char*)this,sizeof(Cancelacion));
            }
        }
        file.close();
        file2.close();
        remove("CancelacioneShein.bin");
        char oldname[] ="temporalCancel.bin";
        char newname[] ="CancelacioneShein.bin";
        rename(oldname,newname);
    }
}

void Cancelacion::Eliminar()
{
    char auxil[10];
    int opcion=0;
    ifstream file("CancelacioneShein.bin", ios::app);
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {

        ofstream file2("temporalCancel.bin",ios::app);
        while(!file.eof())
        {
            file.read((char*)this,sizeof(Cancelacion));
            if(file.eof())
            {
                break;
            }
            else
            {
                cout << "\n\n\t\tC A N C E L A C I O N   A   E L I M I N A R"<<endl;
                cout << "\n\t\tCodigo: " << codigo << endl;
                cout << "\n\t\tMotivo: " << Motivo <<endl;
                cout << "\n\t\tSugerencia: " << Sugerencia << endl;
                cout << "\n\t\tCorrreo: " << correo << endl;
                cout << "\n\t\tFecha: " << Fecha << endl;

                cout << "\n\t\tDESEAS   ELIMINARLO ?\n\n\t\t1 - SI\t\t\t0 - NO\n\n\t\t--> ";
                cin >> opcion;
                if(opcion==1)
                {

                }
                else
                {
                    file2.write((char*)this,sizeof(Cancelacion));
                }
            }
        }
        file.close();
        file2.close();
        remove("CancelacioneShein.bin");
        char oldname[] ="temporalCancel.bin";
        char newname[] ="CancelacioneShein.bin";
        rename(oldname,newname);
    }
    file.close();
}

void Cancelacion::Buscar()
{
    char auxil[10];
    ifstream file("CancelacioneShein.bin");
    if(!file.good())
    {
        cout<<"\n\n\t\t El file no existe....."<<endl;
    }
    else
    {
        cout << "\n\n\t\tB U S C A R    C A N C E L A C I O N"<<endl;
        cout << "\n\n\t\tIngresa el codigo: " << "\n\n\t\t--> ";
        cin.getline(auxil,10);
        file.read((char*)this,sizeof(Cancelacion));
        if(strcmp(codigo,auxil)==0)
        {
            cout << "\n\n\t\tC A N C E L A C I O N    E N C O N T R A D O"<<endl;
            cout << "\n\t\tCodigo: " << codigo << endl;
            cout << "\n\t\tMotivo: " << Motivo <<endl;
            cout << "\n\t\tSugerencia: " << Sugerencia << endl;
            cout << "\n\t\tCorrreo: " << correo << endl;
            cout << "\n\t\tFecha: " << Fecha << endl;
        }
        else
        {
            cout << "\n\n\t\tCancelacion no encontrada..." << endl;
        }
    }
    file.close();
}

void Cancelacion::menuOpciones()
{
    int op, opc1;
    system("cls");
    cout << "\n\n\n\t\t\tQuieres agregar una Cancelacion:\t\t( 1 ) Si      ( 2 ) NO"  << endl << "\n\t\t--> ";
    cin >> opc1;
    if(opc1 == 1)
    {
        system("cls");
        Agregar();
    }
    do
    {
        system("cls");
        cout<<"\n\n\t\t\t\t\tC A N C E L A C I O N E S" << endl << endl;
        Mostrar();
        gotoxy(20, 40);cout<<"| 1 |  Modificar";
        gotoxy(60, 40);cout<<"| 2 |  Eliminar";
        gotoxy(100, 40);cout<<"| 3 |  Buscar";
        gotoxy(140, 40);cout<<"| 4 |  Salir";
        op = getch();
        switch(op)
        {
        case 49:
            {
                system("cls");
                Modificar();
                getch();
            }break;
        case 50:
            {
                system("cls");
                Eliminar();
                getch();
            }break;
        case 51:
            {
                system("cls");
                Buscar();
                getch();
            }break;
        case 52:
            {

            }break;
        }
    }
    while(op!=52);
}

///**********************************************************

