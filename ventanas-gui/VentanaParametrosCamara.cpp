//
// Created by secre on 01/12/2024.
//

#include "iostream"
#include "VentanaParametrosCamara.h"

/**
 * Metodo para visualizar la ventana de parametros de camara
 */
void PAG::VentanaParametrosCamara::refrescarVentana() {
    if(camara == nullptr)
    {
        return;
    }

    ImGui::SetNextWindowPos(ImVec2 (500, 400), ImGuiCond_Once );

    glm::vec3 posicion = camara->getPosicion();
    float x = posicion[0];
    float y = posicion[1];
    float z = posicion[2];

    ImGui::Begin("Ventana de parametros de camara");
    ImGui::Text("Posición");
    ImGui::Text("X");
    ImGui::Text(std::to_string(x).c_str());
    ImGui::Text("Y");
    ImGui::Text(std::to_string(y).c_str());
    ImGui::Text("Z");
    ImGui::Text(std::to_string(z).c_str());
    ImGui::End();
}

/**
 * Constructor de la ventana
 */
PAG::VentanaParametrosCamara::VentanaParametrosCamara() {

}

/**
 * Metodo para asignarle la camara a la ventana
 * @param _camara La camara de la escena
 */
void PAG::VentanaParametrosCamara::asociarCamara(PAG::Camara *_camara) {
    camara = _camara;
}
