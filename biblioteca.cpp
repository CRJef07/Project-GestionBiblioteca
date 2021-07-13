#include "biblioteca.h"

biblioteca::biblioteca() : _LM(new lista<materia>), _LU(new lista<usuario>), numLIbro(0) {

}

biblioteca::~biblioteca() {
    delete _LM;
    delete _LU;
}

//                                                                MENU

void biblioteca::menuPrincipal() {
    leerUsuarios();
    leerMaterias();

    string opc = "";

    do {
        fflush(stdin); //LIMPIAR BUFFER 
        system("clear");

        cout << "\t\t\tBienvenido a la biblioteca querido usuario\n";
        cout << "Digite la opcion que desee ejecutar\n";
        cout << " 1 - MENU ADMINISTRATIVO \n";
        cout << " 2 - REGISTRARSE \n";
        cout << " 3 - INICIAR SESION \n";
        cout << "77 - SALIR \n";
        cout << "Opcion:  ";
        getline(cin, opc);

        try {
            if (opc != "1" && opc != "2" && opc != "3" && opc != "77") {
                throw opc;
            }
            switch (std::stoi(opc)) {
                case 1:
                    menuBibliotecario();
                    break;

                case 2:
                    registrarUsuario();
                    break;

                case 3:
                    inicioSesion();
                    break;
            }
        } catch (string opc) {
        }
    } while (opc != "77");
}

void biblioteca::menuUsuario(string id, string nom) {
    string opc = "";
    string opc2 = "";
    do {
        fflush(stdin); //LIMPIAR BUFFER 
        system("clear");

        cout << "Bienvenido a la biblioteca usuario " << nom << endl;
        cout << "Digite la opcion que desee ejecutar\n";
        cout << "1 - Solicitar un libro \n";
        cout << "2 - Buscar un libro en especifico \n";
        cout << "3 - Ver libros solicitados \n";
        cout << "4 - Devolver un libro\n";
        cout << "77 - SALIR \n";
        cout << "Opcion:  ";
        std::getline(std::cin, opc);

        try {
            if (opc != "1" && opc != "2" && opc != "3" && opc != "4" && opc != "77") {
                throw opc;
            }
            switch (stoi(opc)) {
                case 1:
                    solicitarLibro(id);
                    cin.get();
                    break;

                case 2:
                    buscarLibros();
                    cin.get();
                    break;

                case 3:
                    cout << imprimirSolicitados(id) << endl;
                    cin.get();
                    break;
                case 4:
                    devolverLibro(id);
                    break;
            }
        } catch (string opc) {

        }
    } while (opc != "77");


}

void biblioteca::menuBibliotecario() {
    string opc = "";

    do {
        fflush(stdin); //LIMPIAR BUFFER 
        system("clear");

        cout << "Bienvenido bibliotecario\n";
        cout << "Digite la opcion que desee ejecutar\n";
        cout << "1 - AGREGAR UN LIBRO \n";
        cout << "2 - AGREGAR UNA MATERIA NUEVA \n";
        cout << "3 - VER LA LISTA DE MATERIAS Y LIBROS \n";
        cout << "4 - VER LA LISTA USUARIOS \n";
        cout << "5 - ELIMINAR UN LIBRO \n";
        cout << "6 - ELIMINAR UNA MATERIA\n";
        cout << "7 - ELIMINAR UN USUARIO\n";
        cout << "77 - SALIR \n";
        cout << "Opcion:  ";

        getline(cin, opc);

        try {
            if (opc != "1" && opc != "2" && opc != "3" && opc != "4" && opc != "5" && opc != "77" && opc != "6" && opc != "7") {
                throw opc;
            }
            switch (stoi(opc)) {
                case 1:
                    agregarLibro();
                    break;

                case 2:
                    agregarMateria();
                    break;

                case 3:

                    cout << endl << _LM->toString() << endl;
                    cin.get();
                    break;

                case 4:

                    cout << endl << _LU->toString() << endl;
                    cin.get();
                    break;

                case 5:

                    eliminarLibro();
                    break;

                case 6:

                    eliminarMateria();
                    break;

                case 7:

                    eliminarUsuario();
                    break;
            }
        } catch (string opc) {
        }
    } while (opc != "77");
}
//EL USUARIO REGISTRADO EN EL SISTEMA ACCEDE A SUS ACCIONES POSIBLES PASANDO POR ESTE
//METODO

void biblioteca::inicioSesion() {
    fflush(stdin); //LIMPIAR BUFFER 
    system("clear");

    nodo<usuario>* actual = _LU->getCabeza();
    string ident = "";
    string contra = "";
    string nombre = "";

    cout << "Digite su numero de identificacion\n";
    getline(cin, ident);

    cout << "Digite su contraseña\n";
    getline(cin, contra);

    while (actual != nullptr) {
        if (actual->getDato()->getCedula() == ident && actual->getDato()->getContra() == contra) {
            nombre = actual->getDato()->getNombre();
            menuUsuario(ident, nombre);
            return;
        }
        actual = actual->getSig();
    }
    if (actual == nullptr) {
        cout << "Credenciales incorrectas\n";
    }

    cin.get();
}

//                                                                     PRESTAMO                                         

/*REALIZA LA SOLICITACION DE UN LIBRO Y REVISA SI SE NECESITA QUE SE DIGITE 
 LA MATERIA DEL LIBRO O NO*/
void biblioteca::solicitarLibro(string id) {
    string libro = "";
    string materiaB = "";
    string numUnico = "";
    nodo<materia> *actualM = _LM->getCabeza();
    fflush(stdin); //LIMPIAR BUFFER 

    if (verificarPrestamo(id) == true) {//VERIFICA SI EL USUARIO PUEDE OPTAR POR UN PRÉSTAMO
        cout << "\t\tIngrese el titulo del libro que desea buscar y solicitar: \n";
        std::getline(std::cin, libro);



        if ((actualM = buscarT2(libro)) != nullptr) {

            if (buscarRepetido(libro) == false) {

                realizarPrestamo(id, libro);
                return;
            } else {
                fflush(stdin); //LIMPIAR BUFFER 

                cout << imprimirTitulo(libro) << endl;
                cout << "Si desea solicitar uno de los libros, por favor ingrese la materia correspondiente" << endl;
                cout << "Caso contrario digite la tecla 'ENTER' \n";
                cout << "Opcion digitada:  ";
                std::getline(std::cin, materiaB);

                realizarPrestamoRepetido(id, libro, materiaB);
                return;
            }

        } else {
            cout << "\tEl libro ingresado NO se encuentra en la base de datos\n";
        }
    } else {
        cout << "NO CUMPLE CON LOS REQUISITOS PARA OBTENER UN PRESTAMO" << endl;
    }
}

/*CONCRETA EL PRESTAMO DE UN LIBRO QUE SU TITULO ES UNICO EN
 TODO EL SISTEMA*/
void biblioteca::realizarPrestamo(string id, string libroNuevo) {
    nodo<usuario> *actualU = _LU->getCabeza();
    nodo<materia> *actualM;
    string matId = "";
    libro* lib;


    if ((actualM = buscarT2(libroNuevo)) != nullptr) {

        matId = actualM->getDato()->getIdent();

        while (actualU != nullptr) {

            if (actualU->getDato()->getCedula() == id) {

                lib = traerlibro(actualM, libroNuevo);

                actualU->getDato()->agregarLibro(lib);

                cambiarDisponibilidadFalse(libroNuevo, matId);

                cout << "\tPRESTAMO REALIZADO CON EXITO\n";
            }
            actualU = actualU->getSig();
        }


    }
}

/*CONCRETA EL PRESTAMO DE UN LIBRO UTILIZANDO EL TITULO Y LA MATERIA
 YA QUE HAY OTROS CON EL MISMO TITULO*/
void biblioteca::realizarPrestamoRepetido(string id, string libroNuevo, string matId) {
    nodo<usuario> *buscarU = _LU->getCabeza();
    nodo<materia> *mat = _LM->getCabeza();
    libro* lib;

    mat = buscarM(matId);
    while ((mat = buscarT(libroNuevo, mat)) != nullptr) {

        while (buscarU != nullptr) {
            if (buscarU->getDato()->getCedula() == id) {

                lib = traerlibro(mat, libroNuevo);

                buscarU->getDato()->agregarLibro(lib);

                cambiarDisponibilidadFalse(libroNuevo, matId);

                cout << "\tPRESTAMO REALIZADO CON EXITO\n";
            }
            buscarU = buscarU->getSig();
        }
        mat = mat->getSig();
    }

}

bool biblioteca::verificarPrestamo(string id) {
    nodo <usuario> *actual = _LU->getCabeza();

    while (actual != nullptr) {

        if (actual->getDato()->getCedula() == id) {
            /*VER SI TIENE MÁS DE 8 LIBROS PRESTADOS O TIENE ALGUNO VENCIDO*/
            if (actual->getDato()->getCantLibros() > 8 || actual->getDato()->getVencidos() == true) {
                return false;
            }
        }
        actual = actual->getSig();
    }
    return true;
}

/*CAMBIA LA DISPONIBIDAD DEL LIBRO PARA QUE NO PUEDA SER PRESTADO DE NUEVO*/
void biblioteca::cambiarDisponibilidadFalse(string libro, string mate) {
    nodo<materia>* actual;
    actual = buscarM(mate);
    if (actual != nullptr) {

        actual->getDato()->CambiarDispoFalse(libro);

    }
}

/*LIBERA EL LIBRO PARA QUE PUEDA SER PRESTADO DE NUEVO*/
bool biblioteca::cambiarDisponibilidadTrue(string numero) {
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {

        if (actual->getDato()->CambiarDispoTrue(numero) == true) {
            return true;
        }

        actual = actual->getSig();
    }
    return false;
}

/*DEVUELVE UN LIBRO ESPECIFICO POR SU TITULO Y MATERIA*/
libro* biblioteca::traerlibro(nodo<materia>* actual, string titulo) {
    return actual->getDato()->traer(titulo);
}

//                                                                      MATERIA

/*VERIFICA QUE A LISTA NO ESTE VACIA*/
bool biblioteca::verificarListaMateria() {

    nodo<materia>* actual = _LM->getCabeza();

    if (actual != nullptr) {
        return true;
    }
    return false;
}

/*AGREGA UNA MATERIA A LA LISTA*/
void biblioteca::agregarMateria() {
    string opcRegistro, mt;

    fflush(stdin);

    system("clear");
    cout << "\t\t DESEA INGRESAR UNA MATERIA EN LA BIBLIOTECA?\n";
    cout << "1 - SI\n"
            "2 - NO\n"
            "Opcion: ";
    getline(cin, opcRegistro);
    try {
        if (opcRegistro != "1" && opcRegistro != "2") {
            throw opcRegistro;
        }
        if (std::stoi(opcRegistro) == 1) {
            cout << "Digite la materia que desea ingresar\n";
            getline(cin, mt);

            if (buscarM(mt) == nullptr) {
                materia* mat = new materia(mt);
                _LM->agregar(mat);
            }
        }
    } catch (string opcRegistro) {
    }
}

/*COMPLEMENTO DE AGREGARLIBROPT2, PARA AGREGAR UN LIBRO, SI LA MATERIA INGRESADA 
 NO SE ENCUENTRA EN LA LISTA */
bool biblioteca::agregarMateriaParaAgregarLibro(string mt) {
    string opcRegistro;

    fflush(stdin);

    system("clear");
    cout << "\t\t LA MATERIA QUE DIGITO NO SE ENCUENTRA EN LA BIBLIOTECA\n";
    cout << "\t\t\t DESEA AGREGARLA?\n";
    cout << "1 - SI\n"
            "2 - NO\n"
            "Opcion: ";
    //opcRegistro;
    getline(cin, opcRegistro);
    try {
        if (opcRegistro != "1" && opcRegistro != "2") {
            throw opcRegistro;
        }
        if (std::stoi(opcRegistro) == 1) {
            materia* mat = new materia(mt);
            _LM->agregar(mat);
        } else if (std::stoi(opcRegistro) == 2) {
            return false;
        }
    } catch (string opcRegistro) {
        return false;
    }
    return true;
}

/*BUSCA LA MATERIA INGRESADA POR PARAMETROS Y DEVUELVE EL NODO DE LA 
  LISTA EN EL QUE SE ENCUENTRA LA MATERIA*/
nodo<materia>* biblioteca::buscarM(string mat) {
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->getIdent() == mat) {

            return actual;
        }
        actual = actual->getSig();
    }
    return nullptr;
}

/*BUSCA UN LIBRO POR EL TITULO EN UN NODO EN EL QUE YA SE ENCONTRO
   LA MATERIA ( UTILIZA BUSCARM )*/
nodo<materia>* biblioteca::buscarT(string titulo, nodo<materia>* mat) {
    if (mat == nullptr) {
        return nullptr;
    }
    string mt = mat->getDato()->getIdent();
    while (mat != nullptr) {
        if (mat->getDato()->especificoT(titulo) == true) {
            return mat;
        }
        mat = mat->getSig();
    }
    return nullptr;
}

/*BUSCA UN LIBRO EN LA BIBLIOTECA POR MEDIO DEL TITULO*/
nodo<materia>* biblioteca::buscarT2(string titulo) {
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->especificoT(titulo) == true) {
            return actual;
        }
        actual = actual->getSig();
    }
    return nullptr;
}

/*BUSCA UN LIBRO EN LA BIBLIOTECA POR MEDIO DEL AUTOR*/
nodo<materia>* biblioteca::buscarA(string autor) {
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->especificoA(autor) == true) {
            return actual;
        }
        actual = actual->getSig();
    }
    return nullptr;
}

/*SE INGRESA A LA MATERIA QUE SE QUIERE ELIMINAR Y SE ELIMINA*/
void biblioteca::eliminarMateria() {
    system("clear");
    fflush(stdin);
    nodo<materia>* mt;
    string mat;
    cout << " Digite la materia que desea eliminar: \n";
    getline(cin, mat);

    mt = buscarM(mat);

    if (mt != nullptr) {
        _LM->eliminar(mt->getDato());
    }
}
//                                                                        LIBRO

/*se verifica si el usuario desea realizar la inclusion de un libro */
void biblioteca::agregarLibro() {
    string opcRegistro;

    fflush(stdin);

    system("clear");
    cout << "\t\t DESEA INGRESAR UN LIBRO EN LA BIBLIOTECA?\n";
    cout << "1 - SI\n"
            "2 - NO\n"
            "Opcion: ";
    getline(cin, opcRegistro);
    try {
        if (opcRegistro != "1" && opcRegistro != "2") {
            throw opcRegistro;
        }
        if (std::stoi(opcRegistro) == 1) {
            agregarLibroPT2();
        }
    } catch (string opcRegistro) {
    }
}

void biblioteca::agregarLibroPT2() {
    numLIbro = 0;
    nodo<materia>* actual = _LM->getCabeza();

    string titulo, autor, mate, editorial;
    stringstream x;
    int anno, cantLibros;

    fflush(stdin);
    cout << "\n\tDigite el titulo de la obra\n";
    getline(cin, titulo);

    cout << "\n\tDigite el nombre del autor de la obra\n";
    getline(cin, autor);
    int au = autor.length();

    cout << "\n\tDigite la materia a la que pertenece esta obra\n";
    getline(cin, mate);

    if (buscarM(mate) == nullptr) {
        if (agregarMateriaParaAgregarLibro(mate) == false) {
            return;
        }
    }

    cout << "\n\tDigite el nombre de la editorial a la que pertenece la obra\n";
    getline(cin, editorial);

    cout << "\n\tDigite el anno en el que fue publicada la obra\n";
    anno = convertirNumero();

    cout << "\n\tDigite la cantidad de copias que desea ingresar a la biblioteca\n";

    cantLibros = convertirNumero();

    actual = buscarM(mate);

    if (actual != nullptr) {
        numLIbro++;
        if (numLIbro <= 9) {
            x << mate[0] << mate[1] << mate[2] << "-";

            x << autor[0] << autor[au - 1];

            x << "-0" << numLIbro;
        } else {
            x << mate[0] << mate[1] << mate[2] << "-" << autor[0] << autor[1] << autor[2] << "-" << numLIbro;
        }

        int i = 1;
        
        while (i <= cantLibros) {
            libro * nuevoLibro = new libro(titulo, autor, mate, anno, editorial, i);
            actual->getDato()->agregar(nuevoLibro);
            darNumUnico(actual, x.str(), titulo, i);
            i++;
        }
    }
}

int biblioteca::convertirNumero() {
    int numero = 0;
    bool repite = true;
    std::string linea;
    do {
        std::getline(std::cin, linea);
        if (verificarNumero(linea)) {
            repite = false;
        } else {
            std::cout << "\n\tERROR\nEl dato debe contener solo numeros" << std::endl;
            std::cout << "Digite el dato nuevamente: ";
        }
    } while (repite); //while (repite == true)

    numero = atoi(linea.c_str());

    return numero;
}

bool biblioteca::verificarNumero(std::string linea) {
    bool b = true;
    int longitud = linea.size();

    if (longitud == 0) { // Cuando el usuario pulsa ENTER
        b = false;
    } else if (longitud == 1 && !isdigit(linea[0])) {
        b = false;
    } else {
        int i;
        if (linea[0] == '+' || linea[0] == '-')
            i = 1;
        else
            i = 0;
        while (i < longitud) {
            if (!isdigit(linea[i])) {
                b = false;
                break;
            }
            i++;
        }
    }
    return b;
}

void biblioteca::darNumUnico(nodo<materia>* actual, string codigo, string titulo, int i) {
    if (actual != nullptr) {
        actual = buscarT(titulo, actual);
        if (actual != nullptr) {
            actual->getDato()->darUnico(codigo, titulo, i);
        }
    }
}

void biblioteca::eliminarLibro() {
    nodo<materia> * actual = _LM->getCabeza();
    fflush(stdin); //LIMPIAR BUFFER 
    system("clear");
    string lib, mat;
    cout << "Digite el nombre del libro\n";
    getline(cin, lib);
    cout << "Digite la materia del libro\n";
    getline(cin, mat);
    actual = buscarM(mat);

    while ((actual = buscarT(lib, actual)) != nullptr) {
        actual->getDato()->eliminar(lib);
    }
}

//                                                                     DEVOLVER 

void biblioteca::devolverLibro(string id) {
    fflush(stdin); //LIMPIAR BUFFER 
    //system("clear");
    string m;

    string mat;
    string ti;

    m = imprimirSolicitados(id);

    cout << m << "\n\n";
    if (m == "Aun no ha solicitado ningun libro\n") {
        cin.get();
        return;
    }

    cout << "Digite el numero unico del libro que desea devolver:\n";
    cout << "Opcion: ";
    getline(cin, ti);

    if (ti != "") {
        devolviendo(ti, id);
    } else {
        cerr << "No digitó nada\n";
        cin.get();
    }
}

void biblioteca::devolviendo(string num, string id) {
    nodo<usuario> *buscarU = _LU->getCabeza();

    while (buscarU != nullptr) {
        if (buscarU->getDato()->getCedula() == id) {
            buscarU->getDato()->quitarLibro(num);
            if (cambiarDisponibilidadTrue(num) == true) {
                cout << "Devolucion realiza exitosamente\n";
                cin.get();
                return;
            }
        }
        buscarU = buscarU->getSig();
    }
}

//                                                                      USUARIO

bool biblioteca::verificarUsuario(string id) {
    nodo<usuario> *buscar = _LU->getCabeza();

    while (buscar != nullptr) {
        if (buscar->getDato()->getCedula() == id) {
            return true;
        }
        buscar = buscar->getSig();
    }
    return false;
}

void biblioteca::registrarUsuario() {
    string opcRegistro, nombre, cedula;

    fflush(stdin); //LIMPIAR BUFFER 
    system("clear");

    cout << "\tDesea registrarse?\n";
    cout << "1 - SI\n"
            "2 - NO\n"
            "Opcion: ";
    getline(cin, opcRegistro);
    try {
        if (opcRegistro != "1" && opcRegistro != "2") {
            throw opcRegistro;
        }
        if (std::stoi(opcRegistro) == 1) {
            agregarUsuario();
        }
    } catch (string opcRegistro) {
    }
}

void biblioteca::agregarUsuario() {
    string nombre;
    string numero;
    string ident;

    nodo<usuario> * actual = _LU->getCabeza();


    fflush(stdin); //LIMPIAR BUFFER 
    system("clear");

    cout << "Digite su nombre\n";
    getline(cin, nombre);

    cout << "Digite su numero de identificacion\n";
    getline(cin, ident);

    cout << "Digite su contraseña\n";
    getline(cin, numero);

    if (actual == nullptr) {
        usuario *u1 = new usuario(nombre, ident, numero, 0, false);
        _LU->agregar(u1);
        system("clear");

        cout << "Esta sera su informacion en la biblioteca: \n\n";
        cout << imprimirUsuarioEspecifico(ident);
        cout << "\n Para ingresar  a la biblioteca solo debe ingrresar \n"
                "     su numero de indentificacion y contraseña\n";
        cin.get();
    }

    while (actual != nullptr) {
        try {
            if (actual->getDato()->getCedula() == ident) {
                throw -1;
            }
        } catch (int) {
            cerr << "\t\tERROR\n"
                    "El usuario ya existe\n";
            cin.get();
            return;
        }
        actual = actual->getSig();
    }

    usuario *u1 = new usuario(nombre, ident, numero, 0, false);
    _LU->agregar(u1);
    system("clear");

    cout << "Esta sera su informacion en la biblioteca: \n\n";
    cout << imprimirUsuarioEspecifico(ident);
    cout << "\n Para ingresar  a la biblioteca solo debe ingrresar \n"
            "     su numero de indentificacion y contraseña\n";
    cin.get();
    return;
}

void biblioteca::eliminarUsuario() {
    system("clear");
    string cedula;
    usuario* us;

    cout << endl << _LU->toString() << endl;

    if (_LU->getCabeza() == nullptr) {
        cin.get();
        return;
    }

    cout << "Escriba la cedula del usuario que desea eliminar \n";
    cout << "Opcion: ";
    getline(cin, cedula);

    us = buscarUsuarioEliminar(cedula);
    if (us == nullptr) {
        cout << "Usuario no encontrado\n";
        cin.get();
        return;
    }
    _LU->eliminar(us);
}

usuario* biblioteca::buscarUsuarioEliminar(string nombre) {
    nodo<usuario> * actual = _LU->getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getNombre() == nombre) {
            return actual->getDato();
        }
        actual = actual->getSig();
    }
    return nullptr;
}

//                                                                    SOLICITAR

string biblioteca::imprimirSolicitados(string id) {
    nodo<usuario> * actual = _LU->getCabeza();

    stringstream x;


    while (actual != nullptr) {
        if (actual->getDato()->getCedula() == id) {

            x << actual->getDato()->imprimirLibros();
        }
        actual = actual->getSig();
    }
    return x.str();
}

void biblioteca::buscarLibros() {


    string opc = "";
    string autor = "";
    string materia = "";
    string titulo = "";

    fflush(stdin); //LIMPIAR BUFFER 
    system("clear");

    cout << "\t\tDigite una de las siguientes opciones\n";
    cout << "1 - Buscar libro por Nombre del autor\n";
    cout << "2 - Buscar libro por Titulo\n";
    cout << "3 - Buscar libro por Materia\n";
    cout << "4 - Ver todos los libros disponibles\n";

    cout << "\n\t\tSi no se desplega nada en pantalla \nes porque no se encuentra disponible ningun libro "
            "con el criterio buscado\n\n";

    cout << "Opcion:  ";
    getline(cin, opc);

    try {
        if (opc != "1" && opc != "2" && opc != "3" && opc != "4" && opc != "99") {
            throw opc;
        }

        switch (std::stoi(opc)) {
            case 1:
                cout << "Digite el nombre del autor/a que desea buscar:   ";
                getline(cin, autor);

                if (buscarA(autor) != nullptr) {
                    cout << endl << imprimirAutor(autor) << endl;
                } else {
                    cout << "No se encontro ningun/a autor/a con ese nombre:   ";
                }
                break;

            case 2:
                cout << "Digite el nombre del titulo del libro que desea buscar:   ";
                getline(cin, titulo);

                if (buscarT2(titulo) != nullptr) {
                    cout << endl << imprimirTitulo(titulo) << endl;
                } else {
                    cout << "No se encontro ningun titulo con ese nombre\n";
                }
                break;

            case 3://VERIFICAR
                cout << "Digite el nombre de la materia que desea buscar:   ";
                getline(cin, materia);

                cout << endl << imprimirMateria(materia) << endl;

                break;

            case 4:
                cout << endl << verDisponibles() << endl;
                break;
        }
    } catch (string opc) {
    }
}

bool biblioteca::buscarRepetido(string titulo) {


    nodo<materia>* actual = _LM->getCabeza();

    string encontrado = "false";
    string encontrado2 = "false";
    bool repetido = false;

    while (actual != nullptr) {
        if (actual->getDato()->especificoT(titulo) == true) {
            encontrado = actual->getDato()->getIdent(); //INFORMATICA
        }
        actual = actual->getSig();
        if (actual != nullptr) {
            if (actual->getDato()->especificoT(titulo) == true) {
                encontrado2 = actual->getDato()->getIdent(); //QUIMICA
            }
        }
    }
    if (encontrado != "false" && encontrado2 != "false") {
        repetido = true;
    }
    return repetido;
}

//                                                                  IMPRESIONES

string biblioteca::imprimirMateria(string mat) {
    stringstream x;
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {
        if (actual->getDato()->especificoM(mat) == true) {
            x << actual->getDato()->verDisponibles() << endl;
            //x << actual->getDato()->toString() << endl;
        }
        actual = actual->getSig();
    }
    return x.str();
}

string biblioteca::imprimirAutor(string autor) {
    stringstream x;
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {

        //if (actual->getDato()->especificoA(autor) != nullptr) {

        x << actual->getDato()->traerAutor(autor) << endl;

        //}
        actual = actual->getSig();
    }
    return x.str();
}

string biblioteca::imprimirTitulo(string titulo) {

    nodo<materia>* actual = _LM->getCabeza();
    stringstream x;

    while (actual != nullptr) {


        x << actual->getDato()->imprimirEspecifico(titulo);


        actual = actual->getSig();
    }
    return x.str();
}

string biblioteca::verDisponibles() {
    stringstream x;
    nodo<materia>* actual = _LM->getCabeza();

    while (actual != nullptr) {
        x << actual->getDato()->verDisponibles() << endl;
        actual = actual->getSig();
    }
    return x.str();
}

string biblioteca::imprimirUsuarioEspecifico(string id) {
    stringstream x;
    nodo<usuario>* actual = _LU->getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getCedula() == id) {
            x << *actual->getDato() << endl;
        }
        actual = actual->getSig();
    }
    return x.str();
}

string biblioteca::imprimirUsuarioParaEliminar() {
    stringstream x;
    nodo<usuario>* actual = _LU->getCabeza();
    while (actual != nullptr) {
        if (actual->getDato()->getVencidos() == true) {
            x << *actual->getDato() << endl;

        }
        actual = actual->getSig();
    }
    return x.str();
}

//                                                                     ARCHIVOS

void biblioteca::escribirUsuarios() {
    nodo<usuario> * actual = _LU->getCabeza();
    ofstream archivo;
    archivo.open("ListaDeUsuarios.csv");

    try {
        if (archivo.good() == true) {
            while (actual != nullptr) {
                usuario * nuevo = actual->getDato();
                nuevo->autoGuardar(archivo);
                actual = actual->getSig();
            }
        } else {
            throw -1;
        }
    } catch (int) {
        cerr << "\t\tHUBO UN ERROR AL ABRIR EL ARCHIVO\n";
        cin.get();
    }
    archivo.close();
}

void biblioteca::leerUsuarios() {
    ifstream archivo;
    usuario * aux;
    usuario * nuevoU = new usuario;

    archivo.open("ListaDeUsuarios.csv");

    try {
        if (archivo.good() == false || !archivo) {
            archivo.close();
            throw -1;
        } else {
            while (archivo.eof() == false) {
                aux = &nuevoU->autoCargar(archivo);
                if (aux->getNombre() != "") {
                    _LU->agregar(aux);
                }
            }
        }
    } catch (int) {
        cerr << "\t\tHUBO UN ERROR AL ABRIR EL ARCHIVO\n";
        cin.get();
    }
    archivo.close();
}

void biblioteca::escribirMaterias() {
    nodo<materia> * actual = _LM->getCabeza();
    ofstream archivo;
    archivo.open("ListaDeMaterias.csv");
    try {
        if (archivo.good() == true) {
            while (actual != nullptr) {
                materia * nuevaM = actual->getDato();
                nuevaM->autoGuardar(archivo);
                actual = actual->getSig();
            }
        } else {
            throw -1;
        }
    } catch (int) {
        cerr << "\t\tHUBO UN ERROR AL ABRIR EL ARCHIVO\n";
        cin.get();
    }
    archivo.close();
}

void biblioteca::leerMaterias() {
    ifstream archivo;
    materia * aux;
    string vacio;
    materia * nuevaM = new materia("");

    archivo.open("ListaDeMaterias.csv");
    try {
        if (archivo.good() == false || !archivo) {
            archivo.close();
            throw -1;
        } else {
            getline(archivo, vacio, '\n');
            while (archivo.eof() == false) {
                aux = &nuevaM->autoCargar(archivo);
                if (aux->getIdent() != "") {
                    _LM->agregar(aux);
                }
            }
        }
    } catch (int) {
        cin.get();
        cerr << "\t\tHUBO UN ERROR AL ABRIR EL ARCHIVO\n";
    }
}