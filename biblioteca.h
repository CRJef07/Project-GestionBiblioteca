#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "materia.h"
#include "usuario.h"

class biblioteca {
public:
    biblioteca();
    ~biblioteca();

    //                                                                     MENU
    virtual void menuPrincipal();
    virtual void menuBibliotecario();
    virtual void inicioSesion();
    virtual void menuUsuario(string, string);
    

    //                                                                  USUARIO
    virtual bool verificarUsuario(string);
    virtual void registrarUsuario();
    virtual void agregarUsuario();
    virtual void eliminarUsuario();
    virtual usuario* buscarUsuarioEliminar(string);

    //                                                                 PRESTAMO
    virtual void realizarPrestamo(string, string);
    virtual void realizarPrestamoRepetido(string, string, string);
    virtual bool verificarPrestamo(string);
    virtual void cambiarDisponibilidadFalse(string, string);

    //                                                                  MATERIA

    virtual bool verificarListaMateria();
    virtual void agregarMateria();
    virtual bool agregarMateriaParaAgregarLibro(string);
    virtual nodo<materia>* buscarM(string);
    virtual nodo<materia>* buscarT(string, nodo<materia>*);
    virtual nodo<materia>* buscarT2(string);
    virtual nodo<materia>* buscarA(string);
    virtual void eliminarMateria();

    //                                                                    LIBRO
    virtual void agregarLibro();
    virtual void agregarLibroPT2();
    virtual int convertirNumero();
    virtual bool verificarNumero(std::string linea);
    virtual void darNumUnico(nodo<materia>*, string, string, int);
    virtual void eliminarLibro();

    //                                                                 DEVOLVER

    virtual void devolverLibro(string);
    virtual void devolviendo(string, string);
    //virtual void cambiarDisponibilidadTrue( string);
    virtual bool cambiarDisponibilidadTrue( string);

    //                                                                SOLICITAR
    
    virtual void solicitarLibro(string);    
    virtual string imprimirSolicitados(string);
    virtual void buscarLibros();
    virtual bool buscarRepetido(string);
    virtual libro* traerlibro(nodo<materia>*, string);


    //                                                                 IMPRIMIR
    virtual string imprimirMateria(string);
    virtual string imprimirTitulo(string);
    virtual string imprimirAutor(string);
    virtual string verDisponibles();
    virtual string imprimirUsuarioEspecifico(string);
    virtual string imprimirUsuarioParaEliminar();

    //                                                                 ARCHIVOS

    void escribirUsuarios();
    void leerUsuarios();
    void escribirMaterias();
    void leerMaterias();


private:
    lista<materia>* _LM;
    lista<usuario>* _LU;
    int numLIbro;
};
#endif /* BIBLIOTECA_H */

