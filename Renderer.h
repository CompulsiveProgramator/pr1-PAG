//
// Created by secre on 27/09/2024.
//

#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <iostream>
#include <GLFW/glfw3.h>
#include "GUI.h"

///El espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG{
    /**
     * Clase que sigue el patron SINGLETON para renderizar
     */
    class Renderer {
    private:
        static Renderer* instancia; //Para el patron Singleton
        Renderer();
        GLfloat colorFondo[4];
        GLFWwindow *window;
        GLuint idVS = 0; //Id del vertex shader
        GLuint idFS = 0; //Id del fragment shader
        GLuint idSP = 0; //Id del shader program
        GLuint idVAO = 0; //Id del Vertex Array Object
        GLuint idVBO = 0; //Id del Vertex Buffer Object
        GLuint idIBO = 0; //Id del Index Buffer Object

        Renderer(GLFWwindow *window);
    public:
        virtual ~Renderer();
        static Renderer* getInstancia(GLFWwindow *window); //Para obtener la instancia desde fuera
        void refrescar();
        GLfloat *getColorFondo();
        void setColorFondo(const GLfloat color[4]);

        //Todos los metodos callbacks del main de la Pr1:
        static void error_callback ( int errno, const char* desc );
        static void window_refresh_callback ( GLFWwindow *window );
        static void framebuffer_size_callback ( GLFWwindow *window, int width, int height );
        static void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods );
        static void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods );
        static void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset );

        void creaShaderProgram();
    };
}



#endif //PR1_RENDERER_H
