//
// Created by secre on 17/11/2024.
//

#include "Modelo.h"

/**
 * El destructor del modelo, que libera los recursos ;)
 */
PAG::Modelo::~Modelo() {
    if( idVBO1 != 0 )
    {
        glDeleteBuffers( 1, &idVBO1);
    }

    if( idIBO != 0 )
    {
        glDeleteBuffers( 1, &idIBO);
    }

    if( idVAO != 0 )
    {
        glDeleteVertexArrays( 1, &idVAO);
    }
}

/**
 * Metodo que crea el modelo
 * Con el VAO, VBO e IBO
 */
void PAG::Modelo::creaModelo() {
//Los vertices con su posicion (x,y,z) y color (r,g,b) , en un VBO entrelazado
    //Aquí las coordenadas vienen dadas en el sistema local del triángulo, por lo que todavía se le tienen que aplicar las transformaciones de MVP
    GLfloat posicionVerticeColor[] = { -0.5, -0.5, 0.0,1.0, 0.0, 0.0,
                                       0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
                                       0.0, 0.5, 0.0, 0.0, 0.0, 1.0};

    /*
    //Otro vbo pero para el color de cada vertice
    GLfloat colorVertices[] = { 1.0, 0.0, 0.0,
                                0.0, 1.0, 0.0,
                                0.0, 0.0, 1.0};
    */

    //Solo hay 3 indices porque solo tenemos un triangulo ;)
    GLuint indices[] = {0, 1, 2}; //Los datos del IBO, que dice en que orden se procesan los vertices del VBO1

    glGenVertexArrays ( 1, &idVAO); //Creamos el VAO
    glBindVertexArray ( idVAO); //Enlazamos el VAO para poder usarlo, a partir de aqui todas las operaciones sobre VAOs seran sobre este VAO

    //Generamos los VBOs y IBOs
    glGenBuffers ( 1, &idVBO1);
    //glGenBuffers(1, &idVBO2);
    glGenBuffers (1, &idIBO); //Creamos el IBO

    //VBO para posiciones
    glBindBuffer (GL_ARRAY_BUFFER, idVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(posicionVerticeColor), posicionVerticeColor, GL_STATIC_DRAW);

    //VBO para colores
    //glBindBuffer(GL_ARRAY_BUFFER, idVBO2);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(colorVertices), colorVertices, GL_STATIC_DRAW);

    //IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer (GL_ARRAY_BUFFER, idVBO1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(0); //Habilitamos el layout 0

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(1); //Habilitamos el layout 0

    //glBindBuffer(GL_ARRAY_BUFFER, idVBO2);
    ///Primero decimos que es para el layout 1, y luego lo habilitamos
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    //glEnableVertexAttribArray(1); //Habilitamos el layout 1

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices, GL_STATIC_DRAW); //Le pasamos los datos al IBO
}

GLuint PAG::Modelo::getIdVao() const {
    return idVAO;
}

GLuint PAG::Modelo::getIdVbo1() const {
    return idVBO1;
}

GLuint PAG::Modelo::getIdIbo() const {
    return idIBO;
}
