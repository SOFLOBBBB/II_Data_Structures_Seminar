#include "MetodoDePago.hpp"

void MetodoDePago::copyAll(const MetodoDePago& m) {
    clave = m.clave;
    fecha_venci = m.fecha_venci;
    nombre = m.nombre;
    }

MetodoDePago::MetodoDePago() { }

MetodoDePago::MetodoDePago(const MetodoDePago& m) {
    copyAll(m);
    }

MetodoDePago& MetodoDePago::operator = (const MetodoDePago& m) {
    copyAll(m);
    return *this;
    }

std::string MetodoDePago::toString() const {
    std::stringstream ss;

    ss << clave << "|" << fecha_venci << "|" <<  nombre;
    return ss.str();
    }

std::string MetodoDePago::getClave() const {
    return clave;
    }

std::string MetodoDePago::getNombre() const {
    return nombre;
    }

std::string MetodoDePago::getFecha_venci() const {
    return fecha_venci;
    }

void MetodoDePago::setClave(const std::string& c) {
    clave = c;
    }

void MetodoDePago::setNombre(const std::string& n) {
    nombre = n;
    }

void MetodoDePago::setFecha_venci(const std::string& f) {
    fecha_venci = f;
    }

bool MetodoDePago::operator == (const MetodoDePago& c) const {
    return clave == c.clave;
    }

bool MetodoDePago::operator != (const MetodoDePago& c) const {
    return !(*this == c);
    }

bool MetodoDePago::operator < (const MetodoDePago& c) const {
    return clave < c.clave;
    }

bool MetodoDePago::operator > (const MetodoDePago& c) const {
    return !(*this <= c);
    }

bool MetodoDePago::operator <= (const MetodoDePago& c) const {
    return *this < c or *this == c;
    }

bool MetodoDePago::operator >= (const MetodoDePago& c) const {
    return !(*this < c);
    }

std::istream& operator >> (std::istream& is, MetodoDePago& c) {
    std::string str;
    getline(is, str, '*');
    std::stringstream ss(str);

    getline(ss, c.clave, '|');
    getline(ss, c.fecha_venci, '|');
    getline(ss, c.nombre, '|');

    return is;
    }

std::ostream& operator << (std::ostream& os, const MetodoDePago& c) {
    os << c.clave << '|';
    os << c.fecha_venci << '|';
    os << c.nombre << '|';
    os << '*';

    return os;
    }
