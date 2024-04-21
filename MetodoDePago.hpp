#ifndef METODODEPAGO_HPP_INCLUDED
#define METODODEPAGO_HPP_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <wchar.h>
#include <locale.h>

class MetodoDePago
{
    private:

        std::string clave;
        std::string nombre;
        std::string fecha_venci;

        void copyAll(const MetodoDePago&);

    public:
        MetodoDePago();
        MetodoDePago(const MetodoDePago&);

        MetodoDePago& operator = (const MetodoDePago&);

        std::string toString() const;

        std::string getClave() const;
        std::string getNombre() const;
        std::string getFecha_venci() const;

        void setClave(const std::string&);
        void setNombre(const std::string&);
        void setFecha_venci(const std::string&);

        bool operator == (const MetodoDePago&) const;
        bool operator != (const MetodoDePago&) const;
        bool operator < (const MetodoDePago&) const;
        bool operator > (const MetodoDePago&) const;
        bool operator <= (const MetodoDePago&) const;
        bool operator >= (const MetodoDePago&) const;

        friend std::istream& operator >> (std::istream&, MetodoDePago&);
        friend std::ostream& operator << (std::ostream&, const MetodoDePago&);
};

#endif // METODODEPAGO_HPP_INCLUDED
