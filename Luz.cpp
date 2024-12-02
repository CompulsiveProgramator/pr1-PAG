//
// Created by secre on 01/12/2024.
//

#include "Luz.h"

/**
 * Constructor de la clase
 * @param tipo El tipo de luz que se quiere crear
 */
PAG::Luz::Luz(PAG::TipoLuz tipo):tipoLuz(tipo) {}

/**
 * Getter del atributo tipoLuz
 * @return El tipo de luz
 */
PAG::TipoLuz PAG::Luz::getTipoLuz() const {
    return tipoLuz;
}

const GLfloat *PAG::Luz::getIa() const {
    return Ia;
}

const GLfloat *PAG::Luz::getId() const {
    return Id;
}

const GLfloat *PAG::Luz::getIs() const {
    return Is;
}

GLfloat PAG::Luz::getExponenteEspecular() const {
    return exponenteEspecular;
}

const GLfloat *PAG::Luz::getPosicion() const {
    return posicion;
}

const GLfloat *PAG::Luz::getDireccion() const {
    return direccion;
}

GLfloat PAG::Luz::getAnguloApertura() const {
    return anguloApertura;
}

void PAG::Luz::setPosicion(GLfloat *pos) {
    for(int i = 0 ; i < 3 ; i++){
        posicion[i] = pos[i];
    }
}

void PAG::Luz::setDireccion(GLfloat *dir) {
    for(int i = 0 ; i < 3 ; i++){
        direccion[i] = dir[i];
    }
}
