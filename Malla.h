//
// Created by secre on 17/11/2024.
//

// #pragma once /// Esto sirve para decirle al compilador que solo compile el archivo .h una vez, por lo que hace lo mismo que el #ifndef y el #define

/// Include Guards, para que no se lean .h innecesarios duplicado
#ifndef PR1_MALLA_H
#define PR1_MALLA_H

#include <vector>
#include <GL/gl.h>
#include <glm/mat4x4.hpp>

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

        void trasladarMalla(glm::mat4 matrizTraslacion);
        void rotarMalla(glm::mat4 matrizRotacion);
        void escalarMalla(glm::mat4 matrizEscalado);
    };
}


#endif //PR1_MALLA_H
