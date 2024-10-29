//
// Created by secre on 28/09/2024.
//

#include "GUI.h"

PAG::GUI* PAG::GUI::instancia = nullptr; //Para inicializar la instancia como nula

/**
 * Constructor por defecto de la clase, que inicializa toodo para que ImGui funcione
 * @param window Es la ventana sobre la que se pintará la GUI
 */
PAG::GUI::GUI(): botonPulsado(false), nombreShaderProgram(), ventanaSeleccionColor(), ventanaLog(){

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
    if(instancia == nullptr){
        instancia = new GUI();
    }

    return *instancia;
}

/**
 * Metodo para refrescar la ventana
 */
void PAG::GUI::refrescar() {
    pintarGUI();
}

void PAG::GUI::pintarGUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Ventana para pillar el color de fondo:
    ventanaSeleccionColor.refrescarVentana();

    //Ventana del log:
    ventanaLog.refrescarVentana();

    //Ventana para seleccionar el shader program
    ImGui::SetNextWindowPos(ImVec2(10, 300), ImGuiCond_Once);
    ImGui::Begin("Seleccionar shader program");
    ImGui::Text("Dime el nombre del shader program:");
    ImGui::Text("Formato 'pag0x'");
    ImGui::InputText("##", &nombreShaderProgram, ImGuiInputTextFlags_AutoSelectAll);
    botonPulsado = ImGui::Button("Load");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
}

/**
 * Metodo para asignarle a la ventana de color que color modificar
 * @param _color El color a modificar
 */


/**
 * Metodo para agregar un mensaje al log de la GUI
 * @param cad El nuevo mensaje
 */
void PAG::GUI::agregarMensajeLog(std::string &cad) {
    ventanaLog.agregarMensajeLog(cad);
}

/**
 * Metodo para devolver el nombre del archivo del Shader Program
 * @return
 */
std::string PAG::GUI::getNombreShaderProgram() {
    return nombreShaderProgram;
}

/**
 * Metodo para comprobar si se pulsó el boton
 * @return
 */
bool PAG::GUI::getBotonPulsado() {
    return botonPulsado;
}

/**
 * Metodo para pasarle el puntero al color a modificar, a la ventana de selección de color
 * @param color El puntero color a modificar
 */
void PAG::GUI::setColor(GLfloat *color) {
    this->ventanaSeleccionColor.setColor(color);
}
