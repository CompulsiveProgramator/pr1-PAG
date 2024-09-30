//
// Created by secre on 27/09/2024.
//

#include <glad/glad.h>
#include <GL/gl.h>
#include "Renderer.h"

namespace PAG
{
    Renderer* PAG::Renderer::instancia = nullptr;

    Renderer::Renderer(GLFWwindow *window) {
        this->window = window;
    }

    /**
     * Constructor por defecto vacio
     */
    Renderer::Renderer() {
        glEnable ( GL_DEPTH_TEST ); //Para decirle a Open GL que use la profundidad ejej

        // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
        // 3D construido.
        std::cout << glGetString ( GL_RENDERER ) << std::endl
                  << glGetString ( GL_VENDOR ) << std::endl
                  << glGetString ( GL_VERSION ) << std::endl
                  << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

        for(int i = 0 ; i < 4; i++){
            colorFondo[i] = 0.0;
        }
    }

    Renderer::~Renderer() {

    }

    /**
    * Metodo para obtener la instancia de la clase
    * @return
    */
    Renderer *PAG::Renderer::getInstancia(GLFWwindow *window) {
        if(!instancia){
            instancia = new Renderer(window);
        }
        return instancia;
    }

    /**
     * Metodo para refrescar la ventana
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(colorFondo[0], colorFondo[1], colorFondo[2], colorFondo[3]);
    }

    /**
     * Funcion callback llamada cuando haya un error en GLFW
     * @param _errno
     * @param desc
     */
    void Renderer::error_callback(int errno, const char *desc) {
        std::string aux (desc);
        std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
    }

    /**
     * Funcion callback llamada para refrescar la ventana
     * @param window
     */
    void Renderer::window_refresh_callback(GLFWwindow *window) {
        instancia->refrescar();
        glfwSwapBuffers(window); //La funcion para intercambiar los buffers, y que no haya parpadeo

        PAG::GUI::getInstancia(window)->postEntradaLog("El callback de refrescar ventana fue llamado\n");
    }

    /**
     * Callback llamado cuando se cambie el tamaño de la ventana de la aplicacion
     * @param window
     * @param width
     * @param height
     */
    void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        PAG::GUI::getInstancia(window)->postEntradaLog("El callback de escalado de ventana fue llamado\n");
    }

    /**
     * Callback llamado cuando se pulse una tecla
     * @param window
     * @param key
     * @param scancode
     * @param action
     * @param mods
     */
    void Renderer::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
        if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        PAG::GUI::getInstancia(window)->postEntradaLog("Key callback called\n");
    }

    /**
     * Callback llamado cuando pulsemos un boton sobre la pantalla de la app
     * @param window
     * @param button
     * @param action
     * @param mods
     */
    void Renderer::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
        if ( action == GLFW_PRESS )
        {
            std::string cad = "Pulsado el boton: ";
            cad.push_back(char(button + 48)); //Para hacer la conversion a caracter
            PAG::GUI::getInstancia(window)->postEntradaLog(cad);
        }
        else if ( action == GLFW_RELEASE )
        {
            std::string cad = "Soltado el boton: ";
            cad.push_back(char(button + 48)); //Para hacer la conversion a caracter
            PAG::GUI::getInstancia(window)->postEntradaLog(cad);
        }
    }

    /**
     * Callback llamado cuando giremos la rueda del raton
     * @param window
     * @param xoffset
     * @param yoffset
     */
    void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        std::string cad;
        //Para convertir de int,float,double a string, usar std::to_string(). Se puede usar desde C++ 11
        cad = "Movida la rueda del raton" + std::to_string(xoffset) + " unidades en horizontal y " + std::to_string(yoffset) + " unidades en vertical\n";
        PAG::GUI::getInstancia(window)->postEntradaLog(cad);
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
}