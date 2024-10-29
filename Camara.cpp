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

/**
 * Función que devuelve la transformación de visión con los parámetros de la cámara
 * Nos llevamos la cámara al origen de coordenadas
 * @return
 */
glm::mat4 PAG::Camara::getMatrizVision() {
    return glm::lookAt(posicion, lookAt, glm::vec3(0,1,0));
}

/**
 * Función que devuelve la transformación de perspectiva con los parámetros de la cámara
 * @return
 */
glm::mat4 PAG::Camara::getMatrizPerspectiva() {
    return glm::perspective(fovY, aspect, zNear, zFar);
}

/**
 * Rotamos en el eje y, la posicion del punto al que mira la camara ( lookAt )
 * Movimiento PAN
 */
void PAG::Camara::rotarSobreEjeY() {
    glm::mat4 rotacionY = glm::rotate(glm::radians(1.0f) ,glm::vec3(0,1,0));

    lookAt = rotacionY * glm::vec4(lookAt, 1);
}

/**
 * Desplazamos la posicion de la camara y el punto de mira en el ejeX
 * @param positivo True si la camara se mueve en el eje X positivo, y false si se mueve
 */
void PAG::Camara::desplazarSobreEjeX(bool positivo) {
    if(!positivo){
        posicion = glm::translate(glm::vec3(-0.1, 0, 0)) * glm::vec4(posicion, 1 );
        lookAt = glm::translate(glm::vec3(-0.1, 0, 0)) * glm::vec4(lookAt, 1 );
    }else{
        posicion = glm::translate(glm::vec3(0.1, 0, 0)) * glm::vec4(posicion, 1 );
        lookAt = glm::translate(glm::vec3(0.1, 0, 0)) * glm::vec4(lookAt, 1 );
    }

}
