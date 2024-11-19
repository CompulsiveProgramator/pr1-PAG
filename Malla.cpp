//
// Created by secre on 17/11/2024.
//

#include "Malla.h"

/**
 * El constructor de la clase
 */
PAG::Malla::Malla() {
    matrizModelado = glm::rotate(glm::radians(90.0f), glm::vec3(0,0,1));
}

/**
 * El destructor del modelo, que libera los recursos ;)
 */
PAG::Malla::~Malla() {
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
void PAG::Malla::creaModelo() {
    //Para un modelo sencillo, tenemos un VAO, un VBO entrelazado para posicion/color, y un solo IBO para recorrerlo
    //Podemos tener multiples IBOs, uno para ver el modelo como malla de triangulos, otro para verlo como puntos, otro para lineas ...

    ///Los datos del VBO entrelazado para posicion/color de cada vertice ( en este caso hay solo 3 vertices )
    std::vector<GLfloat> vboPosicionColor = {.5, 0., 0., 1., 0., 0.,
                                             -.5, 0., 0., 0., 1., 0.,
                                             0., .5, 0., 0., 0., 1.};

    ///Los datos del IBO para indices de triangulo
    std::vector<GLuint> iboIndicesTriangulo = {0,1,2};

    // Generamos los buffers de OpenGL vacios:
    glGenVertexArrays(1, &idVAO);
    glGenBuffers(1, &idVBO1);
    glGenBuffers(1, &idIBO);

    // Activamos el VAO
    glBindVertexArray(idVAO);

    // Activamos el VBO
    // GL_ARRAY_BUFFER -> Activamos un VBO
    // GL_ELEMENT_ARRAY_BUFFER -> Activamos un IBO
    glBindBuffer(GL_ARRAY_BUFFER, idVBO1);

    ///Cargamos los datos del VBO una sola vez:
    /*
    * Le pasamos los datos al VBO activo, los parametros son para:
    * - Decir que es un VBO
    * - El numero exacto de bytes a leer
    * - Los datos a pasar, con su direccion en memoria
    * - El modo de uso de los datos, GL_STATIC_DRAW es para decir que es solo para leer, no vamos a modificar el modelo
   */
    glBufferData(GL_ARRAY_BUFFER, vboPosicionColor.size() * sizeof(GLfloat), vboPosicionColor.data(), GL_STATIC_DRAW);

    // Le decimos a OpenGL como leer los datos del VBO para que extraiga la posicion y color de cada vertice
    /*
     * La funcion glVertexAttribPointer sirve para decir como leer los datos del VBO, sus parametros son:
     * - El layout que se va a leer
     * - Cuantos elementos tiene cada componente
     * - El tipo del dato de cada componenente
     * - Si queremos que se normalicen los datos
     * - La distancia en "bytes" entre el comienzo de un elemento y otro del mismo tipo (en el ejemplo como es un VBO entrelazado hay 6 flotantes entre cada uno, 3 de posicion y 3 de color)
     * - El desplazamiento en el VBO para llegar al primer elemento (esto es claramente para un VBO entrelazado)
     */
    glEnableVertexAttribArray(0); //Esto es para decir que el contenido que vamos a leer para este VBO ira al "layout = 0" de nuestro vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,6 * sizeof(GLfloat), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * iboIndicesTriangulo.size(), iboIndicesTriangulo.data(), GL_STATIC_DRAW);
}

GLuint PAG::Malla::getIdVao() const {
    return idVAO;
}

GLuint PAG::Malla::getIdVbo1() const {
    return idVBO1;
}

GLuint PAG::Malla::getIdIbo() const {
    return idIBO;
}

const glm::mat4 &PAG::Malla::getMatrizModelado() {
    return matrizModelado;
}
