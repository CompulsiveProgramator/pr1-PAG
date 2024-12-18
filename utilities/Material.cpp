//
// Created by secre on 29/11/2024.
//

#include "Material.h"

const GLfloat *PAG::Material::getKa() const {
    return Ka;
}

const GLfloat *PAG::Material::getKd() const {
    return Kd;
}

const GLfloat *PAG::Material::getKs() const {
    return Ks;
}
