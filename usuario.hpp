#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

class Usuario
{

    private:
        std::string codigo;
        std::string nombre;
        std::string apellido;
        std::string telefono;
        std::string direccion;
        std::string contrasena;

    public:
        void AgregarUsuario();
        void MostrarUsuario();
        void ModificarUsuario();
        void EliminarUsuario();
        void BuscarUsuario();
        void Encriptar();
        void Desencriptar();
        void MenuOpciones();

        // Declaración de métodos setter
    void setCodigo(const std::string& Codigo);
    void setNombre(const std::string& Nombre);
    void setApellido(const std::string& Apellido);
    void setTelefono(const std::string& Telefono);
    void setDireccion(const std::string& Direccion);
    void setContrasena(const std::string& Contrasena);

    // Declaración de métodos getter
    std::string getCodigo() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getTelefono() const;
    std::string getDireccion() const;
    std::string getContrasena() const;
};


#endif // USUARIO_HPP
