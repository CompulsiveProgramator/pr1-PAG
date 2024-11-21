//
// Created by secre on 17/11/2024.
//

#ifndef PR1_MALLA_H
#define PR1_MALLA_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glad/glad.h>
#include "GL/gl.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include <vector>

namespace PAG{
    class Malla {
    private:
        ///Los ids del VAO, VBO y IBO del modelo
        GLuint idVAO = 0; //Id del Vertex Array Object
        GLuint idVBO1 = 0; //Id del Vertex Buffer Object
        GLuint idIBO = 0; //Id del Index Buffer Object

        glm::mat4 matrizModelado; //La matriz de modelado, que coloca en escena al objeto ;)
    public:
        Malla();
        ~Malla();
        void creaModeloPrueba();
        void creaModelo(std::vector<GLfloat> posicionVertices, std::vector<GLfloat> coloresVertices, std::vector<GLuint> indices);
        GLuint getIdVao() const;
        GLuint getIdVbo1() const;
        GLuint getIdIbo() const;
        const glm::mat4 &getMatrizModelado();
    };
}


#endif //PR1_MALLA_H
