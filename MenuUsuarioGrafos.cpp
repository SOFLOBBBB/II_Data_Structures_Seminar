#include "MenuUsuarioGrafos.hpp"

using namespace std;

void InterfazGrafo::menuUsuario() {
    MetodoDePago origVert, destVert;
    string auxTemp;
    int opc, auxInt;

    setlocale(LC_ALL, "");

    do {
        system("cls");
        cout << "\n\n\t\t\tM E T O D O    D E    P A G O";
        cout << "\n\n\t\t\t( 1 ) Insertar Vertice";
        cout << "\n\n\t\t\t( 2 ) Eliminar Vertice";
        cout << "\n\n\t\t\t( 3 ) Insertar Arista";
        cout << "\n\n\t\t\t( 4 ) Eliminar Arista";
        cout << "\n\n\t\t\t( 5 ) Mostrar Grafo";
        cout << "\n\n\t\t\t( 6 ) Recorridos";
        cout << "\n\n\t\t\t( 7 ) Vaciar Grafo";
        cout << "\n\n\t\t\t( 8 ) Guardar Grafo";
        cout << "\n\n\t\t\t( 9 ) Cargar Grafo";
        cout << "\n\n\t\t\t( 0 ) Salir";
        cout << "\n\n\t\t\tIngrese Una Opcion: " << "\n\n\t\t\t--> ";
        cin >> opc;

        cin.ignore();

        cout << endl << endl;

        switch(opc)
        {
            case 1:
                myGraph->insertVertex(capturarPago());
                break;
            case 2:
                cout << "\n\n\t\t\tIngrese la Clave: ";
                getline(cin, auxTemp);
                origVert.setClave(auxTemp);

                if(myGraph->findVertex(origVert) != nullptr)
                    {
                    cout << "\n\n\t\t\tEliminar Vértice ";
                    if(op())
                        {
                        myGraph->deleteVertex(origVert);
                        cout << "\n\n\t\t\tVértice Eliminado" << endl;
                        }
                    }
                else {
                    cout << "\n\n\t\t\tEl Vértice no existe" << endl;
                    }

                break;
            case 3:
                cout << "\n\n\t\t\tClave de Origen: ";
                getline(cin, auxTemp);
                origVert.setClave(auxTemp);

                if(myGraph->findVertex(origVert) == nullptr) {
                    cout << "\n\n\t\t\tEl Origen no existe" << endl;
                    break;
                    }

                cout << "\n\n\t\t\tClave de Destino: ";
                getline(cin, auxTemp);
                destVert.setClave(auxTemp);

                if(myGraph->findVertex(destVert) == nullptr) {
                    cout << "\n\n\t\t\tEl Destino no existe" << endl;
                    break;
                    }

                if(myGraph->findEdge(origVert, destVert) != nullptr) {
                    cout << "\n\n\t\t\tLa Arista ya existe" << endl;
                    system("pause");
                    break;
                    }

                cout << "\n\n\t\t\tPeso: ";
                cin >> auxInt;
                cin.ignore();

                myGraph->insertEdge(origVert, destVert, auxInt);
                cout << "\n\n\t\t\tArista insertada" << endl;
                break;
            case 4:
                cout << "\n\n\t\t\tClave de Origen: ";
                getline(cin, auxTemp);
                origVert.setClave(auxTemp);

                cout << "\n\n\t\t\tClave de Destino: ";
                getline(cin, auxTemp);
                destVert.setClave(auxTemp);

                if(myGraph->findEdge(origVert, destVert) != nullptr) {
                    cout << "\n\n\t\t\tEliminar Arista ";
                    if(op()) {
                        myGraph->deleteEdge(origVert, destVert);
                        cout << "\n\n\t\t\tArista Eliminada" << endl;
                        }
                    }
                else {
                    cout << "\n\n\t\t\tLa Arista no existe" << endl;
                    }

                break;
            case 5:
                cout << myGraph->toString() << endl;
                break;
            case 6:
                cout << "\n\n\t\t\tG R A F O" << endl;
                cout << myGraph->toString() << endl;
                cout << endl << endl;

                cout << "\n\n\t\t\tClave de Origen: ";
                getline(cin, auxTemp);
                origVert.setClave(auxTemp);
                if(myGraph->findVertex(origVert) == nullptr) {
                    cout << "\n\n\t\t\tClave de Origen no existe" << endl;
                    break;
                    }

                cout << "\n\n\t\t\tClave Destino: ";
                getline(cin, auxTemp);
                destVert.setClave(auxTemp);
                if(myGraph->findVertex(destVert) == nullptr) {
                    cout << "\n\n\t\t\tla Clave no existe" << endl;
                    break;
                    }

                cout << "\n\n\t\t\tPrimero en Anchura" << endl;
                cout << myGraph->breadthFirstSearch(origVert, destVert) << endl;
                cout << endl << endl;

                cout << "\n\n\t\t\tPrimero en Profundidad" << endl;
                cout << myGraph->depthFirstSearch(origVert, destVert) << endl;
                break;
            case 7:
                cout << "\n\n\t\t\tEliminar Todo ";
                if(op()) {
                    myGraph->deleteAll();
                    cout << "\n\n\t\t\tGrafo Eliminado" << endl;
                    }
                break;
            case 8:
                cout << "\n\n\t\t\tGuardar Grafo ";
                if(op()) {
                    if(myGraph->saveData(FILE_NAME)) {
                        cout << "\n\n\t\t\tGrafo Guardado" << endl;
                        }
                    else {
                        cout << "\n\n\t\t\tError al Guardar el Grafo" << endl;
                        }
                    }
                break;
            case 9:
                cout << "\n\n\t\t\tCargar Grafo ";
                if(op()) {
                    if(myGraph->loadData(FILE_NAME)) {
                        cout << "\n\n\t\t\tGrafo Cargado" << endl;
                        }
                    else {
                        cout << "\n\n\t\t\tError al Cargar el Grafo" << endl;
                        }
                    }
                break;
            case 0:
                return;
            break;
            default: cout << "\n\n\t\t\tOpcion invalida" << endl;
            }

    cout << endl << endl;
    cout << "\n\n\t\t\tPresione una tecla para continuar" << endl;
    getch();

    }while(true);
    }

MetodoDePago InterfazGrafo::capturarPago() {
    MetodoDePago myPago;
    string auxTemp;

    cout << "\n\n\t\t\tClave: "  << "\n\n\t\t\t--> ";
    getline(cin, auxTemp);
    myPago.setClave(auxTemp);

    cout << "\n\n\t\t\tFecha De vencimiento: " << "\n\n\t\t\t--> ";
    getline(cin, auxTemp);
    myPago.setFecha_venci(auxTemp);

    cout << "\n\n\t\t\tNombre del propietario: " << "\n\n\t\t\t--> ";
    getline(cin, auxTemp);
    myPago.setNombre(auxTemp);

    return myPago;
    }

bool InterfazGrafo::op() {
    char op;
    cout << "\n\n\t\t(S/N): " << "\n\n\t\t\t--> ";
    cin >> op;
    cin.ignore();

    return toupper(op) == 'S';
    }

InterfazGrafo::InterfazGrafo(Graph<MetodoDePago>* g) : myGraph(g) {
    menuUsuario();
    }
