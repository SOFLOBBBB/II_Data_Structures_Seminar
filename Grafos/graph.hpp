#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "list.hpp"
#include "queue.hpp"
#include "stack.hpp"

template <class T>
class Graph {
        class NodeEdge;
        class NodeVertex;

    public:
        typedef NodeEdge* EdgePos;
        typedef NodeVertex* VertexPos;

    private:
        class NodeVertex {
            private:
                friend class Graph;

                T* data;
                VertexPos prevVertex;
                VertexPos nextVertex;
                EdgePos headerEdge;

                int edgeCount;

            public:
                NodeVertex() : data(nullptr), prevVertex(nullptr), nextVertex(nullptr), headerEdge(new NodeEdge), edgeCount(0) {
                    headerEdge->prevEdge = headerEdge->nextEdge = headerEdge;
                    }
                NodeVertex(const T& d) : data(new T(d)), prevVertex(nullptr), nextVertex(nullptr), headerEdge(new NodeEdge), edgeCount(0) {
                    headerEdge->prevEdge = headerEdge->nextEdge = headerEdge;
                    }
                NodeVertex(const T& d, const int& c) : data(new T(d)), prevVertex(nullptr), nextVertex(nullptr), headerEdge(new NodeEdge), edgeCount(c) {
                    headerEdge->prevEdge = headerEdge->nextEdge = headerEdge;
                    }
                ~NodeVertex() {
                    delete data;
                    delete headerEdge;
                    }
            };

        class NodeEdge {
            private:
                friend class Graph;

                int weight;
                VertexPos destination;
                EdgePos prevEdge;
                EdgePos nextEdge;

            public:
                NodeEdge() : weight(1), destination(nullptr), prevEdge(nullptr), nextEdge(nullptr) {}
                NodeEdge(VertexPos d, const int& w) : weight(w), destination(d), prevEdge(nullptr), nextEdge(nullptr) {}
            };

        class PairOrigDest {
            private:
                friend class Graph;

                VertexPos orig;
                VertexPos dest;
                int weight;

            public:
                PairOrigDest();
                PairOrigDest(const PairOrigDest& p) : orig(p.orig), dest(p.dest), weight(p.weight) { }
                PairOrigDest(VertexPos o, VertexPos d, const int& w) : orig(o), dest(d), weight(w) { }
                PairOrigDest& operator = (const PairOrigDest& p) {
                    orig = p.orig;
                    dest = p.dest;
                    weight = p.weight;
                    }
            };

        int vertCount;

        VertexPos headerVertex;

        void copyAll(const Graph&);

        bool thereIsEdge(VertexPos, VertexPos) const;

        std::string pairStackToString(VertexPos, Stack<PairOrigDest>&);
    public:
        Graph();
        Graph(const Graph&);

        ~Graph();

        Graph& operator = (const Graph&);

        std::string toString() const;

        bool isEmpty() const;

        void insertVertex(const T&);
        void deleteVertex(const T&);

        VertexPos findVertex(const T&);
        EdgePos findEdge(const T&, const T&);

        void insertEdge(const T&, const T&, const int& w = 1);
        void deleteEdge(const T&, const T&);

        void deleteAll();

        bool saveData(const std::string&) const;
        bool loadData(const std::string&);

        std::string breadthFirstSearch(const T&, const T&);
        std::string depthFirstSearch(const T&, const T&);
    };



template <class T>
void Graph<T>::copyAll(const Graph& g) {
    VertexPos auxVert(g.headerVertex->nextVertex), newVertex, auxDest, thisOrig;
    EdgePos auxEdge, newEdge;

    /// Copiar Vertices
    while(auxVert != g.headerVertex) {
        newVertex = new NodeVertex(*(auxVert->data));

        newVertex->prevVertex = headerVertex->prevVertex;
        newVertex->nextVertex = headerVertex;

        headerVertex->prevVertex = headerVertex->prevVertex->nextVertex = newVertex;

        auxVert = auxVert->nextVertex;
        }

    /// Copiar Aristas
    auxVert = g.headerVertex->nextVertex;
    thisOrig = headerVertex->nextVertex;
    while(auxVert != g.headerVertex) {
        auxEdge = auxVert->headerEdge->nextEdge;

        while(auxEdge != auxVert->headerEdge) {
            auxDest = findVertex(*(auxEdge->destination->data));

            newEdge = new NodeEdge(auxDest, auxEdge->weight);

            newEdge->prevEdge = thisOrig->headerEdge->prevEdge;
            newEdge->nextEdge = thisOrig->headerEdge;

            thisOrig->headerEdge->prevEdge = thisOrig->headerEdge->prevEdge->nextEdge = newEdge;

            auxEdge = auxEdge->nextEdge;
            }

        thisOrig = thisOrig->nextVertex;
        auxVert = auxVert->nextVertex;
        }
    }

template <class T>
bool Graph<T>::thereIsEdge(VertexPos origPos, VertexPos destPos) const {
    EdgePos auxEdge(origPos->headerEdge->nextEdge);
    while(auxEdge != origPos->headerEdge) {
        if(auxEdge->destination == destPos) {
            return true;
            }

        auxEdge = auxEdge->nextEdge;
        }

    return false;
    }

template <class T>
std::string Graph<T>::pairStackToString(VertexPos dest, Stack<PairOrigDest>& pairStack) {
    VertexPos currentDest(dest);
    std::stringstream ss;
    int cost(0);
    while(!pairStack.isEmpty()) {
        ss << "(" << currentDest->data->toString();

        while(!pairStack.isEmpty() and pairStack.getTop().dest != currentDest) {
            pairStack.pop();
            }

        if(!pairStack.isEmpty()) {
            currentDest = pairStack.getTop().orig;
            cost+= pairStack.getTop().weight;
            ss << ":" << pairStack.getTop().weight << ")" << "<-";
            }
        }

    ss << ") Costo Total: " << cost;

    return ss.str();
    }

template <class T>
Graph<T>::Graph() : headerVertex(new NodeVertex), vertCount(0) {
    headerVertex->prevVertex = headerVertex->nextVertex = headerVertex;
    }

template <class T>
Graph<T>::Graph(const Graph& g) : Graph() {
    copyAll(g);
    }

template <class T>
Graph<T>::~Graph() {
    deleteAll();
    delete headerVertex;
    }

template <class T>
Graph<T>& Graph<T>::operator = (const Graph& g) {
    deleteAll();
    copyAll(g);
    return *this;
    }

template <class T>
std::string Graph<T>::toString() const {
    std::stringstream ss;
    VertexPos auxVert(headerVertex->nextVertex);
    EdgePos auxEdge;

    while(auxVert != headerVertex) {
        auxEdge = auxVert->headerEdge->nextEdge;
        ss << "[" << auxVert->data->toString() << "]" << char(16);
        while(auxEdge != auxVert->headerEdge) {
            ss << "->(" << auxEdge->destination->data->toString() << ":" << auxEdge->weight << ")";
            auxEdge = auxEdge->nextEdge;
            }
        ss << std::endl;
        auxVert = auxVert->nextVertex;
        }

    return ss.str();
    }

template <class T>
bool Graph<T>::isEmpty() const {
    return headerVertex->nextVertex == headerVertex;
    }

template <class T>
void Graph<T>::insertVertex(const T& v) {
    if(findVertex(v) != nullptr) {
        return;
        }

    VertexPos newVertex(new NodeVertex(v));

    newVertex->prevVertex = headerVertex->prevVertex;
    newVertex->nextVertex = headerVertex;

    headerVertex->prevVertex = headerVertex->prevVertex->nextVertex = newVertex;

    vertCount++;
    }

template <class T>
void Graph<T>::deleteVertex(const T& v) {
    VertexPos vertex(findVertex(v));
    if(vertex == nullptr) {
        return;
        }

    /// Liberar aristas hacia v
    VertexPos auxVert(headerVertex->nextVertex);
    EdgePos auxEdge, tmp;
    while(auxVert != headerVertex) {
        auxEdge = auxVert->headerEdge->nextEdge;

        while(auxEdge != auxVert->headerEdge) {
            if(auxEdge->destination == vertex) {
                tmp = auxEdge;
                auxEdge->prevEdge->nextEdge = auxEdge->nextEdge;
                auxEdge->nextEdge->prevEdge = auxEdge->prevEdge;
                delete tmp;
                auxVert->edgeCount--;
                }

            auxEdge = auxEdge->nextEdge;
            }

        auxVert = auxVert->nextVertex;
        }

    /// Liberar aristas desde v
    while(vertex->headerEdge->nextEdge != vertex->headerEdge) {
        auxEdge = vertex->headerEdge->nextEdge;
        vertex->headerEdge->nextEdge = auxEdge->nextEdge;
        delete auxEdge;
        }

    /// Liberar v
    vertex->prevVertex->nextVertex = vertex->nextVertex;
    vertex->nextVertex->prevVertex = vertex->prevVertex;

    delete vertex;
    vertCount--;
    }

template <class T>
typename Graph<T>::VertexPos Graph<T>::findVertex(const T& v) {
    VertexPos aux(headerVertex->nextVertex);

    while(aux != headerVertex) {
        if(*(aux->data) == v) {
            return aux;
            }

        aux = aux->nextVertex;
        }

    return nullptr;
    }

template <class T>
typename Graph<T>::EdgePos Graph<T>::findEdge(const T& o, const T& d) {
    VertexPos origPos(findVertex(o));
    VertexPos destPos(findVertex(d));

    if(origPos == nullptr or destPos == nullptr) {
        return nullptr;
        }

    EdgePos auxEdge(origPos->headerEdge->nextEdge);
    while(auxEdge != origPos->headerEdge) {
        if(auxEdge->destination == destPos) {
            return auxEdge;
            }

        auxEdge = auxEdge->nextEdge;
        }

    return nullptr;
    }

template <class T>
void Graph<T>::insertEdge(const T& o, const T& d, const int& w) {
    VertexPos origPos(findVertex(o));
    VertexPos destPos(findVertex(d));

    if(origPos == nullptr or destPos == nullptr) {
        return;
        }

    if(thereIsEdge(origPos, destPos)) {
        return;
        }

    EdgePos newEdge(new NodeEdge(destPos, w));

    newEdge->prevEdge = origPos->headerEdge->prevEdge;
    newEdge->nextEdge = origPos->headerEdge;

    origPos->headerEdge->prevEdge = origPos->headerEdge->prevEdge->nextEdge = newEdge;

    origPos->edgeCount++;
    }

template <class T>
void Graph<T>::deleteEdge(const T& o, const T& d) {
    VertexPos origPos(findVertex(o));
    VertexPos destPos(findVertex(d));

    if(origPos == nullptr or destPos == nullptr) {
        return;
        }

    EdgePos edgePos(origPos->headerEdge->nextEdge);
    while(edgePos != origPos->headerEdge and edgePos->destination != destPos) {
        edgePos = edgePos->nextEdge;
        }

    if(edgePos == origPos->headerEdge) {
        return;
        }

    edgePos->prevEdge->nextEdge = edgePos->nextEdge;
    edgePos->nextEdge->prevEdge = edgePos->prevEdge;

    delete edgePos;
    origPos->edgeCount--;
    }

template <class T>
void Graph<T>::deleteAll() {
    VertexPos auxVert;
    EdgePos auxEdge;

    while(headerVertex->nextVertex != headerVertex) {
        auxVert = headerVertex->nextVertex;

        while(auxVert->headerEdge->nextEdge != auxVert->headerEdge) {
            auxEdge = auxVert->headerEdge->nextEdge;
            auxVert->headerEdge->nextEdge = auxEdge->nextEdge;
            delete auxEdge;
            }

        headerVertex->nextVertex = auxVert->nextVertex;
        delete auxVert;
        }

    headerVertex->prevVertex = headerVertex;
    vertCount = 0;
    }

template <class T>
bool Graph<T>::saveData(const std::string& fileName) const {
    std::ofstream myFile(fileName, std::ios_base::trunc);

    if(!myFile.is_open()) {
        return false;
        }

    myFile << vertCount << std::endl;

    /// Guardar Vertices
    VertexPos auxVert(headerVertex->nextVertex);
    for(int i(0); i < vertCount; i++) {
        myFile << *(auxVert->data);
        myFile << auxVert->edgeCount << std::endl;
        auxVert = auxVert->nextVertex;
        }

    /// Guardar Aristas
    EdgePos auxEdge;
    auxVert = headerVertex->nextVertex;
    while(auxVert != headerVertex) {
        auxEdge = auxVert->headerEdge->nextEdge;

        for(int i(0); i < auxVert->edgeCount; i++) {
            myFile << *(auxEdge->destination->data);
            myFile << auxEdge->weight << std::endl;
            auxEdge = auxEdge->nextEdge;
            }

        auxVert = auxVert->nextVertex;
        }


    myFile.close();

    return true;
    }

template <class T>
bool Graph<T>::loadData(const std::string& fileName) {
    std::ifstream myFile(fileName);
    std::string myStr;
    VertexPos newVertex, destPos, origPos;
    EdgePos newEdge;
    T data;

    if(!myFile.is_open()) {
        return false;
        }

    deleteAll();

    /// Recuperar Vertices
    getline(myFile, myStr);
    vertCount = std::atoi(myStr.c_str());
    for(int i(0); i < vertCount; i++) {
        myFile >> data;
        getline(myFile, myStr);

        newVertex = new NodeVertex(data, std::atoi(myStr.c_str()));

        newVertex->prevVertex = headerVertex->prevVertex;
        newVertex->nextVertex = headerVertex;

        headerVertex->prevVertex = headerVertex->prevVertex->nextVertex = newVertex;
        }

    /// Recuperar Aristas
    origPos = headerVertex->nextVertex;
    while(origPos != headerVertex) {
        for(int i(0); i < origPos->edgeCount; i++) {
            myFile >> data;
            getline(myFile, myStr);

            destPos = findVertex(data);

            newEdge = new NodeEdge(destPos, std::atoi(myStr.c_str()));

            newEdge->prevEdge = origPos->headerEdge->prevEdge;
            newEdge->nextEdge = origPos->headerEdge;

            origPos->headerEdge->prevEdge = origPos->headerEdge->prevEdge->nextEdge = newEdge;
            }

        origPos = origPos->nextVertex;
        }


    myFile.close();
    return true;
    }

template <class T>
std::string Graph<T>::breadthFirstSearch(const T& o, const T& d) {
    VertexPos origPos(findVertex(o));
    VertexPos destPos(findVertex(d));

    if(origPos == nullptr or destPos == nullptr) {
        return "";
        }

    ListaGrafo<VertexPos> visitedList;
    Queue<VertexPos> vertexQueue;
    Stack<PairOrigDest> pairStack;

    VertexPos currentVert;
    EdgePos auxDest;

    vertexQueue.enqueue(origPos);
    while(!vertexQueue.isEmpty()) {
        currentVert = vertexQueue.dequeue();

        if(visitedList.findData(currentVert) == nullptr) {
            if(currentVert == destPos) {
                return pairStackToString(destPos, pairStack);
                }

            visitedList.insertData(visitedList.getLastPos(), currentVert);

            auxDest = currentVert->headerEdge->nextEdge;
            while(auxDest != currentVert->headerEdge) {
                if(visitedList.findData(auxDest->destination) == nullptr) {
                    vertexQueue.enqueue(auxDest->destination);
                    pairStack.push(PairOrigDest(currentVert, auxDest->destination, auxDest->weight));
                    }

                auxDest = auxDest->nextEdge;
                }

            }
        }

    return "";
    }

template <class T>
std::string Graph<T>::depthFirstSearch(const T& o, const T& d) {
    VertexPos origPos(findVertex(o));
    VertexPos destPos(findVertex(d));

    if(origPos == nullptr or destPos == nullptr) {
        return "";
        }

    ListaGrafo<VertexPos> visitedList;
    Stack<VertexPos> vertexStack;
    Stack<PairOrigDest> pairStack;

    VertexPos currentVert;
    EdgePos auxDest;

    vertexStack.push(origPos);
    while(!vertexStack.isEmpty()) {
        currentVert = vertexStack.pop();

        if(visitedList.findData(currentVert) == nullptr) {
            if(currentVert == destPos) {
                return pairStackToString(destPos, pairStack);
                }

            visitedList.insertData(visitedList.getLastPos(), currentVert);

            auxDest = currentVert->headerEdge->nextEdge;
            while(auxDest != currentVert->headerEdge) {
                if(visitedList.findData(auxDest->destination) == nullptr) {
                    vertexStack.push(auxDest->destination);
                    pairStack.push(PairOrigDest(currentVert, auxDest->destination, auxDest->weight));
                    }

                auxDest = auxDest->nextEdge;
                }

            }
        }

    return "";
    }



#endif // GRAPH_HPP_INCLUDED
