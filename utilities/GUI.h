//
// Created by secre on 28/09/2024.
//
// Enlace al manual interactivo de ImGui:
// https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html

#ifndef PR1_GUI_H
#define PR1_GUI_H

//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
//#include <vector>
//#include <iostream>
//#include "GL/gl.h" //Solo para el color de fondo de la ventana de color
#include "../ventanas-gui/VentanaSeleccionColor.h"
#include "../ventanas-gui/VentanaLog.h"
#include "../ventanas-gui/VentanaSeleccionShaderProgram.h"
#include "../ventanas-gui/VentanaMovimientoCamara.h"
#include "../ventanas-gui/VentanaSelectorModelo.h"
#include "../ventanas-gui/VentanaTransformacionesModelos.h"
#include "../ventanas-gui/VentanaParametrosCamara.h"
//#include "Camara.h"

namespace PAG
{
    /**
     * Clase segun patron SINGLETON para gestionar la interfaz gráfica de usuario (la GUI para los ingleses ;))
     */
    class GUI {
    private:
        static GUI* instancia;
        GUI();
        VentanaSeleccionColor ventanaSeleccionColor;
        VentanaLog ventanaLog;
        VentanaSeleccionShaderProgram ventanaSeleccionShaderProgram;
        VentanaMovimientoCamara ventanaMovimientoCamara;
        VentanaSelectorModelo ventanaSelectorModelo;
        VentanaTransformacionesModelos ventanaTransformacionesModelos;
        VentanaParametrosCamara ventanaParametrosCamara;

        void pintarGUI();
    public:
        virtual ~GUI();
        static GUI& getInstancia();
        void refrescar(); //Metodo para pintar la ventana
        void agregarMensajeLog(std::string &cad);
        std::string getNombreShaderProgram();
        bool getBotonPulsado();
        void setColor(GLfloat *color);
        void asociarCamara(Camara *camara);
        std::string getLocalizacionArchivo();
        void asociarModelos(std::vector<Modelo*> *modelos);
        bool getSeguirRaton();
        bool getEliminarModelo();
        unsigned int getPosicionModeloEliminar();
        void mostrarShaderActivo();
    };
}



#endif //PR1_GUI_H
