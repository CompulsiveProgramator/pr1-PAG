//
// Created by secre on 29/10/2024.
//

#ifndef PR1_CAMARA_H
#define PR1_CAMARA_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/mat4x4.hpp>

namespace PAG{
    /**
     * Clase para gestionar una camara virtual, que guarda sus atributos (posicion, punto donde mira, angulo de vision vertical, el aspecto (ancho/alto), zNear, zFar)
     */
    class Camara {
    private:
        glm::vec3 posicion, lookAt;
        glm::float32 fovY;
        glm::float32 aspect;
        glm::float32 zNear, zFar;
    public:
        Camara(glm::vec3 posicion, glm::vec3 lookAt, glm::float32 fovY, glm::float32 aspect, glm::float32 zNear, glm::float32 zFar);
        glm::mat4 getMatrizVision();
        glm::mat4 getMatrizPerspectiva();
        void rotarSobreCamaraEjeX(bool antihorario);
        void rotarSobreCamaraEjeY(bool antihorario);
        void desplazarSobreEjeX(bool positivo);
        void desplazarSobreEjeY(bool positivo);
        void desplazarSobreEjeZ(bool positivo);
        void rotarSobreLookAtEjeX(bool antihorario);
        void rotarSobreLookAtEjeY(bool antihorario);
        void zoom(bool positivo);

        const glm::vec3 &getPosicion() const;

        const glm::vec3 &getLookAt() const;

        glm::float32 getFovY() const;

        glm::float32 getAspect() const;

        glm::float32 getZNear() const;

        glm::float32 getZFar() const;
    };
}

#endif //PR1_CAMARA_H
