//
// Created by secre on 27/09/2024.
//

#include "Renderer.h"

namespace PAG
{
    Renderer* PAG::Renderer::instancia = nullptr;

    /**
     * Constructor por defecto vacio
     */
    Renderer::Renderer() {
        // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
        // 3D construido.
        std::cout << glGetString ( GL_RENDERER ) << std::endl
                  << glGetString ( GL_VENDOR ) << std::endl
                  << glGetString ( GL_VERSION ) << std::endl
                  << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

        for(int i = 0 ; i < 3; i++){
            colorFondo[i] = 0.0; //El color inicial es negro
        }
        colorFondo[3] = 1.0; //Para que se vea el color completo
    }

    /**
     * Destructor de la clase
     */
    Renderer::~Renderer() {
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

        if( idVBO != 0 )
        {
            glDeleteBuffers( 1, &idVBO);
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
    * Metodo para obtener la instancia de la clase
    * @return Una "referencia" a la instancia, para no usar un puntero directamente desde fuera
    */
    Renderer& PAG::Renderer::getInstancia() {
        if(instancia == nullptr){ //Lazy initialization, se crea cuando se necesite
            instancia = new Renderer();
        }
        return *instancia;
    }

    /**
     * Metodo para refrescar la ventana
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);

        glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );

        glUseProgram ( idSP );
        ///Hacer esto por cada malla de triangulos jeje
        glBindVertexArray ( idVAO );
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, idIBO );
        glDrawElements ( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );
    }

    /**
     * Getter del color de fondo
     * @return
     */
    GLfloat *Renderer::getColorFondo(){
        return colorFondo;
    }

    /**
     * Setter del color de fondo
     * @param color El color
     */
    void Renderer::setColorFondo(const GLfloat color[4]) {
        for(int i = 0 ; i < 4 ; i++){
            colorFondo[i] = color[i];
        }
    }

    /**
     * Métoodo para crear, compilar y enlazar el shader program
     * Con comprobacion de errores
     */
    void Renderer::creaShaderProgram() {
        std::string contenido;
        GLuint shaderHandler; //Para gestionar cada shader object
        std::string filename;

        crearSP(idSP); //Fase 1

        //1o El vertex shader
        filename = "C:\\Users\\secre\\OneDrive\\Escritorio\\pag03-vs.glsl";
        contenido = leerShaderSource(filename); //Fase 2
        shaderHandler = creaShaderObject(GL_VERTEX_SHADER); //Fase 3
        compilarShaderObject(contenido, shaderHandler, GL_VERTEX_SHADER); //Fase 4
        enlazarSP(idSP, shaderHandler, filename);

        filename = "C:\\Users\\secre\\OneDrive\\Escritorio\\pag03-fs.glsl";
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
    void Renderer::crearSP(GLuint &handler) {
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
    std::string Renderer::leerShaderSource(std::string filename) {
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
    GLuint Renderer::creaShaderObject(GLenum shaderType) {
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
    void Renderer::compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType) {
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
    void Renderer::enlazarSP(GLuint handler, GLuint shaderHandler, std::string filename) {
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
    void Renderer::creaModelo() {
        //Los vertices con sus posiciones (x,y,z) en un VBO no entrelazado (solo posicion)
        GLfloat vertices[] = { -.5, -.5, 0,
                               .5, -.5, 0,
                               .0, .5, 0};

        GLuint indices[] = {0, 1, 2}; //Los datos del bonito IBO

        glGenVertexArrays ( 1, &idVAO); //Creamos el VAO
        glBindVertexArray ( idVAO); //Enlazamos el VAO para poder usarlo, a partir de aqui todas las operaciones sobre VAOs seran sobre este VAO

        glGenBuffers ( 1, &idVBO); //Creamos el VBO
        glBindBuffer (GL_ARRAY_BUFFER, idVBO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr); //Le decimos como recorrer el VBO
        glBufferData( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW); //Le indicamos donde estan los datos

        glGenBuffers (1, &idIBO); //Creamos el IBO
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(GLuint), indices, GL_STATIC_DRAW); //Le pasamos los datos al IBO
    }

    /**
     * Metodo para inicializar los parametros globales de OpenGL
     */
    void Renderer::inicializaOpenGL(){
        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glPrimitiveRestartIndex(0xFFFF);
        glEnable(GL_PRIMITIVE_RESTART);

        glEnable(GL_PROGRAM_POINT_SIZE);
        glEnable(GL_MULTISAMPLE);
    }

    /**
     * Funcion para pasar de coordenadas de mundo virtual, a las de la pantalla tan guay de mi ordenador ( o del tuyo si lo ejecutas en el tuyo)
     * @param width
     * @param height
     */
    void Renderer::modificarTamañoVentana(int width, int height) {
        glViewport(0, 0, width, height);
    }
}