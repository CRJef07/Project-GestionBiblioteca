#ifndef USUARIO_H
#define USUARIO_H

#include "persona.h"
#include "lista.h"
#include "libro.h"

class usuario : public persona {
public:
    /*CONSTRUCTOR SIN PARÁMETROS DE USUARIO*/
    usuario();

    /*CONSTRUCTOR CON PARÁMETROS DE USUARIO*/
    usuario(string nombre, string cedula, string contra, int cantLibros, bool vencidos);

    /*DESTRUCTOR DE USUARIO*/
    virtual ~usuario();

    /*SETTERS Y GETTERS*/
    virtual void setContra(const string &);
    virtual void setCantLibros(const int &);
    virtual void setVencidos(const bool &);
    /*El primer const de los métodos GET es para el valor. Garantiza que se va a retornar una referencia constante a un valor tipo STRING*/
    /*El segundo const es para el método. Garantiza que no se puede modificar ningún atributo de la clase dentro del método*/
    virtual const string &getContra()const;
    virtual const int &getCantLibros()const;
    virtual const bool &getVencidos()const;

    virtual void agregarLibro(libro*);

    virtual string imprimirLibros();

    virtual string imprimirEspecifico(int);
        
    virtual void quitarLibro(string);
    
    virtual void reordenarVector();

    /*METODO PARA IMPRIMIR EL ESTADO DEL OBJETO*/
    virtual string toString();

    void autoGuardar(ofstream &);
    usuario & autoCargar(ifstream &);
    int convertirInt(string);
    bool convertirBolean(string);
private:
    string contra;

    /*cantidad LibrosPrestados*/
    int cantLibros;

    /*prestamos vencidos si o no*/
    bool vencidos;

    libro* _VL[8];
    //lista<string>* _LB;
};

#endif /* USUARIO_H */
