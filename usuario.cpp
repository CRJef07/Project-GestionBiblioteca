#include "usuario.h"

/*CONSTRUCTOR SIN PARÁMETROS DE USUARIO*/

usuario::usuario() : contra(""), cantLibros(0), vencidos(0), persona("", "") {
    for (int i = 0; i < 8; i++) {
        _VL[i] = new libro;
    }
}

usuario::usuario(string nombre, string cedula, string contra, int cantLibros, bool vencidos) : contra(contra), cantLibros(cantLibros), vencidos(vencidos), persona(nombre, cedula) {
    for (int i = 0; i < 8; i++) {
        _VL[i] = new libro;
    }
}

usuario::~usuario() {
}

void usuario::setContra(const string & contra) {
    this->contra = contra;
}

void usuario::setCantLibros(const int &cantLibros) {
    this->cantLibros = cantLibros;
}

void usuario::setVencidos(const bool &vencidos) {
    this->vencidos = vencidos;
}

const string &usuario::getContra()const {
    return contra;
}

const int &usuario::getCantLibros()const {
    return cantLibros;
}

const bool &usuario::getVencidos()const {
    return vencidos;
}

void usuario::agregarLibro(libro* n) {
    if (cantLibros < 8 && vencidos == false) {
        _VL[cantLibros] = n;
        cantLibros = cantLibros + 1;
    }
}

string usuario::imprimirLibros() {
    stringstream x;

    if (cantLibros > 0) {
        x << "\tLibros prestados:\n";
        for (int i = 0; i < cantLibros; i++) {
            x << i + 1 << ": " << *_VL[i];
        }
    } else {
        x << "Aun no ha solicitado ningun libro\n";
    }

    return x.str();
}

string usuario::imprimirEspecifico(int i) {
    stringstream x;

    x << _VL[i];

    return x.str();
}

void usuario::quitarLibro(string num) {
    for (int i = 0; i < 8; i++) {
        if (_VL[i]->getNumU() == num) {
            _VL[i] = new libro;
            reordenarVector();
            cantLibros -=1;
        }
    }
}

void usuario::reordenarVector() {

    for (int i = 0; i < 6; i++) {
        if (_VL[i]->getTitulo() == "" && _VL[i + 1]->getTitulo() != "") {

            _VL[i] = _VL[i + 1];
            _VL[i + 1] = _VL[i + 2];
            _VL[i + 2] = new libro;
        }
    }
}

/*
El método lo que hace es primero llamar al método toString() de la clase persona 
(método el cuál el usuario hereda)
Después ya imprime los valores del estado del objeto
Y por último llama al método imprimirLibros() el cual imprime los libros del usuario
 */
string usuario::toString() {
    stringstream x;

    x << persona::toString();

    x << "Su contraseña es: " << contra << endl;

    if (vencidos == true) {
        x << "El usuario tiene al menos 1 prestamo vencido :(" << endl;
    } else {
        x << "El usuario NO tiene prestamos vencidos :)" << endl;
    }

    x << imprimirLibros();

    return x.str();
}

void usuario::autoGuardar(ofstream& guardar) {
    guardar << getNombre() << ',';
    guardar << getCedula() << ',';
    guardar << contra << ',';
    guardar << cantLibros << ',';
    guardar << vencidos << endl;
}

//usuario(string nombre, string cedula, string contra, int cantLibros, bool vencidos)

usuario & usuario::autoCargar(ifstream & cargar) {
    string txtNombre, txtCedula, txtContra, txtCantLibros, txtVencidos;

    getline(cargar, txtNombre, ',');
    getline(cargar, txtCedula, ',');
    getline(cargar, txtContra, ',');

    getline(cargar, txtCantLibros, ',');
    int cantReal = convertirInt(txtCantLibros);

    getline(cargar, txtVencidos, '\n');
    int vencidosReal = convertirBolean(txtVencidos);

    return ( * new usuario(txtNombre, txtCedula, txtContra, cantReal, vencidosReal));
}

int usuario::convertirInt(string entero) {
    stringstream x(entero);

    int variableInt = -1;

    x >> variableInt;

    return variableInt;
}

bool usuario::convertirBolean(string bolean) {
    stringstream x(bolean);

    bool variableBool = 0;

    x >> variableBool;

    return variableBool;
}

