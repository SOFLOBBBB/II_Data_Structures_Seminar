#ifndef VENTAS_HPP_INCLUDED
#define VENTAS_HPP_INCLUDED

#include<iostream>

using namespace std;

class Ventas
{
public:

    Ventas();
    string getProducto() const;
    void setProducto(const string &value);

    string getFecha() const;
    void setFecha(const string &value);

    string getPrecio() const;
    void setPrecio(const string &value);

    string getCodigo() const;
    void setCodigo(const string &value);

    string getBandera() const;
    void setBandera(const string &value);

    friend ostream& operator <<(ostream &out,const Ventas &p){
        out<<p.getProducto() <<","
           <<p.getFecha()<<","
           <<p.getPrecio() <<","
           <<p.getCodigo() <<","
           <<p.getBandera()<<",";
        return out;
    }

private:

    string producto;
    string fecha;
    string precio;
    string codigo;
    string bandera;
};

#endif // VENTAS_HPP_INCLUDED
