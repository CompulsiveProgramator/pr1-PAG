//
// Created by secre on 17/11/2024.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "glad/glad.h"
#include <glm/gtx/transform.hpp>
#include "Malla.h" ///SIEMPRE EL .H DE MI .CPP SE INCLUYE EL ULTIMO

/**
 * Reglas para los includes:
 *
 * 1a -> En el archivo solo poner los includes que se usen directamente, es decir, no declarar en el .h lo que se vaya a usar en el .cpp solo, lo correcto es ponerlo
 * en el .cpp
 * 2o -> Primero los includes <> que son de las librerias externas del proyecto (las que metemos con Conan, las de STL tan chulas, ...)
 * luego los includes "" que son de nuestro proyecto (los de Dear ImGui)
 * 3o -> Invitar a
 */

/**
 * El constructor de la clase
 */
PAG::Malla::Malla() {
    matrizModelado = glm::rotate(glm::radians(90.0f), glm::vec3(0,0,1));
    creaModeloPrueba();
}

PAG::Malla::Malla(std::vector<GLfloat> posicionVertices,
                  std::vector<GLfloat> normales, std::vector<GLfloat> coordenadasTextura, std::vector<GLuint> indices) {
    matrizModelado = glm::translate(glm::vec3(0,0,0));
    creaModelo(posicionVertices, normales, coordenadasTextura, indices);
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
void PAG::Malla::creaModeloPrueba() {
    //Para un modelo sencillo, tenemos un VAO, un VBO entrelazado para posicion/color, y un solo IBO para recorrerlo
    //Podemos tener multiples IBOs, uno para ver el modelo como malla de triangulos, otro para verlo como puntos, otro para lineas ...

    ///Los datos del VBO entrelazado para posicion/color de cada vertice ( en este caso hay solo 3 vertices )
    std::vector<GLfloat> vboPosicionColor = {.5, 0., 0., 1., 0., 0.,
                                             -.5, 0., 0., 0., 1., 0.,
                                             0., .5, 0., 0., 0., 1.};

    ///Los datos del IBO para indices de triangulo
    std::vector<GLuint> iboIndicesTriangulo = {0,1,2};

    numIndices = 3;
    numVertices = 3;

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


/**
 * Metodo que crea el VAO, VBO e IBO para los datos dados
 * @param posicionVertices Un array con las posiciones x,y,z de cada vertice
 * @param normales Un array con las normales (x,y,z) de cada vertice
 * @param indices Un array con los indices para dibujar triangulos      Ej:  0,1,2 == Triangulo con los vertices 0, 1, 2 del array "posicionVertices"
 */
void PAG::Malla::creaModelo(std::vector<GLfloat> posicionVertices, std::vector<GLfloat> normales, std::vector<GLfloat> coordenadasTextura, std::vector<GLuint> indices){
    numVertices = posicionVertices.size();
    numIndices = indices.size();

    glGenVertexArrays(1, &idVAO);
    glGenBuffers(1, &idVBO1); //El VBO para los vertices
    glGenBuffers(1, &idVBO2); //El VBO para los colores
    glGenBuffers(1, &idVBO3); // El VBO para las coord. de textura !!!
    glGenBuffers(1, &idIBO);

    glBindVertexArray(idVAO);

    glBindBuffer(GL_ARRAY_BUFFER, idVBO1);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), posicionVertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0); //Esto es para decir que el contenido que vamos a leer para este VBO ira al "layout = 0" de nuestro vertex shader
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, idVBO2);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), normales.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,3 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, idVBO3);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), coordenadasTextura.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,2 * sizeof(GLfloat), nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices.data(), GL_STATIC_DRAW);
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

GLuint PAG::Malla::getNumIndices() const {
    return numIndices;
}

GLuint PAG::Malla::getNumVertices() const {
    return numVertices;
}

void PAG::Malla::trasladarMalla(glm::mat4 matrizTraslacion) {
    matrizModelado = matrizTraslacion * matrizModelado;
}

void PAG::Malla::rotarMalla(glm::mat4 matrizRotacion) {
    matrizModelado = matrizRotacion * matrizModelado;
}

void PAG::Malla::escalarMalla(glm::mat4 matrizEscalado) {
    matrizModelado = matrizEscalado * matrizModelado;
}
