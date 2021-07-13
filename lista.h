#ifndef LISTA_H
#define LISTA_H

#include <fstream>
using std::ofstream;
using std::ifstream;

#include "nodo.h"

template <class T>
class lista {
public:
    lista();
    virtual ~lista();
    virtual nodo<T> * getCabeza();
    virtual void agregar(T*);
    virtual bool eliminar(T*);
    virtual string toString();

    void cargar(string);
    void guardar(string);
private:
    nodo<T> *cabeza;
};

/*------------------------------------------------*/
template <class T>
lista<T>::lista() : cabeza(nullptr) {
}

template <class T>
lista<T>::~lista() {
    nodo<T>* borrar = cabeza;
    nodo<T> * temp;

    while (borrar != nullptr) {
        temp = borrar;
        borrar = borrar->getSig();
        delete temp;
    }
}

template <class T>
nodo<T> * lista<T>::getCabeza() {
    return cabeza;
}

template <class T>
void lista<T>::agregar(T* dato) {
    cabeza = new nodo<T>(cabeza, dato);
}

template <class T>
bool lista<T>::eliminar(T* dato) {
    nodo<T> * borrar = cabeza;
    nodo<T> * anterior = nullptr;

    bool tempBorrado = false;

    if (borrar == nullptr) {
        return false;
    }
    if (borrar->getDato() == dato) {
        cabeza = borrar->getSig();
        delete borrar;
        tempBorrado = true;
    } else {
        while ((borrar != nullptr) && (borrar->getDato() != dato)) {
            anterior = borrar;
            borrar = borrar->getSig();
        }
        if (borrar == nullptr) {
            tempBorrado = false;
        } else {
            anterior->setSig(borrar->getSig());
            delete borrar;
            tempBorrado = true;
        }
    }
    return tempBorrado;
}

template <class T>
string lista<T>::toString() {
    stringstream x;

    nodo<T>* temp = cabeza;
    if (temp == nullptr) {
        x << "No hay datos en la lista, esta vacia\n";
        return x.str();
    }
    if (temp->getSig() == nullptr) {
        temp->getDato();
        x << *temp->getDato() << endl;
        return x.str();
    } else {
        while (temp != nullptr) {
            x << *temp->getDato() << endl;
            temp = temp->getSig();
        }
    }

    /*while (temp != nullptr) {
        x << *temp->getDato() << endl;
        
        temp = temp->getSig();
    }*/

    return x.str();
}

//*****************************

template <class T>
void lista<T>::cargar(string file) {
    T line;
    ifstream in;

    in.open(file.c_str());

    if (!in.is_open()) {//USAR ERRORES Y FIN ARCHIVO ARCHIVO.GOOD
        std::cerr << "No se puede abrir el archivo: " << file << endl << endl;
    } else {
        while (in >> line) {
            agregar(line);
        }
    }
    in.close();
}

template <class T>
void lista<T>::guardar(string file) {
    nodo<T> * actual = cabeza;

    ofstream out;
    out.open(file.c_str());

    if (!out.is_open()) {
        cout << "No se puede guardar el archivo " << endl;
    } else {
        while (actual) {
            out << *actual->getDato();
            actual = actual->getSig();
        }
    }
    out.close();
}

#endif /* LISTA_H */

