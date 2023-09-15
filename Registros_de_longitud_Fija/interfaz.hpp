#ifndef INTERFAZ_HPP_INCLUDED
#define INTERFAZ_HPP_INCLUDED

class InterfazUsuario
{
public:
    InterfazUsuario(); // Constructor
    ~InterfazUsuario(); // Destructor
    void LimpiarPantalla();
    void MostrarManiqui();
    void MenuPrincipal(); // Menú principal
    void MenuProductos(); // Menú de productos
    void MenuPedidos(); // Menú de pedidos
    void MenuProveedores(); // Menú de proveedores
};

#endif // INTERFAZ_HPP_INCLUDED