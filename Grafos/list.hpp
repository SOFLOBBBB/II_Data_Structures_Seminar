#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>

template <class T>
class ListaGrafo {
        class Node;

    public:
        class Exception : public std::exception {
            private:
                std::string msg;

            public:
                Exception()noexcept : msg("Error indefinido") {}

                Exception(const Exception& ex) noexcept : msg(ex.msg) {}

                Exception(const std::string& m) : msg(m) {}

                Exception& operator = (const Exception& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                    }

                virtual ~Exception() {}

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };

        typedef Node* Position;

    private:
        class Node {
            private:
                T* dataPtr;

                Position prev;
                Position next;

            public:
                class Exception : public ListaGrafo<T>::Exception {
                    public:
                        using ListaGrafo<T>::Exception::Exception;
                    };

                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr();
                T& getData();
                Position getPrev() const;
                Position getNext() const;

                void setDataPtr(const T*);
                void setData(const T&);
                void setPrev(const Position&);
                void setNext(const Position&);
            };

        Position headerPtr;

        void copyAll(const ListaGrafo<T>&);
        bool isValidPos(const Position&) const;

    public:
        ListaGrafo();
        ListaGrafo(const ListaGrafo<T>&);

        ~ListaGrafo();

        bool isEmpty() const;

        std::string toString() const;

        void insertData(const Position&, const T&);
        void deleteData(const Position&);

        T retrieve(const Position&) const;
        Position findData(const T&) const;

        Position getFirstPos() const;
        Position getLastPos() const;
        Position getPrevPos(const Position&) const;
        Position getNextPos(const Position&) const;

        /// Disk ***********************

        void writeToDisk(const std::string&);
        void readFromDisk(const std::string&);

        /// ****************************

        void deleteAll();

        ListaGrafo<T>& operator = (const ListaGrafo<T>&);

        /// **********************************

        Position findData(const T&, int(const T&, const T&)) const;
    };

/// Implementation

/// Node

template <class T>
ListaGrafo<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

template <class T>
ListaGrafo<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr) {
    if(dataPtr == nullptr) {
        throw Exception("Memoria no disponible, Node");
        }
    }

template <class T>
ListaGrafo<T>::Node::~Node() {
    if(dataPtr != nullptr) {
        delete dataPtr;
        }
    }

template <class T>
T* ListaGrafo<T>::Node::getDataPtr() {
    return dataPtr;
    }

template <class T>
T& ListaGrafo<T>::Node::getData() {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, getData");
        }

    return *dataPtr;
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::Node::getPrev() const {
    return prev;
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::Node::getNext() const {
    return next;
    }

template <class T>
void ListaGrafo<T>::Node::setDataPtr(const T* p) {
    dataPtr = p;
    }

template <class T>
void ListaGrafo<T>::Node::setData(const T& e) {
    if(dataPtr == nullptr) {
        if((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible, setData");
            }
        }
    else {
        *dataPtr = e;
        }
    }

template <class T>
void ListaGrafo<T>::Node::setPrev(const Position& p) {
    prev = p;
    }

template <class T>
void ListaGrafo<T>::Node::setNext(const Position& p) {
    next = p;
    }

/// List

/// Private:

template <class T>
void ListaGrafo<T>::copyAll(const ListaGrafo<T>& l) {
    Position aux(l.headerPtr->getNext()), newNode;
    while(aux != l.headerPtr) {
        try {
            if((newNode = new Node(aux->getData())) == nullptr) {
                throw Exception("Memoria no disponible, copyAll");
                }
            }
        catch(const typename Node::Exception& ex) {
            throw Exception("Memoria no disponible en nuevo nodo, copyAll");
            }

        newNode->setPrev(headerPtr->getPrev());
        newNode->setNext(headerPtr);

        headerPtr->getPrev()->setNext(newNode);
        headerPtr->setPrev(newNode);

        aux = aux->getNext();
        }
    }

template <class T>
bool ListaGrafo<T>::isValidPos(const Position& p) const {
    Position aux(headerPtr->getNext());
    while(aux != headerPtr and p != aux) {
        aux = aux->getNext();
        }

    return aux == headerPtr ? false : true;
    }

/// Public:

template <class T>
ListaGrafo<T>::ListaGrafo() : headerPtr(new Node) {
    if(headerPtr == nullptr) {
        throw Exception("Memoria no disponible, ListaGrafo");
        }

    headerPtr->setNext(headerPtr);
    headerPtr->setPrev(headerPtr);
    }

template <class T>
ListaGrafo<T>::ListaGrafo(const ListaGrafo<T>& l) : ListaGrafo() {
    copyAll(l);
    }

template <class T>
ListaGrafo<T>::~ListaGrafo() {
    deleteAll();

    delete headerPtr;
    }

template <class T>
bool ListaGrafo<T>::isEmpty() const {
    return headerPtr->getNext() == headerPtr;
    }

template <class T>
std::string ListaGrafo<T>::toString() const {
    std::string l;
    Position aux(headerPtr->getNext());

    while(aux != headerPtr) {
        l += aux->getData().toString() + '\n';

        aux = aux->getNext();
        }

    return l;
    }

template <class T>
void ListaGrafo<T>::insertData(const Position& p, const T& e) {
    if(p != nullptr and !isValidPos(p)) {
        throw Exception("Posicion invalida, insertData");
        }

    Position newNode;
    try {
        if((newNode = new Node(e)) == nullptr) {
            throw Exception("Memoria no disponible, insertData");
            }
        }
    catch(const typename Node::Exception& ex) {
        throw Exception("Memoria no disponible en nuevo nodo, insertData");
        }

    Position insPos(p == nullptr ? headerPtr : p);

    newNode->setNext(insPos->getNext());
    newNode->setPrev(insPos);

    insPos->getNext()->setPrev(newNode);
    insPos->setNext(newNode);

    }

template <class T>
void ListaGrafo<T>::deleteData(const Position& p) {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, deleteData");
        }

    p->getNext()->setPrev(p->getPrev());
    p->getPrev()->setNext(p->getNext());

    delete p;
    }

template <class T>
T ListaGrafo<T>::retrieve(const Position& p) const {
    if(!isValidPos(p)) {
        throw Exception("Posicion invalida, retrieve");
        }

    return p->getData();
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::findData(const T& e) const {
    Position aux(headerPtr->getNext());
    while(aux != headerPtr and aux->getData() != e) {
        aux = aux->getNext();
        }

    return aux == headerPtr ? nullptr : aux;
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::getFirstPos() const {
    return isEmpty() ? nullptr : headerPtr->getNext();
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::getLastPos() const {
    return isEmpty() ? nullptr : headerPtr->getPrev();
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::getPrevPos(const Position& p) const {
    return (p == headerPtr->getNext() or !isValidPos(p)) ? nullptr : p->getPrev();
    }

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::getNextPos(const Position& p) const {
    return (p == headerPtr->getPrev() or !isValidPos(p)) ? nullptr : p->getNext();
    }

/// Disk *******************************************************************

template <class T>
void ListaGrafo<T>::writeToDisk(const std::string& fileName) {
    std::ofstream myFile;

    myFile.open(fileName, std::ios_base::trunc);

    if(!myFile.is_open()) {
        throw Exception("No se pudo abrir el archivo para escritua, writeToDisk");
        }

    Position aux(headerPtr->getNext());
    while(aux != headerPtr) {
        myFile << aux->getData() << std::endl;

        aux = aux->getNext();
        }

    myFile.close();
    }

template <class T>
void ListaGrafo<T>::readFromDisk(const std::string& fileName) {
    std::ifstream myFile;

    myFile.open(fileName);

    if(!myFile.is_open()) {
        throw Exception("No se pudo abrir el archivo para lectura, readFromDisk");
        }

    deleteAll();

    T e;
    Position newNode;
    try {
        while(myFile >> e) {
            try {
                if((newNode = new Node(e)) == nullptr) {
                    throw Exception("Memoria no disponible, readFromDisk");
                    }
                }
            catch(const typename Node::Exception& ex) {
                throw Exception("Memoria no disponible en nuevo nodo, readFromDisk");
                }

            newNode->setPrev(headerPtr->getPrev());
            newNode->setNext(headerPtr);

            headerPtr->getPrev()->setNext(newNode);
            headerPtr->setPrev(newNode);

            }
        }
    catch(const typename ListaGrafo::Exception& ex) {
        myFile.close();

        throw Exception("Fallo la insercion, readFromDisk");
        }

    myFile.close();
    }


/// ************************************************************************

template <class T>
void ListaGrafo<T>::deleteAll() {
    Position aux;
    while(headerPtr->getNext() != headerPtr) {
        aux = headerPtr->getNext();
        headerPtr->setNext(aux->getNext());
        delete aux;
        }

    headerPtr->setPrev(headerPtr);
    }

template <class T>
ListaGrafo<T>& ListaGrafo<T>::operator = (const ListaGrafo<T>& l) {
    deleteAll();
    copyAll(l);
    return *this;
    }

/// ************************

template <class T>
typename ListaGrafo<T>::Position ListaGrafo<T>::findData(const T& e, int cmp(const T&, const T&)) const {
    Position aux(headerPtr->getNext());
    while(aux != headerPtr and cmp(aux->getData(), e) != 0) {
        aux = aux->getNext();
        }

    return aux == headerPtr ? nullptr : aux;
    }

#endif // LIST_HPP_INCLUDED
