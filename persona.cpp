#include "persona.h"

/*CONSTRUCTOR SIN PARÁMETROS DE PERSONA*/
persona::persona() : nombre(""), cedula("") {
}

/*CONSTRUCTOR CON PARÁMETROS DE PERSONA*/
persona::persona(string nombre, string cedula) : nombre(nombre), cedula(cedula) {
}

/*DESTRUCTORDE PERSONA*/
persona::~persona() {
}

/*SETTERS Y GETTERS*/
void persona::setNombre(const string & nombre) {
    this->nombre = nombre;
}

void persona::setCedula(const string & cedula) {
    this->cedula = cedula;
}

/*El primer const de los métodos GET es para el valor. Garantiza que se va a retornar una referencia constante a un valor tipo STRING*/

/*El segundo const es para el método. Garantiza que no se puede modificar ningún atributo de la clase dentro del método*/
const string & persona::getNombre() const {
    return nombre;
}

const string & persona::getCedula() const {
    return cedula;
}

/*MÉTODO PARA IMPRIMIR EL ESTADO DEL OBJETO*/
string persona::toString() {
    stringstream x;

    x << "Nombre: " << nombre << endl;

    x << "Cedula: " << cedula << endl;

    return x.str();
}