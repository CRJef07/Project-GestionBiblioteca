#ifndef OBJETOBASE_H
#define OBJETOBASE_H

#include <iostream>
using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::getline;

#include <sstream>
using std::stringstream;



class objetoBase {
public:
    /*CONSTRUCTOR DEL OBJETO BASE*/
    objetoBase();

    /*DESTRUCTOR DEL OBJETO BASE*/
    virtual ~objetoBase();

    /*MÉTODO PARA IMPRIMIR - ES UN MÉTODO VIRTUAL PURO (SOLO SE DECLARA EN EL .H Y SE DEFINE EN LAS CLASES EN LAS QUE SE VAYA A USAR)*/
    virtual string toString() = 0;
};
/*SOBRECARDA DE OPERADORES, OPERADOR DE INSERCIÓN U OPERADOR DE SALIDA "<<" */
ostream& operator<<(ostream&, objetoBase&);

#endif /* OBJETOBASE_H */

