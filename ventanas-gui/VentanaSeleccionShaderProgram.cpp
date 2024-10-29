//
// Created by secre on 29/10/2024.
//

#include "VentanaSeleccionShaderProgram.h"

/**
 * Constructor por defecto de la clase
 */
PAG::VentanaSeleccionShaderProgram::VentanaSeleccionShaderProgram():botonPulsado(false), nombreShaderProgram() {

}

/**
 * Funcion para mostrar la ventana de selección del shader program, donde se escribe su nombre para activarlo
 */
void PAG::VentanaSeleccionShaderProgram::refrescarVentana() {
    ImGui::SetNextWindowPos(ImVec2(10, 300), ImGuiCond_Once);
    ImGui::Begin("Seleccionar shader program");
    ImGui::Text("Dime el nombre del shader program:");
    ImGui::Text("Formato 'pag0x'");
    ImGui::InputText("##", &nombreShaderProgram, ImGuiInputTextFlags_AutoSelectAll);
    botonPulsado = ImGui::Button("Load");
    ImGui::End();
}

const std::string &PAG::VentanaSeleccionShaderProgram::getNombreShaderProgram() const {
    return nombreShaderProgram;
}

bool PAG::VentanaSeleccionShaderProgram::isBotonPulsado() const {
    return botonPulsado;
}
