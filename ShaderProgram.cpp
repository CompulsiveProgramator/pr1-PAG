//
// Created by secre on 11/10/2024.
//

#include "ShaderProgram.h"

namespace PAG{
    /**
     * Constructor de la clase
     * @param nombreFicheros
     */
    ShaderProgram::ShaderProgram(std::string &nombreFicheros) {
        this->nombreFicheros = nombreFicheros;
        creaShaderProgram();
    }

    ShaderProgram::~ShaderProgram() {
        if( idVS != 0 )
        {
            glDeleteShader(idVS);
        }

        if( idFS != 0 )
        {
            glDeleteShader(idFS);
        }

        if( idSP != 0 )
        {
            glDeleteProgram(idSP);
        }

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
 * Metodo llamado desde Renderer para ejecutar el shader program
 */
    void ShaderProgram::ejecutarSP() {
        glUseProgram ( idSP );
        ///Hacer esto por cada malla de triangulos jeje
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
    }

/**
     * Métoodo para crear, compilar y enlazar el shader program
     * Con comprobacion de errores
     */
    void ShaderProgram::creaShaderProgram() {
        std::string contenido;
        GLuint shaderHandler; //Para gestionar cada shader object
        std::string filename;

        crearSP(idSP); //Fase 1

        //1o El vertex shader
        filename = "../"+nombreFicheros+"-vs.glsl";
        contenido = leerShaderSource(filename); //Fase 2
        shaderHandler = creaShaderObject(GL_VERTEX_SHADER); //Fase 3
        compilarShaderObject(contenido, shaderHandler, GL_VERTEX_SHADER); //Fase 4
        enlazarSP(idSP, shaderHandler, filename);

        filename = "../"+nombreFicheros+"-fs.glsl";
        contenido = leerShaderSource(filename); //Fase 2
        shaderHandler = creaShaderObject(GL_FRAGMENT_SHADER); //Fase 3
        compilarShaderObject(contenido, shaderHandler, GL_FRAGMENT_SHADER); //Fase 4
        enlazarSP(idSP, shaderHandler, filename); //Fase 5

        creaModelo();
    }

/**
 * 1a fase del compilado del shader program
 * Crear el SP vacio
 * @return
 */
    void ShaderProgram::crearSP(GLuint &handler) {
        handler = glCreateProgram();
        if(handler == 0){
            throw std::string("Cannot create shader program\n");
        }
    }

/**
 * 2 fase del compilado del shader program
 * Abrir y leer el shader source
 * @param filename El nombre del archivo que queremos leer (pag03)
 * @return El string con el contenido del archivo
 */
    std::string ShaderProgram::leerShaderSource(std::string filename) {
        std::ifstream shaderSourceFile(filename);

        if(!shaderSourceFile.is_open()){
            throw std::string("Cannot open shader source file\n");
        }

        std::stringstream shaderSourceStream;
        shaderSourceStream << shaderSourceFile.rdbuf();
        std::string shaderSourceString = shaderSourceStream.str();

        shaderSourceFile.close();

        return shaderSourceString;
    }

/**
 * 3 fase del compilado del shader program
 * Crear el shader object
 * @param shaderType El tipo de objeto (vertex o fragment)
 * @return El id del objeto
 */
    GLuint ShaderProgram::creaShaderObject(GLenum shaderType) {
        GLuint shaderHandler = glCreateShader(shaderType);
        if(shaderHandler == 0){
            throw std::string("Cannot create shader object\n");
        }

        return shaderHandler;
    }

/**
 * 4 fase del compilado del shader program
 * Compilar el shader object
 * @param shaderSourceString El string con el archivo
 * @param shaderHandler El id del objeto
 * @param shaderType El tipo de objeto
 */
    void ShaderProgram::compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType) {
        const char * shaderSourceCString = shaderSourceString.c_str();
        glShaderSource(shaderHandler, 1, &shaderSourceCString, NULL);

        // - Compilar el shader object —————————————————————————
        glCompileShader(shaderHandler);
        GLint compileResult;
        glGetShaderiv(shaderHandler, GL_COMPILE_STATUS, &compileResult);
        if (compileResult == GL_FALSE) {
            GLint logLen = 0;
            std::string logString = "";
            glGetShaderiv(shaderHandler, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetShaderInfoLog(shaderHandler, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                std::stringstream ss;
                ss << shaderType;
                throw std::string("Cannot compile shader " + ss.str() + logString + "\n");
            }
        }
    }


/**
 * 5 fase del compilado del shader program
 * Enlazar el shader object al shader program
 * @param handler El id del shader program
 * @param shaderHandler El id del shader object
 * @param filename El nombre del shader
 */
    void ShaderProgram::enlazarSP(GLuint handler, GLuint shaderHandler, std::string filename) {
        glAttachShader(handler, shaderHandler);

        glLinkProgram(handler);
        GLint linkSuccess = 0;
        glGetProgramiv(handler, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            std::string logString = "";
            GLint logLen = 0;
            glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logLen);
            if (logLen > 0) {
                char * cLogString = new char[logLen];
                GLint written = 0;
                glGetProgramInfoLog(handler, logLen, &written, cLogString);
                logString.assign(cLogString);
                delete[] cLogString;
                throw std::string("Cannot link shader" + filename + "\n" + logString + "\n");
            }
        }
    }

/**
 * Metodo para crear el VAO para el modelo a renderizar
 */
    void ShaderProgram::creaModelo() {
        //Los vertices con sus posiciones (x,y,z) en un VBO no entrelazado (solo posicion)
        GLfloat posicionVerticeColor[] = { -0.5, -0.5, 0.0,1.0, 0.0, 0.0,
                                           0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
                                           0.0, 0.5, 0.0, 0.0, 0.0, 1.0};

        /*
        //Otro vbo pero para el color de cada vertice
        GLfloat colorVertices[] = { 1.0, 0.0, 0.0,
                                    0.0, 1.0, 0.0,
                                    0.0, 0.0, 1.0};
        */

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
}

