#ifndef PERSONA_H
#define PERSONA_H

#include "objetoBase.h"

/*LA CLASE PERSONA HEREDA LOS MÉTODOS PÚBLICOS DE LA CLASE OBJETOBASE*/

/*POR LO QUE, HAY UNA HERENCIA, PERO TAMBIÉN HAY UNA ASOCIACIÓN*/
class persona : public objetoBase {
public:
    /*CONSTRUCTOR SIN PARÁMETROS DE PERSONA*/
    persona();

    /*CONSTRUCTOR CON PARÁMETROS DE PERSONA*/
    persona(string nombre, string cedula);

    /*DESTRUCTORDE PERSONA*/
    virtual ~persona();

    /*SETTERS Y GETTERS*/
    virtual void setNombre(const string &);
    virtual void setCedula(const string &);

    /*El primer const de los métodos GET es para el valor. Garantiza que se va a retornar una referencia constante a un valor tipo STRING*/
    /*El segundo const es para el método. Garantiza que no se puede modificar ningún atributo de la clase dentro del método*/
    virtual const string &getNombre() const;
    virtual const string &getCedula() const;

    /*MÉTODO PARA IMPRIMIR EL ESTADO DEL OBJETO*/
    virtual string toString();

private:
    string nombre;
    string cedula;
};

#endif /* PERSONA_H */

