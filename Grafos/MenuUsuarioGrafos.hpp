#ifndef MENUUSUARIOGRAFOS_HPP_INCLUDED
#define MENUUSUARIOGRAFOS_HPP_INCLUDED

#include <iostream>
#include <string>
#include <wchar.h>
#include <locale.h>
#include <conio.h>

#include "graph.hpp"
#include "MetodoDePago.hpp"

#define FILE_NAME "metodoDePago.txt"

class InterfazGrafo {
    private:
        Graph<MetodoDePago>* myGraph;

        void menuUsuario();

        MetodoDePago capturarPago();
        bool op();

    public:
        InterfazGrafo(Graph<MetodoDePago>*);
    };

#endif // MENUUSUARIOGRAFOS_HPP_INCLUDED
