//
// Created by secre on 01/12/2024.
//

#ifndef PR1_LUZ_H
#define PR1_LUZ_H

#include "GL/gl.h"
#include <math.h>

namespace PAG{

    enum TipoLuz{
        AMBIENTAL,
        PUNTUAL,
        DIRECCIONAL,
        FOCAL
    };

    /**
     * Clase que contiene toda la funcionalidad de la luz, para ser usada en el shader program
     */
    class Luz {
    private:
        TipoLuz tipoLuz;
        GLfloat Ia[3] = {0.1, 0.1, 0.1}; // Color luz ambiente
        GLfloat Id[3] = {.7, .7, .7}; // Color luz difusa
        GLfloat Is[3] = {1., 1., 1.}; // Color luz especular
        GLfloat exponenteEspecular = 1.0; // Exponente para tunear la reflexion especular
        GLfloat posicion[3] = {0.0, -1.0,-1}; // Posicion de la luz ( Puntual o focal )
        GLfloat direccion[3] = {0.0, 0.0, -1.0}; // Vector que dice la direccion de la luz ( Direccional o focal )
        GLfloat anguloApertura = M_PI/3; // El angulo de apertura del foco en grados sexagesimales
    public:
        Luz(TipoLuz tipo);
        TipoLuz getTipoLuz() const;
        const GLfloat *getIa() const;
        const GLfloat *getId() const;
        const GLfloat *getIs() const;
        GLfloat getExponenteEspecular() const;
        const GLfloat *getPosicion() const;
        const GLfloat *getDireccion() const;
        GLfloat getAnguloApertura() const;
        void setPosicion(GLfloat pos[3]);
        void setDireccion(GLfloat dir[3]);
    };
}



#endif //PR1_LUZ_H
