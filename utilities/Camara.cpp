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
    return glm::perspective(fovY, aspect, zNear, zFar); //ToDo Estudiar como usarla correctamente
}

/**
 * Rotamos en el eje x "de la camara", la posicion del punto al que mira la camara ( lookAt )
 * Movimiento TILT
 * @param antihorario True si rotamos antihorario, y false si rotamos horario
 */
void PAG::Camara::rotarSobreCamaraEjeX(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionCamara = glm::translate(posicion) * glm::rotate(glm::radians(10.0f), glm::vec3(1,0,0)) * glm::translate(-posicion);
        lookAt = rotacionSobrePosicionCamara * glm::vec4(lookAt, 1);
    }else{
        glm::mat4 rotacionSobrePosicionCamara = glm::translate(posicion) * glm::rotate(glm::radians(-10.0f), glm::vec3(1,0,0)) * glm::translate(-posicion);
        lookAt = rotacionSobrePosicionCamara * glm::vec4(lookAt, 1);
    }
}

/**
 * Rotamos en el eje y "de la camara", la posicion del punto al que mira la camara ( lookAt )
 * Movimiento PAN
 * @param antihorario True si rotamos en sentido antihorario visto desde arriba, y false si vamos horario
 * //ToDo El movimiento PAN solo funciona bien si me alejo haciendo un Dolly en el eje z antihorario, probablemente tenga que ver con los parametros de la camara y glm::perspective
 */
void PAG::Camara::rotarSobreCamaraEjeY(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionCamara = glm::translate(posicion) * glm::rotate(glm::radians(10.0f), glm::vec3(0,1,0)) * glm::translate(-posicion);
        lookAt = rotacionSobrePosicionCamara * glm::vec4(lookAt, 1);
    }else{
        glm::mat4 rotacionSobrePosicionCamara = glm::translate(posicion) * glm::rotate(glm::radians(-10.0f), glm::vec3(0,1,0)) * glm::translate(-posicion);
        lookAt = rotacionSobrePosicionCamara * glm::vec4(lookAt, 1);
    }
}

/**
 * Desplazamos la posicion de la camara y el punto de mira en el ejeX
 * Movimiento DOLLY
 * @param positivo True si la camara se mueve en el eje X positivo, y false si se mueve en el eje x negativo
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

/**
 * Desplazamos la posición de la camara y el punto de mira en el ejeY
 * Movimiento CRANE
 * @param positivo True si la camara se mueve en el eje y positivo, y false si se mueve en el eje y negativo
 */
void PAG::Camara::desplazarSobreEjeY(bool positivo) {
    if(!positivo){
        posicion = glm::translate(glm::vec3(0, -.1, 0)) * glm::vec4(posicion, 1);
        lookAt = glm::translate(glm::vec3(0, -.1, 0)) * glm::vec4(lookAt, 1);
    }else{
        posicion = glm::translate(glm::vec3(0, .1, 0)) * glm::vec4(posicion, 1);
        lookAt = glm::translate(glm::vec3(0, .1, 0)) * glm::vec4(lookAt, 1);
    }
}

/**
 * Desplazamos la posicion de la camara y el punto de mira en el ejeZ
 * Movimiento DOLLY
 * @param positivo True si vamos a la z positiva, false si vamos a la z negativa
 */
void PAG::Camara::desplazarSobreEjeZ(bool positivo) {
    if(!positivo){
        posicion = glm::translate(glm::vec3(0, 0, -0.1)) * glm::vec4(posicion, 1);
        lookAt = glm::translate(glm::vec3(0, 0, -0.1)) * glm::vec4(lookAt, 1);
    }else{
        posicion = glm::translate(glm::vec3(0, 0, 0.1)) * glm::vec4(posicion, 1);
        lookAt = glm::translate(glm::vec3(0, 0, 0.1)) * glm::vec4(lookAt, 1);
    }
}

/**
 * Orbitamos alrededor de LookAt entre norte y sur
 * Movimiento ORBIT
 * @param antihorario True si es antihorario, y false si es horario
 */
void PAG::Camara::rotarSobreLookAtEjeX(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(10.0f), glm::vec3(1,0,0)) * glm::translate(-lookAt);
        posicion = rotacionSobrePosicionLookAt * glm::vec4(posicion, 1);
    }else{
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(-10.0f), glm::vec3(1,0,0)) * glm::translate(-lookAt);
        posicion = rotacionSobrePosicionLookAt * glm::vec4(posicion, 1);
    }
}

/**
 * Orbitamos alrededor de LookAt entre este y oeste
 * Movimiento ORBIT
 * @param antihorario True si es antihorario, y false si es horario
 */
void PAG::Camara::rotarSobreLookAtEjeY(bool antihorario) {
    if(antihorario){
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(10.0f), glm::vec3(0,1,0)) * glm::translate(-lookAt);
        posicion = rotacionSobrePosicionLookAt * glm::vec4(posicion, 1);
    }else{
        glm::mat4 rotacionSobrePosicionLookAt = glm::translate(lookAt) * glm::rotate(glm::radians(-10.0f), glm::vec3(0,1,0)) * glm::translate(-lookAt);
        posicion = rotacionSobrePosicionLookAt * glm::vec4(posicion, 1);
    }
}

/**
 * Hacemos zoom con la camara
 * @param positivo True si aumentamos el fovY y false si lo disminuimos
 */
void PAG::Camara::zoom(bool positivo) {
    if(positivo){
        fovY += glm::radians(1.0f);
    }else{
        if(fovY > 0){
            fovY -= glm::radians(1.0f);
        }
    }
}

const glm::vec3 &PAG::Camara::getPosicion() const {
    return posicion;
}

const glm::vec3 &PAG::Camara::getLookAt() const {
    return lookAt;
}

glm::float32 PAG::Camara::getFovY() const {
    return fovY;
}

glm::float32 PAG::Camara::getAspect() const {
    return aspect;
}

glm::float32 PAG::Camara::getZNear() const {
    return zNear;
}

glm::float32 PAG::Camara::getZFar() const {
    return zFar;
}
