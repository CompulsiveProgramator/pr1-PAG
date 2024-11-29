//
// Created by secre on 29/11/2024.
//

#include "Material.h"

const float *PAG::Material::getColorAmbiente() const {
    return colorAmbiente;
}

const float *PAG::Material::getColorDifuso() const {
    return colorDifuso;
}

const float *PAG::Material::getColorEspecular() const {
    return colorEspecular;
}

float PAG::Material::getExponenteEspecular() const {
    return exponenteEspecular;
}
