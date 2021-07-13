
#include "libro.h"
#include <sstream>
using std::stringstream;

libro::libro() : titulo(""), autor(""), materia(""), annoPublicacion(0), editorial(""), disponibilidad(0), numUnico("") {}

libro::libro(string titulo, string autor, string materia, int annoPublicacion, string editorial, int numLibro) : titulo(titulo), autor(autor), materia(materia), annoPublicacion(annoPublicacion), editorial(editorial), disponibilidad(1), numUnico(""), numLibro(numLibro) {}

libro::~libro() {}

string libro::getTitulo() {
    return titulo;
}

string libro::getAutor() {
    return autor;
}

string libro::getMateria() {
    return materia;
}

bool libro::getDisponibilidad() {
    return disponibilidad;
}

string libro::getNumU() {
    return numUnico;
}

void libro::setNumU(string num) {
    numUnico = num;
}

void libro::setDisponibilidad(bool dis) {
    disponibilidad = dis;
}

int libro::getNum(){
    return numLibro;
}

string libro::toString() {
    stringstream x;
    x << "El titulo de la obra es: " << titulo << "\n";
    x << "El autor de la obra es: " << autor << "\n";
    x << "La materia a la que pertenece la obra es: " << materia << "\n";
    x << "El anno de publicacion de la obra es: " << annoPublicacion << "\n";
    x << "La editorial al que pertenece la obra es: " << editorial << "\n";
    x << "El codigo es: " << numUnico << "\n";
    if (disponibilidad == true) {
        x << "El libro se encuentra disponible\n\n";
    } else {
        x << "El libro no esta disponible\n\n";
    }
    return x.str();
}
