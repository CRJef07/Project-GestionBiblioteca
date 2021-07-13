#include "materia.h"
#include "biblioteca.h"

//                                                                      BASICOS

materia::materia(string ident) : id(ident), _lista(new lista<libro>) {
}

materia::~materia() {
}

string materia::toString() {
    stringstream x;
    x << "\t\t\t\tMateria: " << id << "\n\n";
    x << _lista->toString();

    return x.str();
}

void materia::agregar(libro* nuevo) {
    _lista->agregar(nuevo);
}

void materia::eliminar(string viejo) {
    libro* lib = traerParaEliminar(viejo);
    _lista->eliminar(lib);
}

string materia::getIdent() {
    return id;
}

//                                                                       BUSCAR

bool materia::especificoM(string materia) {
    nodo<libro> * actual = _lista->getCabeza();
    

    while (actual != nullptr) {
        if (actual->getDato()->getMateria() == materia) {
            return true;
        }
        actual = actual->getSig();
    }
    return false;
}

bool materia::especificoA(string autor) {
    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getAutor() == autor) {
            return true;
        }
        actual = actual->getSig();
    }
    return false;
}

bool materia::especificoT(string titulo) {
    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo) {
            return true;
        }
        actual = actual->getSig();
    }
    return false;
}

libro* materia::traer(string titulo) {
    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo && actual->getDato()->getDisponibilidad() == true) {
            return actual->getDato();
        }
        actual = actual->getSig();
    }
    return nullptr;
}

libro* materia::traerParaEliminar(string titulo) {
    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo) {
            return actual->getDato();
        }
        actual = actual->getSig();
    }
    return nullptr;
}

string materia::imprimirEspecifico(string titulo) {
    nodo<libro> * actual = _lista->getCabeza();
    stringstream x;
    int i = 0;

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo && i < 1 && actual->getDato()->getDisponibilidad() == true && actual->getDato()->getNum() == 1) {
            x << actual->getDato()->toString();
            i++;
        }
        actual = actual->getSig();
    }
    return x.str();
}

//                                                                        LIBRO

void materia::darUnico(string codigo, string titulo, int i) {
    nodo<libro> * actual = _lista->getCabeza();

    stringstream x;
    if (i <= 9) {
        x << codigo << "0" << i;
    } else {
        x << codigo << i;
    }

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo && actual->getDato()->getNumU() == "") {
            actual->getDato()->setNumU(x.str());
        }
        actual = actual->getSig();
    }
}

void materia::CambiarDispoFalse(string titulo) {

    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getTitulo() == titulo && actual->getDato()->getDisponibilidad() == true) {
            actual->getDato()->setDisponibilidad(0);
            return;
        }
        actual = actual->getSig();
    }
}

bool materia::CambiarDispoTrue(string numero) {

    nodo<libro> * actual = _lista->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getNumU() == numero && actual->getDato()->getDisponibilidad() == false) {
            actual->getDato()->setDisponibilidad(1);
            return true;
        }
        actual = actual->getSig();
    }
    return false;
}

string materia::verDisponibles() {
    nodo<libro> * actual = _lista->getCabeza();
    stringstream x;
    
    while (actual != nullptr) {
        if (actual->getSig() == nullptr) {
            if (actual->getDato()->getDisponibilidad() == true) {
                x << actual->getDato()->toString();
            }
        } else {
            if (actual->getDato()->getTitulo() != actual->getSig()->getDato()->getTitulo() && actual->getDato()->getDisponibilidad() == true) {
                x << actual->getDato()->toString();
            }
        }
        actual = actual->getSig();
    }
    return x.str();
}

string materia::traerAutor(string aut) {
    stringstream x;
    nodo<libro> * actual = _lista->getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getAutor() == aut && actual->getDato()->getDisponibilidad() == true && actual->getDato()->getNum() == 1) {
            x << actual->getDato()->toString();
        }
        actual = actual->getSig();
    }
    return x.str();
}

//                                                                     ARCHIVOS

void materia::autoGuardar(ofstream &guardar) {
    guardar << id << endl;
}

materia & materia::autoCargar(ifstream & cargar) {
    string txtId;
    string vacio;
    fflush(stdin); //LIMPIAR BUFFER

    getline(cargar, txtId, ',');
    getline(cargar, vacio);


    return ( * new materia(txtId));
}