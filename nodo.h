#ifndef NODO_H
#define NODO_H

#include "objetoBase.h"

template <class T>
class nodo : public objetoBase{
public:
    nodo(nodo<T>*,T*);
    virtual ~nodo();
    virtual string toString();
    
/*SETTERS Y GETTERS*/
    virtual void setSig(nodo<T> *);
    virtual void setDato(T*);
    virtual nodo<T> * getSig();
    virtual T * getDato();
    
/*RETORNA LA CEDULA DE LA PERSONA*/
    //virtual string getCedula();
 
private:
    nodo<T> * siguiente;
    T * dato;
};
/*-----------------------------------------------------*/
template <class T>
nodo<T>::nodo(nodo<T>* sig,T* dato) : siguiente(sig), dato(dato){
}

template <class T>
nodo<T>::~nodo(){
}

template <class T>
string nodo<T>::toString(){
    stringstream x;
    
    x << *dato << endl;
    
    return x.str();
}

template <class T>
nodo<T> * nodo<T>::getSig(){
    return siguiente;
}

template <class T>
T * nodo<T>::getDato(){
    return dato;
}

template <class T> 
void nodo<T>::setSig(nodo<T> * sig){
    siguiente = sig;
}

template <class T> 
void nodo<T>::setDato(T* dato){
    this->dato = dato;
}


#endif /* NODO_H */

