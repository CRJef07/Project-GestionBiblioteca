#ifndef MATERIA_H
#define MATERIA_H

#include "lista.h"
#include "libro.h"

class materia : public objetoBase {
public:
    //                                                                  BASICOS
    materia(string);
    ~materia();
    virtual string toString();
    void agregar(libro*); //AGREGAR UN LIBRO
    void eliminar(string); //ELIMINAR UN LIBRO
    string getIdent(); 
    
    //                                                                   BUSCAR
    
    bool especificoM(string); //BUSCAR POR MATERIA
    bool especificoA(string); //BUSCAR POR AUTOR
    bool especificoT(string); //BUSCAR POR TITULO    
    libro* traer(string); //DEVOLVER UN LIBRO ESPECIFICO
    
    libro* traerParaEliminar(string); //DEVOLVER LIBRO ESPECIFICO PARA ELIMINAR
    
    virtual string imprimirEspecifico(string); //IMPRIME UN LIBRO ESPECIFICO
    
    //                                                                    LIBRO 
    
    void darUnico(string, string, int); //DAR UN NUMERO UNICO A UN LIBRO
    void CambiarDispoFalse(string); //CAMBIAR LA DISPONIBILIDAD A UN LIBRO ESPECIFICO
    bool CambiarDispoTrue(string); //CAMBIAR LA DISPONIBILIDAD A UN LIBRO ESPECIFICO
    virtual string verDisponibles(); //IMPRIME UN UNICO LIBRO DISPONIBLE DE CADA GRUPO
    string traerAutor(string); //IMPRIME UN LIBRO POR SU AUTOR
    
    //                                                                 ARCHIVOS
    void autoGuardar(ofstream &); //GUARDAR LISTA
    materia & autoCargar(ifstream &); //LEER LISTA
    
    
    
private:
    lista<libro>* _lista;
    string id;
};
#endif /* MATERIA_H */

