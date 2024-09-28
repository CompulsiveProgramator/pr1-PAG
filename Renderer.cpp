//
// Created by secre on 27/09/2024.
//

#include <glad/glad.h>
#include <GL/gl.h>
#include "Renderer.h"

namespace PAG
{
    Renderer* PAG::Renderer::instancia = nullptr;

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
    }

    Renderer::~Renderer() {

    }

    /**
    * Metodo para obtener la instancia de la clase
    * @return
    */
    Renderer *PAG::Renderer::getInstancia() {
        if(!instancia){
            instancia = new Renderer();
        }
        return instancia;
    }

    /**
     * Metodo para refrescar la ventana
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(1.0, 0.0, 0.0, 1.0);
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
        std::cout << "El callback de refrescar ventana fue llamado" << std::endl;
    }

    /**
     * Callback llamado cuando se cambie el tamaño de la ventana de la aplicacion
     * @param window
     * @param width
     * @param height
     */
    void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
        std::cout << "El callback de escalado de ventana fue llamado";
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
        std::cout << "Key callback called" << std::endl;
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
            std::cout << "Pulsado el boton: " << button << std::endl;
        }
        else if ( action == GLFW_RELEASE )
        {
            std::cout << "Soltado el boton: " << button << std::endl;
        }
    }

    /**
     * Callback llamado cuando giremos la rueda del raton
     * @param window
     * @param xoffset
     * @param yoffset
     */
    void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        std::cout << "Movida la rueda del raton " << xoffset
                  << " Unidades en horizontal y " << yoffset
                  << " unidades en vertical" << std::endl;
    }
}




