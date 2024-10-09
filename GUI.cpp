//
// Created by secre on 28/09/2024.
//

#include "GUI.h"

PAG::GUI* PAG::GUI::instancia = nullptr; //Para inicializar la instancia como nula

/**
 * Constructor por defecto de la clase, que inicializa toodo para que ImGui funcione
 * @param window Es la ventana sobre la que se pintará la GUI
 */
PAG::GUI::GUI(): log(){
}

/**
 * Destructor de la clase, que libera los recursos de GUI
 */
PAG::GUI::~GUI() {

}

/**
 * Metodo para obtener la unica instancia de la clase
 * @return
 */
PAG::GUI &PAG::GUI::getInstancia() {
    if(!instancia){
        instancia = new GUI();
    }

    return *instancia;
}

/**
 * Metodo para refrescar la ventana
 */
void PAG::GUI::refrescar() {
    pintarVentanaColor();
}

void PAG::GUI::pintarVentanaColor() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Ventana para pillar el color de fondo:
    ImGui::SetNextWindowPos ( ImVec2 (10, 10), ImGuiCond_Once );
    ImGui::Begin("Color picker del fondo");
    float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.80f;
    ImGui::SetNextItemWidth(w);
    ImGui::Text("Selecciona el color de fondo:");
    ImGui::ColorPicker3("##MyColor##6", (float*) color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
    ImGui::End();

    //Ventana del log:
    ImGui::SetNextWindowPos ( ImVec2 (200, 10), ImGuiCond_Once );
    ImGui::Begin("Log de mensajes");
    std::vector<std::string> aux = PAG::GUI::instancia->log;
    for(int i = 0 ; i < aux.size() ; i++){
        ImGui::Text(aux[i].c_str());
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
}

/**
 * Metodo para asignarle a la ventana de color que color modificar
 * @param _color El color a modificar
 */
void PAG::GUI::setColor(GLfloat *_color) {
    this->color = _color;
}

/**
 * Metodo para agregar un mensaje al log de la GUI
 * @param cad El nuevo mensaje
 */
void PAG::GUI::agregarMensaje(std::string& cad) {
    log.push_back(cad);
}
