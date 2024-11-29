//
// Created by secre on 11/10/2024.
//

#include "ShaderProgram.h"

namespace PAG{
    /**
     * Constructor de la clase
     * @param nombreFicheros
     */
    ShaderProgram::ShaderProgram(std::string &nombreFicheros, Camara *camara): modelos() {
        this->nombreFicheros = nombreFicheros;
        this->camara = camara;
        creaShaderProgram();
    }

    ShaderProgram::~ShaderProgram() {
        if( idSP != 0 )
        {
            glDeleteProgram(idSP);
        }

        for(int i = 0 ; i < modelos.size() ; i++){
            delete modelos[i];
        }
    }

/**
 * Metodo llamado desde Renderer para ejecutar el shader program
 */
    void ShaderProgram::ejecutarSP() {
        if(modelos.size() == 0){
            return;
        }

        for(int i = 0 ; i < modelos.size() ; i++){
            glm::mat4 matrizModelado = modelos[i]->getMalla()->getMatrizModelado();
            glm::mat4 matrizModeladoVision = camara->getMatrizVision() * matrizModelado;
            glm::mat4 matrizModeladoVisionPerspectiva = camara->getMatrizPerspectiva() * matrizModeladoVision;
            glUseProgram ( idSP );

            ///Hacer esto por cada malla de triangulos:

            //Para pasar un uniform al vertex shader
            std::string matrizMV("matrizModeladoVision"); ///La matriz con la transformacion de modelado del objeto, y la de vision
            GLint pos = glGetUniformLocation(idSP, matrizMV.c_str());
            if(pos != -1){
                glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVision[0][0]);
            }

            std::string matrizMVP("matrizModeladoVisionPerspectiva");
            pos = glGetUniformLocation(idSP, matrizMVP.c_str());
            if(pos != -1){
                glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVisionPerspectiva[0][0]);
            }

            glBindVertexArray ( modelos[i]->getMalla()->getIdVao() );
            glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, modelos[i]->getMalla()->getIdIbo() );
            glDrawElements ( GL_TRIANGLES, modelos[i]->getMalla()->getNumIndices(), GL_UNSIGNED_INT, nullptr);
        }

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
        filename = "../shader_files/"+nombreFicheros+"-vs.glsl";
        contenido = leerShaderSource(filename); //Fase 2
        shaderHandler = creaShaderObject(GL_VERTEX_SHADER); //Fase 3
        compilarShaderObject(contenido, shaderHandler, GL_VERTEX_SHADER); //Fase 4
        enlazarSP(idSP, shaderHandler, filename);

        filename = "../shader_files/"+nombreFicheros+"-fs.glsl";
        contenido = leerShaderSource(filename); //Fase 2
        shaderHandler = creaShaderObject(GL_FRAGMENT_SHADER); //Fase 3
        compilarShaderObject(contenido, shaderHandler, GL_FRAGMENT_SHADER); //Fase 4
        enlazarSP(idSP, shaderHandler, filename); //Fase 5
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
     * Metodo para pasarle el nombre del modelo al shader program
     * @param localizacion
     */
    void ShaderProgram::agregarModelo(std::string localizacion) {
        modelos.push_back(new Modelo(localizacion));
    }

    std::vector<Modelo *> *ShaderProgram::getModelos() {
        return &modelos;
    }

    /**
     * Metodo para eliminar el modelo en la posicion dada
     * //ToDo Cuando se borran todos los elementos, la ventana de ImGui de transformacion de modelos deja de mostrarse aunque luego se agregen mas modelos ( puede ser porque al vaciar el vector este sea "null" )
     * //Todo y el puntero al vector de modelos de la ventana, no se actualiza
     * @param posicion La posicion a borrar
     */
    void ShaderProgram::eliminarModelo(unsigned int posicion) {
        if(posicion >= modelos.size())
        {
            return;
        }

        // Si queremos borrar el ultimo elemento
        if(posicion == modelos.size() - 1)
        {
            //Cuando tenemos un vector de punteros, y usamos std::vector<>::erase(), solo se pone a nullptr el puntero, no se hace delete ;)

            delete modelos[posicion];
            modelos.erase(modelos.end()--);
        }else{ //Si queremos borrar otro elemento
            std::cout << "Se solicita borrar el modelo en la posicion " << posicion << std::endl;

            delete modelos[posicion];

            auto iterador = modelos.begin();
            for(int i = 0 ; i < posicion ; i++){
                iterador++;
            }

            modelos.erase(iterador);
        }
    }
}

