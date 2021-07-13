#include "objetoBase.h"

/*CONSTRUCTOR DEL OBJETO BASE*/
objetoBase::objetoBase() {}

/*DESTRUCTOR DEL OBJETO BASE*/
objetoBase::~objetoBase() {}

/*SOBRECARDA DE OPERADORES, OPERADOR DE INSERCIÓN U OPERADOR DE SALIDA "<<" */
ostream& operator << (ostream& salida, objetoBase& o){
    salida << o.toString();
    return salida;
}