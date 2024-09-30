//
// Created by secre on 28/09/2024.
//
// Enlace al manual interactivo de ImGui:
// https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html

#ifndef PR1_GUI_H
#define PR1_GUI_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

namespace PAG
{
    /**
     * Clase segun patron SINGLETON para gestionar las ventanas de la interfaz grafica
     * Muy chula para controlar variables de nuestra aplicacion ;)
     */
    class GUI {
    private:
        static GUI* instancia;

        GUI(GLFWwindow *window);
    public:
        virtual ~GUI();
        static GUI* getInstancia(GLFWwindow *window);
        void refrescar();
    };
}



#endif //PR1_GUI_H
