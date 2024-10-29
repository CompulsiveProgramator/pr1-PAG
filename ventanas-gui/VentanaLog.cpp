//
// Created by secre on 29/10/2024.
//

#include "VentanaLog.h"

/**
 * Constructor por defecto de la clase
 */
PAG::VentanaLog::VentanaLog():log() {}

/**
 * Metodo para refrescar la ventana del log de mensajes
 */
void PAG::VentanaLog::refrescarVentana() {
    ImGui::SetNextWindowPos ( ImVec2 (400, 10), ImGuiCond_Once );
    ImGui::Begin("Log de mensajes");
    std::cout << log.size();
    for(int i = 0 ; i < log.size() ; i++){
        ImGui::Text(log[i].c_str());
    }
    ImGui::End();
}
