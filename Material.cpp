//
// Created by secre on 29/11/2024.
//

#include "Material.h"

const GLfloat *PAG::Material::getColorAmbiente() const {
    return colorAmbiente;
}

const GLfloat *PAG::Material::getColorDifuso() const {
    return colorDifuso;
}

const GLfloat *PAG::Material::getColorEspecular() const {
    return colorEspecular;
}

GLfloat PAG::Material::getExponenteEspecular() const {
    return exponenteEspecular;
}
