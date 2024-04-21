#include "Empleados.hpp"

using namespace std;

Empleado emp;
Indice indi;

int orden=0;

void Empleado::mostrar()
{
    system("cls");
    ifstream file("Empleados.txt");
    if(!file.good())
    cout<<"No Existe el archivo";
    else
    {
        cout << "\n\t\t\tE M P L E A D O S";
        cout << "\n\t\t**************************************************************";
        while(!file.eof())
        {
            file.read((char*)&emp,sizeof(emp));
            if(file.eof())
            {
                break;
            }
            cout<<"\n\n\t\t\tRFC : "<<emp.rfc<<endl<<"\n\t\t\tNombre : "<<emp.nombre<<endl<<"\n\t\t\tSeccion : "<<emp.seccion<<endl<<"\n\t\t\tCorreo : "<<emp.correo<<endl<<"\n\t\t\tDireccion : "<<emp.direccion<<endl<<"\n\t\t\tFecha de Inicio : "<<emp.FechaEntrada;
            cout << "\n\n\t\t**************************************************************";
        }
    }
    file.close();
}

void Empleado::Mostrar_Indice()
{
    system("cls");
    ifstream file("Indice.txt");
    if(!file.good())
    {
        cout<<"No existe el archivo";
    }
    else
    {
        cout  << "\n\n\t\t\t R F C   E M P L E A D O S:";
        cout  << "\n\n\t\t*****************************************";
        while(!file.eof())
        {
            file.read((char*)&indi,sizeof(indi));
            if(file.eof())
            {
                break;
            }
            cout<<"\n\n\t\t\tRFC : "<<indi.rfc<<endl<<endl;
            cout  << "\n\n\t\t*****************************************";
        }
    }
    file.close();
}

void Empleado::capturar()
{
    system("cls");
    fflush(stdin);
    cout << "\n\t\t\tAnadir E M P L E A D O " << endl;

    cout<< "\n\n\t\t\tRFC :" <<endl << "\n\t\t\t--> ";
    cin.getline(rfc,14);

    cout<< "\n\n\t\t\tDame el nombre del Empleado :"<<endl<< "\n\t\t\t--> ";
    cin.getline(nombre,30);

    cout<<"\n\n\t\t\tDame la seccion :"<<endl<< "\n\t\t\t--> ";
    cin.getline(seccion,30);

    cout<<"\n\n\t\t\tDame el Correo :"<<endl<< "\n\t\t\t--> ";
    cin.getline(correo,30);

    cout<<"\n\n\t\t\tDame la Direccion :"<<endl<< "\n\t\t\t--> ";
    cin.getline(direccion,30);

    cout<<"\n\n\t\t\tDame la Fecha de Inicio :"<<endl<< "\n\t\t\t--> ";
    cin.getline(FechaEntrada,12);

    ofstream file("Empleados.txt",ios::app);
    file.write((char*)&emp,sizeof(emp));
    indi.pos=file.tellp();
    indi.pos-=sizeof(emp);
    file.close();
    strcpy(indi.rfc,rfc);

    ofstream arch("Indice.txt",ios::app);
    arch.write((char*)&indi,sizeof(indi));
    arch.close();
    orden++;
}

void Empleado::buscar()
{
    system("cls");
    char rfcbus[14];
    int band=0;
    //cout<<"posicion "<<Indice.pos;

    ifstream arch("Indice.txt");
    if(!arch.good())
    {
        cout<<"No Existe el archivo";
    }
    else
    {
        cout<<"\n\n\t\t\tDame el RFC :"<<endl<<"\n\t\t\t--> ";
        fflush(stdin);
        cin.getline(rfcbus,14);
        while(!arch.eof())
        {
            arch.read((char*)&indi,sizeof(indi));
            if(arch.eof())
            {
                break;
            }
            if(strcmp(indi.rfc,rfcbus)==0)
            {
                ifstream file("Empleados.txt");
                file.seekg(indi.pos,ios::beg);
                file.read((char*)&emp,sizeof(emp));
                cout<<"\n\n\t\t\tRFC : "<<emp.rfc<<endl<<"\n\t\t\tNombre : "<<emp.nombre<<endl<<"\n\t\t\tSeccion : "<<emp.seccion<<endl<<"\n\t\t\tCorreo : "<<emp.correo<<endl<<"\n\t\t\tDireccion : "<<emp.direccion<<endl<<"\n\t\t\tFecha de Inicio : "<<emp.FechaEntrada;
                file.close();
                band=1;
                break;
            }
        }
        if(band==0)
        {
            cout<<"\n\n\t\t\t NO Existe REGISTRO....."   ;
        }
    }
    arch.close();
}

void Empleado::Modificar()
{
     system("cls");
     char rfcmod[15];
     int band=0;
     int opc;
     ifstream arch("Indice.txt");
     if(!arch.good())
     {
        cout<<"No Existe el archivo";
     }
     else
     {
        cout<<"\n\n\t\t\t Dame el RFC :"<<endl<< "\n\t\t\t--> ";
        fflush(stdin);
        cin.getline(rfcmod,14);
        while(!arch.eof())
        {
            opc=0;
            arch.read((char*)&indi,sizeof(indi));
            if(arch.eof())
            {
                break;
            }
            if(strcmp(indi.rfc,rfcmod)==0 && band==0)
            {
                ifstream file("Empleados.txt");
                file.seekg(indi.pos,ios::beg);

                file.read((char*)&emp,sizeof(emp));
                if(file.eof())
                {
                    break;
                }
                cout<<"\n\n\t\t\tRFC : "<<emp.rfc<<endl<<"\n\t\t\tNombre : "<<emp.nombre<<endl<<"\n\t\t\tSeccion : "<<emp.seccion<<endl<<"\n\t\t\tCorreo : "<<emp.correo<<endl<<"\n\t\t\tDireccion : "<<emp.direccion<<endl<<"\n\t\t\tFecha de Inicio : "<<emp.FechaEntrada;
                cout<<"\n\n\t\t\t Deseas modificarlo\n\n\t\t\t"<<"1.-Si   2.-No\n\n\t\t\t--> ";
                cin>>opc;
                band=1;
                file.close();
                break;
            }//if de comparacion
        }//while
        arch.close();

        if(opc==1)
        {
            fflush(stdin);
            ifstream indiceCo("Indice.txt");
            ifstream empleadosCo("Empleados.txt");
            while(!indiceCo.eof())
            {
                indiceCo.read((char*)&indi,sizeof(indi));
                empleadosCo.read((char*)&emp,sizeof(emp));
                if(indiceCo.eof())
                {
                    break;
                }
                if(strcmp(indi.rfc,rfcmod)==0)
                {
                    cout<< "\n\n\t\t\tRFC :" <<endl << "\n\t\t\t--> ";
                    cin.getline(rfc,14);

                    cout<< "\n\n\t\t\tDame el nombre del Empleado :"<<endl<< "\n\t\t\t--> ";
                    cin.getline(nombre,30);

                    cout<<"\n\n\t\t\tDame la seccion :"<<endl<< "\n\t\t\t--> ";
                    cin.getline(seccion,30);

                    cout<<"\n\n\t\t\tDame el Correo :"<<endl<< "\n\t\t\t--> ";
                    cin.getline(correo,30);

                    cout<<"\n\n\t\t\tDame la Direccion :"<<endl<< "\n\t\t\t--> ";
                    cin.getline(direccion,30);

                    cout<<"\n\n\t\t\tDame la Fecha de Inicio :"<<endl<< "\n\t\t\t--> ";
                    cin.getline(FechaEntrada,12);

                }
                ofstream tem("temp.txt",ios::app);
                tem.write((char*)&emp,sizeof(emp));

                strcpy(indi.rfc,rfc);
                ofstream tem2("tempindi.txt",ios::app);
                tem2.write((char*)&indi,sizeof(indi));
                tem2.close();
                tem.close();
            }//while archivo
        }
        if(band==0)
        {
            cout<<"\n\n\t\t\t NO Existe REGISTRO....."   ;
        }
    }//else
    remove("Indice.txt");
    rename("tempindi.txt","Indice.txt");

    remove("Empleados.txt");
    rename("temp.txt","Empleados.txt");
}

void Empleado::Eliminar()
{
    system("cls");
    char rfceli[15];
    int band=0;
    int opc, cont=0, cont2=0;
    ifstream arch("Indice.txt");
    if(!arch.good())
    {
        cout<<"\n\n\\t\t\tNo Existe el archivo";
    }
    else
    {
        cout<<"\n\n\t\t\t\tDame el RFC :"<<endl << "\n\t\t\t--> ";
        fflush(stdin);
        cin.getline(rfceli,14);
        while(!arch.eof())
        {
            arch.read((char*)&indi,sizeof(indi));
            cont++;
            if(arch.eof())
            {
                break;
            }
            if(strcmp(indi.rfc,rfceli)==0)
            {
                ifstream file("Empleados.txt");
                file.seekg(indi.pos,ios::beg);
                file.read((char*)&emp,sizeof(emp));
                if(file.eof())
                {
                    break;
                }
                cout<<"\n\n\t\t\tRFC : "<<emp.rfc<<endl<<"\n\t\t\tNombre : "<<emp.nombre<<endl<<"\n\t\t\tSeccion : "<<emp.seccion<<endl<<"\n\t\t\tCorreo : "<<emp.correo<<endl<<"\n\t\t\tDireccion : "<<emp.direccion<<endl<<"\n\t\t\tFecha de Inicio : "<<emp.FechaEntrada;
                cout<<"\n\n\t\t\tDeseas eliminar \n\n\t\t\t 1.-Si   2.-No"<<"\n\n\t\t\t--> "; cin>>opc;
                band=1;
                file.close();
                break;
            }//if de comparacion
        }//while
        arch.close();

        if(opc==1)
        {
            ifstream indiceTem("Indice.txt");
            ifstream empleadosTem("Empleados.txt");
            while(!indiceTem.eof())
            {
                indiceTem.read((char*)&indi,sizeof(indi));
                empleadosTem.read((char*)&emp,sizeof(emp));
                if(indiceTem.eof())
                {
                    break;
                }
                if(strcmp(indi.rfc,rfceli))
                {
                    cont2++;
                    ofstream mien("temp.txt",ios::app);
                    mien.write((char*)&emp,sizeof(emp));

                    strcpy(indi.rfc,rfc);
                    ofstream mien2("tempindi.txt",ios::app);
                    mien2.write((char*)&indi,sizeof(indi));
                    mien2.close();
                    mien.close();
                }
            }//while archivo
            indiceTem.close();
            empleadosTem.close();

            remove("Indice.txt");
            rename("tempindi.txt","Indice.txt");

            remove("Empleados.txt");
            rename("temp.txt","Empleados.txt");
        }//if
        else
        {

        }
        if(band==0)
        {
            cout<<"\n\n\t\t\t NO Existe REGISTRO....."   ;
        }
    }//else
}

void Empleado::Orden()
{
    system("cls");
    int i=0;
    char indice[20][14];
    char aux[20];

    ifstream file("Indice.txt");
    if(!file.good())
    {
        cout<<"\n\n\t\t\tNo Existe el archivo";
    }
    else
    {
        while(!file.eof())
        {
            file.read((char*)&indi,sizeof(indi));
            if(file.eof())
            {
                break;
            }
            char *cadena=indi.rfc;
            strcpy(indice[i],cadena);
            i++;
        }
    }
    file.close();

    for(int i=0;i<orden-1;i++)
    for(int j=i+1;j<orden;j++)
        if(strcmp(indice[i],indice[j])>0)
        {
            strcpy(aux,indice[j]);
            strcpy(indice[j],indice[i]);
            strcpy(indice[i],aux);
            system("cls");
        }
    for(int i=0;i<orden;i++)
    {
        strcpy(indi.rfc,indice[i]);

        ofstream tempor("tempindi.txt",ios::app);
        tempor.write((char*)&indi,sizeof(indi));
        tempor.close();
    }

    remove("Indice.txt");
    rename("tempindi.txt","Indice.txt");
    cout << "\n\n\t\t\t O R  D E N A D O . . . .";
}

void Empleado::menu()
{
    int opc;
    do
    {
        system("cls");
        cout << "\n\n\t\t\t\tSELECCIONA UNA OPCION:" << endl;
        cout << "\n\n\t\t*****************************************************";
        cout << "\n\n\t\t\t( 1 ) Capturar" << "\n\n\t\t\t( 2 ) Buscar" << "\n\n\t\t\t( 3 ) Mostrar todos" << "\n\n\t\t\t( 4 ) Modificar" << "\n\n\t\t\t( 5 ) Eliminar" << "\n\n\t\t\t( 6 ) Mostrar Indice" << "\n\n\t\t\t( 7 ) Ordenar Indice" << "\n\n\t\t\t( 8 ) Atras"  << "\n\n\t\t\t--> ";
        opc = getch();
        switch(opc)
        {
            case 49:
            {
                emp.capturar();
                getch();
            }break;
            case 50:
            {
                emp.buscar();
                getch();
            }break;
            case 51:
            {
                emp.mostrar();
                getch();
            }break;
            case 52:
            {
                emp.Modificar();
                getch();
            }break;
            case 53:
            {
                 emp.Eliminar();
                 getch();
            }break;
            case 54:
            {
                emp.Mostrar_Indice();
                getch();
            }break;
            case 55:
            {
                 emp.Orden();
                 getch();
            }break;
            case 56:
            {

            }break;
            default:
            {
                cout << "\n\n\t\t\t Opcion Invalida";
            }break;
        }
    }while(opc!=56);
}
