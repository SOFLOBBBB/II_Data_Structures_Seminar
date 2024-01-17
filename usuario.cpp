#include "usuario.hpp"

using namespace std;

// Implementación de los métodos setter y getter
void Usuario::setCodigo(const string& Codigo) {
    codigo = Codigo;
}

void Usuario::setNombre(const string& Nombre) {
    nombre = Nombre;
}

void Usuario::setApellido(const string& Apellido) {
    apellido = Apellido;
}

void Usuario::setTelefono(const string& Telefono) {
    telefono = Telefono;
}

void Usuario::setDireccion(const string& Direccion) {
    direccion = Direccion;
}

void Usuario::setContrasena(const string& Contrasena) {
    contrasena = Contrasena;
}

string Usuario::getCodigo() const {
    return codigo;
}

string Usuario::getNombre() const {
    return nombre;
}

string Usuario::getApellido() const {
    return apellido;
}

string Usuario::getTelefono() const {
    return telefono;
}

string Usuario::getDireccion() const {
    return direccion;
}

string Usuario::getContrasena() const {
    return contrasena;
}

//Metodos

void Usuario::AgregarUsuario() {
    cout << "\n\n\t\t\tIngrese el codigo: " << "\n\n\t\t\t--> ";;
    cin.ignore();
    getline(cin, codigo);

    cout << "\n\n\t\t\tIngrese el nombre: " << "\n\n\t\t\t--> ";;
    getline(cin, nombre);

    cout << "\n\n\t\t\tIngrese el apellido: " << "\n\n\t\t\t--> ";;
    getline(cin, apellido);

    cout << "\n\n\t\t\tIngrese el telefono: " << "\n\n\t\t\t--> ";;
    getline(cin, telefono);

    cout << "\n\n\t\t\tIngrese la direccion: " << "\n\n\t\t\t--> ";;
    getline(cin, direccion);

    cout << "\n\n\t\t\tIngrese la contrasena: " << "\n\n\t\t\t--> ";
    getline(cin, contrasena);

    // Guardar en el archivo
    ofstream archivo("Usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << codigo << "|" << nombre << "|" << apellido << "|" << telefono << "|" << direccion << "|" << contrasena << "\n";
        archivo.close();
        cout << "\n\n\t\t\tUsuario agregado y guardado en Usuarios.txt" << endl;
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}

void Usuario::MostrarUsuario() {
    ifstream archivo("Usuarios.txt");
    if (archivo.is_open()) {
        string codigo, nombre, apellido, telefono, direccion, contrasena;
        bool encontrado = false;
        while (getline(archivo, codigo, '|')) {
            getline(archivo, nombre, '|');
            getline(archivo, apellido, '|');
            getline(archivo, telefono, '|');
            getline(archivo, direccion, '|');
            getline(archivo, contrasena);

            cout << "\n\n\t\t\tUsuario encontrado:" << endl;
            cout << "\n\n\t\t\tCodigo:     " << codigo;
            cout << "\n\t\t\tNombre:       " << nombre;
            cout << "\n\t\t\tApellido:     " << apellido;
            cout << "\n\t\t\tTelefono:     " << telefono;
            cout << "\n\t\t\tDireccion:    " << direccion;
            cout << "\n\t\t\tContrasena:   " << contrasena;

            encontrado = true;
        }
        archivo.close();
        if (!encontrado) {
            cout << "\n\n\t\t\tNo se encontraron usuarios." << endl;
        }
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}

void Usuario::ModificarUsuario() {
    string codigoBusqueda;
    cout << "\n\n\t\t\tIngrese el codigo del usuario a modificar: " << "\n\n\t\t\t--> ";
    cin.ignore();
    getline(cin, codigoBusqueda);
    bool encontrado = false;
    ifstream archivoLectura("Usuarios.txt");
    ofstream archivoTemp("temp.txt", ios::app);
    if (archivoLectura.is_open() && archivoTemp.is_open()) {
        string codigo, nombre, apellido, telefono, direccion, contrasena;
        while (getline(archivoLectura, codigo, '|')) {
            getline(archivoLectura, nombre, '|');
            getline(archivoLectura, apellido, '|');
            getline(archivoLectura, telefono, '|');
            getline(archivoLectura, direccion, '|');
            getline(archivoLectura, contrasena);
            if (codigo == codigoBusqueda) {
                encontrado = true;
                cout << "\n\n\t\t\tUsuario encontrado. Ingrese los nuevos datos:" << endl;
                cout << "\n\n\t\t\tNuevo codigo: " << "\n\n\t\t\t--> ";
                getline(cin, codigo);
                cout << "\n\n\t\t\tNuevo nombre: " << "\n\n\t\t\t--> ";
                getline(cin, nombre);
                cout << "\n\n\t\t\tNuevo apellido: " << "\n\n\t\t\t--> ";
                getline(cin, apellido);
                cout << "\n\n\t\t\tNuevo telefono: " << "\n\n\t\t\t--> ";
                getline(cin, telefono);
                cout << "\n\n\t\t\tNueva direccion: " << "\n\n\t\t\t--> ";
                getline(cin, direccion);
                cout << "\n\n\t\t\tNueva contrasena: " << "\n\n\t\t\t--> ";
                getline(cin, contrasena);
            }
            archivoTemp << codigo << "|" << nombre << "|" << apellido << "|" << telefono << "|" << direccion << "|" << contrasena << "\n";
        }
        archivoLectura.close();
        archivoTemp.close();
        if (!encontrado) {
            cout << "\n\n\t\t\tUsuario no encontrado." << endl;
        } else {
            remove("Usuarios.txt");
            rename("temp.txt", "Usuarios.txt");
            cout << "\n\n\t\t\tUsuario modificado y guardado en Usuarios.txt" << endl;
        }
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}


void Usuario::BuscarUsuario() {
    string codigoBusqueda;
    cout << "\n\n\t\t\tIngrese el codigo del usuario a buscar: " << "\n\n\t\t\t--> ";
    cin.ignore();
    getline(cin, codigoBusqueda);

    ifstream archivo("Usuarios.txt");
    if (archivo.is_open()) {
        string codigo, nombre, apellido, telefono, direccion, contrasena;
        bool encontrado = false;
        while (getline(archivo, codigo, '|')) {
            getline(archivo, nombre, '|');
            getline(archivo, apellido, '|');
            getline(archivo, telefono, '|');
            getline(archivo, direccion, '|');
            getline(archivo, contrasena);
            if (codigo == codigoBusqueda) {
                encontrado = true;
                cout << "\n\n\t\t\tUsuario encontrado:" << endl;
                cout << "\n\n\t\t\tCodigo:       " << codigo;
                cout << "\n\n\t\t\tNombre:       " << nombre;
                cout << "\n\n\t\t\tApellido:     " << apellido;
                cout << "\n\n\t\t\tTelefono:     " << telefono;
                cout << "\n\n\t\t\tDireccion:    " << direccion;
                cout << "\n\n\t\t\tContrasena:   " << contrasena;
                break;
            }
        }
        archivo.close();
        if (!encontrado) {
            cout << "\n\n\t\t\tUsuario no encontrado." << endl;
        }
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}

void Usuario::EliminarUsuario() {
    string codigoBusqueda;
    cout << "\n\n\t\t\tIngrese el codigo del usuario a eliminar: " << "\n\n\t\t\t-->";
    cin.ignore();
    getline(cin, codigoBusqueda);

    string confirmacion;
    cout << "\n\n\t\t\t¿Esta seguro de que desea eliminar este usuario? (S/N): " << "\n\n\t\t\t\n\n\t\t\t--> ";
    getline(cin, confirmacion);

    if (confirmacion == "S" || confirmacion == "s") {
        ifstream archivoLectura("Usuarios.txt");
        ofstream archivoTemp("temp.txt", ios::app);
        if (archivoLectura.is_open() && archivoTemp.is_open()) {
            string codigo, nombre, apellido, telefono, direccion, contrasena;
            bool encontrado = false;
            while (getline(archivoLectura, codigo, '|')) {
                getline(archivoLectura, nombre, '|');
                getline(archivoLectura, apellido, '|');
                getline(archivoLectura, telefono, '|');
                getline(archivoLectura, direccion, '|');
                getline(archivoLectura, contrasena);
                if (codigo != codigoBusqueda) {
                    archivoTemp << codigo << "|" << nombre << "|" << apellido << "|" << telefono << "|" << direccion << "|" << contrasena << "\n";
                } else {
                    encontrado = true;
                }
            }
            archivoLectura.close();
            archivoTemp.close();
            if (encontrado) {
                remove("Usuarios.txt");
                rename("temp.txt", "Usuarios.txt");
                cout << "\n\n\t\t\tUsuario eliminado correctamente." << endl;
            } else {
                cout << "Usuario no encontrado." << endl;
                remove("temp.txt");
            }
        } else {
            cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
        }
    } else {
        cout << "\n\n\t\t\tEliminacion cancelada." << endl;
    }
}

void Usuario::Encriptar() {
    ifstream archivoLectura("Usuarios.txt");
    ofstream archivoEncriptado("UsuariosEncriptados.txt", ios::app);
    if (archivoLectura.is_open() && archivoEncriptado.is_open()) {
        char clave = 'K'; // Clave de encriptación

        string linea;
        while (getline(archivoLectura, linea)) {
            for (size_t i = 0; i < linea.length(); i++) {
                linea[i] = linea[i] ^ clave; // Aplicar XOR
            }
            archivoEncriptado << linea << "\n";
        }
        archivoLectura.close();
        archivoEncriptado.close();
        cout << "\n\n\t\t\tArchivo encriptado correctamente y guardado en UsuariosEncriptados.txt" << endl;
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}

void Usuario::Desencriptar() {
    ifstream archivoEncriptado("UsuariosEncriptados.txt");
    ofstream archivoDesencriptado("UsuariosDesencriptados.txt", ios::app);
    if (archivoEncriptado.is_open() && archivoDesencriptado.is_open()) {
        char clave = 'K'; // Clave de encriptación

        string linea;
        while (getline(archivoEncriptado, linea)) {
            for (size_t i = 0; i < linea.length(); i++) {
                linea[i] = linea[i] ^ clave; // Aplicar XOR nuevamente para desencriptar
            }
            archivoDesencriptado << linea << "\n";
        }
        archivoEncriptado.close();
        archivoDesencriptado.close();
        cout << "\n\n\t\t\tArchivo desencriptado correctamente y guardado en UsuariosDesencriptados.txt" << endl;
    } else {
        cout << "\n\n\t\t\tNo se pudo abrir el archivo." << endl;
    }
}

void Usuario::MenuOpciones()
{
    int opcion = 0;

    while (opcion != 8)
        {
        system("cls");
        cout << "\n\n\t\t\t\tMENU";
        cout << "\n\n\t\t\t| 1 | Agregar Usuario";
        cout << "\n\n\t\t\t| 2 | Mostrar Usuario";
        cout << "\n\n\t\t\t| 3 | Modificar Usuario";
        cout << "\n\n\t\t\t| 4 | Buscar Usuario";
        cout << "\n\n\t\t\t| 5 | Eliminar Usuario";
        cout << "\n\n\t\t\t| 6 | Encriptar Datos";
        cout << "\n\n\t\t\t| 7 | Desencriptar Datos";
        cout << "\n\n\t\t\t| 8 | Atras";
        cout << "\n\n\t\t\tIngrese una opcion: " << "\n\n\t\t\t--> ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                system("cls");
                AgregarUsuario();
                break;
            }
            case 2: {
                system("cls");
                MostrarUsuario();
                break;
            }
            case 3: {
                system("cls");
                ModificarUsuario();
                break;
            }
            case 4: {
                system("cls");
                BuscarUsuario();
                break;
            }
            case 5: {
                system("cls");
                EliminarUsuario();
                break;
            }
            case 6: {
                system("cls");
               Encriptar();
               break;
            }
             case 7: {
                 system("cls");
                Desencriptar();
                break;
            }
            case 8: {
                break;
            }
            default: {
                cout << "\n\n\t\t\tOpción no válida, intente nuevamente." << endl;
                break;
            }
            getch();
        }
    }

}
