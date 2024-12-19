//
// Created by secre on 11/10/2024.
//

#include "glad/glad.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "exception"
#include "ShaderProgram.h"

namespace PAG{
    /**
     * Constructor de la clase
     * @param nombreFicheros
     */
    ShaderProgram::ShaderProgram(std::string &nombreFicheros, Camara *camara): modelos(), luces() {
        this->nombreFicheros = nombreFicheros;
        this->camara = camara;
        creaShaderProgram();

        luces.push_back(Luz(AMBIENTAL));
        luces.push_back(Luz(PUNTUAL));
        //luces.push_back(Luz(DIRECCIONAL));

        //luces.push_back(Luz(FOCAL));
        //GLfloat dirNuevaFoco[3] = {0, -1, 0};
        //GLfloat posNuevaFoco[3] = {0, 2, -2};
        //luces[3].setDireccion(dirNuevaFoco);
        //luces[3].setPosicion(posNuevaFoco);
    }

    ShaderProgram::~ShaderProgram() {
        if( idSP != 0 )
        {
            glDeleteProgram(idSP);
        }

        if( idTextura != 0)
        {
            glDeleteTextures(1, &idTextura);
        }

        for(int i = 0 ; i < modelos.size() ; i++){
            delete modelos[i];
        }
    }

/**
 * Metodo llamado desde Renderer para ejecutar el shader program
 */
    void ShaderProgram::ejecutarSP() {
        try{
            if(modelos.size() == 0){
                return;
            }

            static bool primeraVez = true;
            if(primeraVez){
                activarTextura();
                primeraVez = false;
            }

            /// Un bucle para pintar cada modelo
            for(int i = 0 ; i < modelos.size() ; i++){
                glm::mat4 matrizModelado = modelos[i]->getMalla()->getMatrizModelado();
                glm::mat4 matrizModeladoVision = camara->getMatrizVision() * matrizModelado;
                glm::mat4 matrizModeladoVisionPerspectiva = camara->getMatrizPerspectiva() * matrizModeladoVision;
                glUseProgram ( idSP );

                // Asignamos el muestreador del shader program a la unidad de textura 0
                GLint posicion = glGetUniformLocation ( idSP, "muestreador" );
                glUniform1i ( posicion, 0 );

                // Activamos la unidad de textura 0, y le asociamos la textura que habíamos configurado
                glActiveTexture ( GL_TEXTURE0 );
                glBindTexture ( GL_TEXTURE_2D, idTextura );

                pasarUniformMV(matrizModeladoVision);

                pasarUniformMVP(matrizModeladoVisionPerspectiva);

                elegirModoVisualizacion();

                /// Pr 8 Iluminacion

                /// Un bucle para cada luz:
                for(int j = 0 ; j < luces.size() ; j++)
                {
                    GLuint pos;

                    std::string colorAmbienteLuz("Ia");
                    std::string colorAmbienteMaterial("Ka");
                    std::string p("lightPosition");
                    std::string direccion("direccion");
                    std::string Id("Id");
                    std::string Is("Is");
                    std::string Kd("Kd");
                    std::string Ks("Ks");
                    std::string exponenteEspecular("exponenteEspecular");
                    std::string angulo("angulo");

                    pos = glGetUniformLocation(idSP, direccion.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, luces[j].getDireccion());
                    }

                    pos = glGetUniformLocation(idSP, Id.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, luces[j].getId());
                    }

                    pos = glGetUniformLocation(idSP, Is.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, luces[j].getIs());
                    }

                    pos = glGetUniformLocation(idSP, Kd.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, modelos[i]->getMaterial()->getKd());
                    }

                    pos = glGetUniformLocation(idSP, Ks.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, modelos[i]->getMaterial()->getKs());
                    }

                    pos = glGetUniformLocation(idSP, exponenteEspecular.c_str());
                    if(pos != -1)
                    {
                        glUniform1f(pos, luces[j].getExponenteEspecular());
                    }

                    pos = glGetUniformLocation(idSP, colorAmbienteLuz.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, luces[j].getIa());
                    }

                    pos = glGetUniformLocation(idSP, colorAmbienteMaterial.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, modelos[i]->getMaterial()->getKa());
                    }

                    pos = glGetUniformLocation(idSP, p.c_str());
                    if(pos != -1)
                    {
                        glUniform3fv(pos, 1, luces[j].getPosicion());
                    }

                    pos = glGetUniformLocation(idSP, angulo.c_str());
                    if(pos != -1)
                    {
                        glUniform1f(pos, luces[j].getAnguloApertura());
                    }

                    if(luces[j].getTipoLuz() == AMBIENTAL)
                    {
                        GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "luzAmbiental");

                        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
                    }
                    else if(luces[j].getTipoLuz() == PUNTUAL)
                    {
                        GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "luzPuntual");

                        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
                    }else if(luces[j].getTipoLuz() == DIRECCIONAL)
                    {
                        GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "luzDireccional");

                        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
                    }else if(luces[j].getTipoLuz() == FOCAL)
                    {
                        GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "luzFocal");

                        glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
                    }

                    if(j == 0)
                    {
                        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                    }else{
                        glBlendFunc(GL_ONE, GL_ONE);
                    }


                    ///Se dibuja una vez por cada luz ;)
                    glBindVertexArray ( modelos[i]->getMalla()->getIdVao() );
                    glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, modelos[i]->getMalla()->getIdIbo() );
                    glDrawElements ( GL_TRIANGLES, modelos[i]->getMalla()->getNumIndices(), GL_UNSIGNED_INT, nullptr);
                }
            }

        }catch (std::exception &e)
        {
            std::cout << e.what();
        }
    }

    /**
     * Métoodo para crear, compilar y enlazar el shader program
     * Con comprobacion de errores
     */
    void ShaderProgram::creaShaderProgram() {
        std::string contenido;
        std::string filename = nombreFicheros;
        GLuint vertexShaderId, fragmentShaderId;
        crearSP(idSP); //Fase 1

        vertexShaderId = creaShaderObject(GL_VERTEX_SHADER);
        contenido = leerShaderSource("../shader_files/"+filename+"-vs.glsl");
        compilarShaderObject(contenido, vertexShaderId, GL_VERTEX_SHADER);

        fragmentShaderId = creaShaderObject(GL_FRAGMENT_SHADER);
        contenido = leerShaderSource("../shader_files/"+filename+"-fs.glsl");
        compilarShaderObject(contenido, fragmentShaderId, GL_FRAGMENT_SHADER);

        glAttachShader(idSP, vertexShaderId);
        glAttachShader(idSP, fragmentShaderId);
        enlazarSP(idSP, filename);
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
 * Enlazar el shader program
 * @param handler El id del shader program
 * @param filename El nombre del shader
 */
    void ShaderProgram::enlazarSP(GLuint handler, std::string filename)
    {
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

    void ShaderProgram::setModoVisualizacion(ModosVisualizacion modo) {
        modoVisualizacion = modo;
    }

    /**
     * Metodo para elegir el modo de visualizacion a renderizar
     */
    void ShaderProgram::elegirModoVisualizacion() {
        if(modoVisualizacion == ALAMBRE){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            //Para obtener el id de la implementacion dada
            GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "colorRojo");
            /*
             * Activamos la implementacion con su id obtenido arriba ;)
             * el parametro "count" es para decir de cuantas subrutinas elegimos la implementacion
             */
            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
        }else if(modoVisualizacion == SOLIDO){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            GLuint aux = glGetSubroutineIndex(idSP, GL_FRAGMENT_SHADER, "colorSolido");

            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &aux);
        }
    }

    /**
     * Metodo para pasar al shader program la matriz de modelado y vision
     * @param matrizMV La matriz de modelado y vision
     */
    void ShaderProgram::pasarUniformMV(glm::mat4 &matrizModeladoVision) {
        //Para pasar un uniform al vertex shader
        std::string matrizMV("matrizModeladoVision"); ///La matriz con la transformacion de modelado del objeto, y la de vision
        GLint pos = glGetUniformLocation(idSP, matrizMV.c_str());
        if(pos != -1){
            glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVision[0][0]);
        }
    }

    /**
     * Metodo para pasar al shader program la matriz de modelado, vision y perspectiva
     * @param matrizMVP La matriz de modelado, vision y perspectiva
     */
    void ShaderProgram::pasarUniformMVP(glm::mat4 &matrizModeladoVisionPerspectiva) {
        std::string matrizMVP("matrizModeladoVisionPerspectiva");
        GLuint pos = glGetUniformLocation(idSP, matrizMVP.c_str());
        if(pos != -1){
            glUniformMatrix4fv(pos, 1, GL_FALSE, &matrizModeladoVisionPerspectiva[0][0]);
        }
    }

    /**
     * Metodo auxiliar para cargar y usar la textura, que se encuentra en el material asociado
     */
    void ShaderProgram::activarTextura() {
        std::vector<unsigned char> imagen = modelos[0]->getMaterial()->getImagenTextura(); // Se lee la imagen de la vaquita!
        unsigned ancho, alto; // El ancho y alto de la imagen (en pixels)

        std::cout << imagen.size(); /// La imagen se lee bien!

        ancho = modelos[0]->getMaterial()->getTextura()->getAncho();
        alto = modelos[0]->getMaterial()->getTextura()->getAlto();
        glGenTextures ( 1, &idTextura );
        glBindTexture ( GL_TEXTURE_2D, idTextura );

        // Cómo resolver la minificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        // Cómo resolver la magnificación. En este caso, le decimos que utilice mipmaps, y que aplique interpolación lineal
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        // Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en horizontal
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        // Cómo pasar de coordenadas de textura a coordenadas en el espacio de la textura en vertical
        glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        // Transferimos la información de la imagen. En este caso, la imagen está guardada en std::vector<unsigned char> _pixels;
        glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagen.data () );

        // Generamos el mimMap
        glGenerateMipmap(idTextura); //siiiiiiiii vale
    }
}

