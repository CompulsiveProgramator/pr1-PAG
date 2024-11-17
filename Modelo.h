//
// Created by secre on 17/11/2024.
//

#ifndef PR1_MODELO_H
#define PR1_MODELO_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include "GL/gl.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"

namespace PAG{
    class Modelo {
    private:
        ///Los ids del VAO, VBO y IBO del modelo
        GLuint idVAO = 0; //Id del Vertex Array Object
        GLuint idVBO1 = 0; //Id del Vertex Buffer Object
        GLuint idIBO = 0; //Id del Index Buffer Object
    public:
        Modelo() = default;
        ~Modelo();
        void creaModelo();
        GLuint getIdVao() const;
        GLuint getIdVbo1() const;
        GLuint getIdIbo() const;
    };
}


#endif //PR1_MODELO_H
