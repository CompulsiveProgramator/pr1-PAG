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
        GLuint idVBO2 = 0;
        GLuint idIBO = 0; //Id del Index Buffer Object

        GLuint numIndices;
        GLuint numVertices;
        glm::mat4 matrizModelado; //La matriz de modelado, que coloca en escena al objeto ;)

        void creaModeloPrueba();
        void creaModelo(std::vector<GLfloat> posicionVertices, std::vector<GLfloat> coloresVertices, std::vector<GLuint> indices);
    public:
        Malla();
        Malla(std::vector<GLfloat> posicionVertices, std::vector<GLfloat> coloresVertices, std::vector<GLuint> indices);
        ~Malla();
        GLuint getIdVao() const;
        GLuint getIdVbo1() const;
        GLuint getIdIbo() const;
        const glm::mat4 &getMatrizModelado();

        GLuint getNumIndices() const;

        GLuint getNumVertices() const;
    };
}


#endif //PR1_MALLA_H
