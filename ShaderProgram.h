//
// Created by secre on 11/10/2024.
//

#ifndef PR1_SHADERPROGRAM_H
#define PR1_SHADERPROGRAM_H

#include <glad/glad.h>
#include "GL/gl.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace PAG{
    class ShaderProgram {
    private:
        GLuint idVS = 0; //Id del vertex shader
        GLuint idFS = 0; //Id del fragment shader
        GLuint idSP = 0; //Id del shader program
        GLuint idVAO = 0; //Id del Vertex Array Object
        GLuint idVBO1 = 0; //Id del Vertex Buffer Object
        GLuint idVBO2 = 0;
        GLuint idIBO = 0; //Id del Index Buffer Object
        std::string nombreFicheros; /// El nombre de los ficheros ( solo parte inicial, EJ: pag03 , y asi sacamos el pag03-vs.glsl y el pag03-fs.glsl ;) )

    public:
        ShaderProgram(std::string &nombreFicheros);
        ~ShaderProgram();
        void ejecutarSP();
        void creaShaderProgram(); ///Este es el que hay que llamar desde fuera
        void creaModelo();

        //Para compilar un shader al completo:
        void crearSP(GLuint &handler);
        std::string leerShaderSource(std::string filename);
        GLuint creaShaderObject(GLenum shaderType);
        void compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType);
        void enlazarSP(GLuint handler, GLuint shaderHandler, std::string filename);
    };
}

#endif //PR1_SHADERPROGRAM_H
