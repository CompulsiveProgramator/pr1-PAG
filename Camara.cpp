//
// Created by secre on 29/10/2024.
//

#include "Camara.h"

/**
 * Constructor que inicializa todos los parámetros de la cámara virtual
 * @param posicion La posición de la camara respecto a las coordenadas de mundo (x,y,z)
 * @param lookAt El punto al que mira la cámara
 * @param fovY El ángulo de visión vertical en radianes
 * @param aspect La relación ancho/alto de la visión de la cámara
 * @param zNear El valor de z del plano zNear
 * @param zFar El valor de z del plano zFar
 */
PAG::Camara::Camara(glm::vec3 posicion, glm::vec3 lookAt, glm::float32 fovY, glm::float32 aspect, glm::float32 zNear, glm::float32 zFar)
{
    this->posicion = posicion;
    this->lookAt = lookAt;
    this->fovY = fovY;
    this->aspect = aspect;
    this->zNear = zNear;
    this->zFar = zFar;
}

glm::mat4 PAG::Camara::getMatrizVision() {
    return glm::lookAt(posicion, lookAt, glm::vec3(0,1,0));
}

/**
 * Rotamos la posicion de la camara respecto al eje y
 */
void PAG::Camara::rotarSobreEjeY() {
    glm::mat4 rotacionY = glm::rotate(0.1f ,glm::vec3(0,1,0));

    posicion = rotacionY * glm::vec4(posicion, 1);
}
