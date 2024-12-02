//
// Created by secre on 29/11/2024.
//

#include "GL/gl.h"

#ifndef PR1_MATERIAL_H
#define PR1_MATERIAL_H
namespace PAG{
    /**
     * Clase que contiene todoo lo relativo a un material, que se le asigna a un modelo
     * Color ambiente, color difuso, color especular, y exponente especular
     *
     * Lo anterior es para decir como se comporta el material al interactuar con la "luz"
     * Un material metalico brilla mucho, la madera no tanto ;) Para lograr eso se juega con los valores del color del material
     */
    class Material {
    private:
        GLfloat Ka[3] {0.1, 0.1, 0.1};
        GLfloat Kd[3] {1.0, .2, .3}; //El color difuso, que es el que se ve al iluminar el modelo con dicho material
        GLfloat Ks[3] {1.0, .2, .3};

    public:
        Material() = default;

        const GLfloat *getKa() const;

        const GLfloat *getKd() const;

        const GLfloat *getKs() const;
    };
}

#endif //PR1_MATERIAL_H
