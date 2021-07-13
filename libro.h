#ifndef LIBRO_H
#define LIBRO_H

#include "objetoBase.h"

class libro : public objetoBase {
public:

    libro();
    libro(string titulo, string autor, string materia, int annoPublicacion, string editorial, int numLibro);
    virtual ~libro();

    string getTitulo();
    string getAutor();
    string getMateria();
    bool getDisponibilidad();
    void setDisponibilidad(bool);
    string getNumU();
    void setNumU(string num);
    int getNum();
    
    virtual string toString();
    
private:
    
    string titulo;
    string autor;
    string materia;
    int annoPublicacion;
    string editorial;
    bool disponibilidad;
    string numUnico;
    int numLibro;
};

#endif /* LIBRO_H */

