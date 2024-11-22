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
    Renderer::Renderer():shaderProgram(nullptr), colorFondo() {
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

        ///Creamos una camara por defecto:
        this->camara = new Camara(glm::vec3(0,0,1), glm::vec3(0,0,-1), glm::radians(90.0f), glm::float32(2), glm::float32(1), glm::float32(3));
    }

    /**
     * Destructor de la clase
     */
    Renderer::~Renderer() {
        if(shaderProgram){
            delete shaderProgram;
        }

        if(camara){
            delete camara;
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

        if(shaderProgram){
            shaderProgram->ejecutarSP();
        }
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
     * Funcion para pasar de coordenadas de mundo virtual, a las de la pantalla de mi ordenador ( o del tuyo si lo ejecutas en el tuyo)
     * @param width
     * @param height
     */
    void Renderer::modificarTamañoVentana(int width, int height) {
        glViewport(0, 0, width, height);
    }

    /**
     * Funcion para establecer el nombre del Shader Program
     * @param nombreF El nombre del archivo
     */
    void Renderer::setNombreShaderProgram(std::string nombreF) {
        nombreSP = nombreF;
        this->shaderProgram = new ShaderProgram(nombreF, camara);
    }

    /**
     * Getter de la camara
     * @return
     */
    Camara *Renderer::getCamara() {
        return camara;
    }

    /**
     * Metodo para seleccionar el modelo amooo
     */
    void Renderer::seleccionarModelo(std::string localizacionArchivo) {
        shaderProgram->setModelo(localizacionArchivo);
    }
}