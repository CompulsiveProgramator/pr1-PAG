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
#include <vector>
#include <iostream>
#include "GL/gl.h" //Solo para el color de fondo de la ventana de color

namespace PAG
{
    /**
     * Clase segun patron SINGLETON para gestionar la interfaz gráfica de usuario (la GUI para los ingleses ;))
     */
    class GUI {
    private:
        static GUI* instancia;
        GUI();
        GLfloat *color;
        std::vector<std::string> log;
        std::string nameFile;
        bool buttonPressed;

        void pintarVentanaColor();
    public:
        virtual ~GUI();
        static GUI& getInstancia();
        void refrescar(); //Metodo para pintar la ventana

        //Para la ventana de color:
        void setColor(GLfloat *_color);
        void agregarMensaje(std::string& cad);
        std::string getNameFile();
        bool getButtonPressed();
    };
}



#endif //PR1_GUI_H
