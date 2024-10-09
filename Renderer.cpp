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
        glEnable ( GL_DEPTH_TEST ); //Para decirle a Open GL que use la profundidad

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

    Renderer::~Renderer() {

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
     * @note Sin comprobación de errores todo
     */
    void Renderer::creaShaderProgram() {
        //Escribimos los shaders en un string:

        /**
         * El vertex shader no hace ningun procesado a la geometría,
         * porque ya se la  pasamos procesada
         */
        std::string miVertexShader =
                "#version 410\n"
                "layout (location = 0) in vec3 posicion;\n"
                "void main ()\n"
                "{ gl_Position = vec4 ( posicion, 1 );\n"
                "}\n";

        std::string miFragmentShader =
                "#version 410\n"
                "out vec4 colorFragmento;\n"
                "void main ()\n"
                "{ colorFragmento = vec4 ( 1.0, .4, .2, 1.0 );\n"
                "}\n";

        idVS = glCreateShader( GL_VERTEX_SHADER );
        const GLchar* fuenteVS = miVertexShader.c_str();
        glShaderSource ( idVS, 1, &fuenteVS, nullptr);
        glCompileShader( idVS);

        idFS = glCreateShader ( GL_FRAGMENT_SHADER);
        const GLchar* fuenteFS = miFragmentShader.c_str();
        glShaderSource (idFS, 1, &fuenteFS, nullptr); //Le decimos donde esta el shader
        glCompileShader (idFS); //Y lo compilamos ;)

        idSP = glCreateProgram(); //Creamos el shader program
        glAttachShader (idSP, idVS); //Y le metemos los shaders!
        glAttachShader ( idSP, idFS);
        glLinkProgram (idSP); //Activamos el programa
    }

    /**
     * Metodo para crear el VAO para el modelo a renderizar
     * @note No se usa ninguna comprobacion de errores todo
     */
    void Renderer::creaModelo() {
        //Los vertices con sus posiciones (x,y,z) en un VBO no entrelazado
        GLfloat vertices[] = { -.5, -.5, 0,
                               .5, -.5, 0,
                               .0, .5, 0};

        GLuint indices[] = {0, 1, 2}; //Los datos del bonito IBO

        glGenVertexArrays ( 1, &idVAO); //Creamos el VAO
        glBindVertexArray ( idVAO);

        glGenBuffers ( 1, &idVBO); //Creamos el VBO
        glBindBuffer (GL_ARRAY_BUFFER, idVBO);
        glBufferData( GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vertices, GL_STATIC_DRAW); //Le indicamos donde estan los datos
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr); //Le decimos como recorrer el VBO
        glEnableVertexAttribArray(0);

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