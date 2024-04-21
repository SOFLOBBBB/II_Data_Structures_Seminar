#ifndef STACK_HPP_INCLUDED
#define STACK_HPP_INCLUDED

#include <string>

/// Definition

template <class T>
class Stack {
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

    private:
        typedef Node* Position;

        class Node {
            private:
                T* dataPtr;
                Position next;

            public:
                class Exception : public Stack<T>::Exception {
                    public:
                        using Stack<T>::Exception::Exception;
                    };

                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr() const;
                T& getData();
                Position getNext() const;

                void setDataPtr(const T*&);
                void setData(const T&);
                void setNext(const Position&);
            };

        Position anchor;

        void copyAll(const Stack<T>&);

        void deleteAll();

    public:
        Stack();
        Stack(const Stack<T>&);

        ~Stack();

        void push(const T&);

        T pop();

        T& getTop();

        bool isEmpty() const;

        Stack<T>& operator = (const Stack<T>&);
    };

/// Implementation

/// Node

template <class T>
Stack<T>::Node::Node() : dataPtr(nullptr), next(nullptr) {}

template <class T>
Stack<T>::Node::Node(const T& e) : dataPtr(new T(e)), next(nullptr) {
    if(dataPtr  == nullptr) {
        throw Exception("Memoria no disponible, Node");
        }
    }

template <class T>
Stack<T>::Node::~Node() {
    delete dataPtr;
    }

template <class T>
T* Stack<T>::Node::getDataPtr() const {
    return dataPtr;
    }

template <class T>
T& Stack<T>::Node::getData() {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, getData");
        }

    return *dataPtr;
    }

template <class T>
typename Stack<T>::Position Stack<T>::Node::getNext() const {
    return next;
    }

template <class T>
void Stack<T>::Node::setDataPtr(const T*& p) {
    dataPtr = p;
    }

template <class T>
void Stack<T>::Node::setData(const T& e) {
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
void Stack<T>::Node::setNext(const Position& p) {
    next = p;
    }

/// Stack

/// Private

template <class T>
void Stack<T>::copyAll(const Stack<T>& s) {
    Position aux(s.anchor), newNode, lastInserted(nullptr);

    while(aux != nullptr) {
        try {
            if((newNode = new Node(aux->getData())) == nullptr) {
                throw Exception("Memoria no disponible, copyAll");
                }
            }
        catch(const typename Node::Exception& ex) {
            throw Exception("Memoria para nodo no disponible, copyAll");
            }

        if(lastInserted == nullptr) {
            anchor = newNode;
            }
        else {
            lastInserted->setNext(newNode);
            }

        lastInserted = newNode;

        aux = aux->getNext();
        }
    }

template <class T>
void Stack<T>::deleteAll() {
    Position aux;

    while(anchor != nullptr) {
        aux = anchor;
        anchor = anchor->getNext();
        delete aux;
        }
    }

/// Public

template <class T>
Stack<T>::Stack() : anchor(nullptr) {}

template <class T>
Stack<T>::Stack(const Stack<T>& s) : anchor(nullptr) {
    copyAll(s);
    }

template <class T>
Stack<T>::~Stack() {
    deleteAll();
    }

template <class T>
void Stack<T>::push(const T& e) {
    Position newNode;

    try {
        if((newNode = new Node(e)) == nullptr) {
            throw Exception("Memoria no disponible, push");
            }
        }
    catch(const typename Node::Exception& ex) {
        throw Exception("Memoria para nodo no disponible, push");
        }

    newNode->setNext(anchor);
    anchor = newNode;
    }

template <class T>
T Stack<T>::pop() {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, pop");
        }

    Position aux(anchor);
    T data(aux->getData());

    anchor = anchor->getNext();

    delete aux;

    return data;
    }

template <class T>
T& Stack<T>::getTop() {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, getTop");
        }

    return anchor->getData();
    }

template <class T>
bool Stack<T>::isEmpty() const {
    return anchor == nullptr;
    }

template <class T>
Stack<T>& Stack<T>::operator = (const Stack<T>& s) {
    deleteAll();
    copyAll(s);
    return *this;
    }

#endif // STACK_HPP_INCLUDED
