#ifndef QUEUE_HPP_INCLUDED
#define QUEUE_HPP_INCLUDED

#include <string>

/// Definition

template <class T>
class Queue {
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

                Position prev;
                Position next;

            public:
                class Exception : public Queue<T>::Exception {
                    public:
                        using Queue<T>::Exception::Exception;
                    };

                Node();
                Node(const T&);

                ~Node();

                T* getDataPtr();
                T& getData();
                Position getPrev() const;
                Position getNext() const;

                void setDataPtr(const T*&);
                void setData(const T&);
                void setPrev(const Position&);
                void setNext(const Position&);
            };

        Position headerPtr;

        void copyAll(const Queue<T>&);
        void deleteAll();

    public:
        Queue();
        Queue(const Queue<T>&);

        ~Queue();

        bool isEmpty() const;

        void enqueue(const T&);
        T dequeue();

        T& getFront();

        Queue<T>& operator = (const Queue<T>&);
    };

/// Implementation

/// Node

template<class T>
Queue<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

template<class T>
Queue<T>::Node::Node(const T& e) : dataPtr(new T(e)), prev(nullptr), next(nullptr) {
    if(dataPtr == nullptr) {
        throw Exception("Memoria no disponible, Node");
        }
    }

template<class T>
Queue<T>::Node::~Node() {
    delete dataPtr;
    }

template<class T>
T* Queue<T>::Node::getDataPtr() {
    return dataPtr;
    }

template<class T>
T& Queue<T>::Node::getData() {
    if(dataPtr == nullptr) {
        throw Exception("Dato inexistente, getData");
        }

    return *dataPtr;
    }

template<class T>
typename Queue<T>::Position Queue<T>::Node::getPrev() const {
    return prev;
    }

template<class T>
typename Queue<T>::Position Queue<T>::Node::getNext() const {
    return next;
    }

template<class T>
void Queue<T>::Node::setDataPtr(const T*& p) {
    dataPtr = p;
    }

template<class T>
void Queue<T>::Node::setData(const T& e) {
    if(dataPtr == nullptr) {
        if((dataPtr = new T(e)) == nullptr) {
            throw Exception("Memoria no disponible, setData");
            }
        }
    else {
        *dataPtr = e;
        }
    }

template<class T>
void Queue<T>::Node::setPrev(const Position& p) {
    prev = p;
    }

template<class T>
void Queue<T>::Node::setNext(const Position& p) {
    next = p;
    }

/// Queue

/// Private

template<class T>
void Queue<T>::copyAll(const Queue<T>& q) {
    Position aux(q.headerPtr->getNext()), newNode;
    while(aux != q.headerPtr) {
        try {
            if((newNode = new Node(aux->getData())) == nullptr) {
                throw Exception("Memoria no disponible, copyAll");
                }
            }
        catch(const typename Node::Exception& ex) {
            throw Exception("Memoria para nodo no disponible, copyAll");
            }

        newNode->setPrev(headerPtr->getPrev());
        newNode->setNext(headerPtr);

        headerPtr->getPrev()->setNext(newNode);
        headerPtr->setPrev(newNode);

        aux = aux->getNext();
        }
    }

template<class T>
void Queue<T>::deleteAll() {
    Position aux;
    while(headerPtr->getNext() != headerPtr) {
        aux = headerPtr->getNext();
        headerPtr->setNext(aux->getNext());
        delete aux;
        }

    headerPtr->setPrev(headerPtr);
    }

/// Public

template<class T>
Queue<T>::Queue() : headerPtr(new Node) {
    if(headerPtr == nullptr) {
        throw Exception("Memoria no disponible, Queue");
        }

    headerPtr->setPrev(headerPtr);
    headerPtr->setNext(headerPtr);
    }

template<class T>
Queue<T>::Queue(const Queue<T>& q) : Queue() {
    copyAll(q);
    }

template<class T>
Queue<T>::~Queue() {
    deleteAll();
    delete headerPtr;
    }

template<class T>
bool Queue<T>::isEmpty() const {
    return headerPtr->getNext() == headerPtr;
    }

template<class T>
void Queue<T>::enqueue(const T& e) {
    Position newNode;
    try {
        if((newNode = new Node(e)) == nullptr) {
            throw Exception("Memoria no disponible, enqueue");
            }
    }catch(const typename Node::Exception& ex) {
        throw Exception("Memoria para nodo no disponible, enqueue");
        }

    newNode->setPrev(headerPtr->getPrev());
    newNode->setNext(headerPtr);

    headerPtr->getPrev()->setNext(newNode);
    headerPtr->setPrev(newNode);
    }

template<class T>
T Queue<T>::dequeue() {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, dequeue");
        }

    Position aux(headerPtr->getNext());
    T data(aux->getData());

    aux->getPrev()->setNext(aux->getNext());
    aux->getNext()->setPrev(aux->getPrev());

    delete aux;

    return data;
    }

template<class T>
T& Queue<T>::getFront() {
    if(isEmpty()) {
        throw Exception("Insuficiencia de datos, getFront");
        }

    return headerPtr->getNext()->getData();
    }

template<class T>
Queue<T>& Queue<T>::operator = (const Queue<T>& q) {
    deleteAll();
    copyAll(q);
    return *this;
    }


#endif // QUEUE_HPP_INCLUDED
