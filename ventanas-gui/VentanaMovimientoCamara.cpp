//
// Created by secre on 29/10/2024.
//

#include "VentanaMovimientoCamara.h"

void PAG::VentanaMovimientoCamara::refrescarVentana() {
    ImGui::Begin("Ventana movimiento camara");
    const char* items[] = { "Dolly", "Crane", "Pan", "Tilt", "Orbit"};
    static int item_current_idx = 0; // Índice de la opción seleccionada

    ImGui::Text("Opciones de movimiento:");
    if (ImGui::BeginCombo("##", items[item_current_idx])) // Etiqueta del combo
    {
        for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n; // Guarda la opción seleccionada

            // Marca el elemento seleccionado para que esté resaltado
            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    if(items[item_current_idx] == "Dolly"){
        if(ImGui::Button("^Back^")){
            camara->desplazarSobreEjeZ(false);
        }
        if(ImGui::Button("Right>")){
            camara->desplazarSobreEjeX(true);
        }
        if(ImGui::Button("<Left")){
            camara->desplazarSobreEjeX(false);
        }
        if(ImGui::Button("Front")){
            camara->desplazarSobreEjeZ(true);
        }
    }

    if(items[item_current_idx] == "Crane"){
        if(ImGui::Button("Up")){
            camara->desplazarSobreEjeY(true);
        }
        if(ImGui::Button("Down")){
            camara->desplazarSobreEjeY(false);
        }
    }

    if(items[item_current_idx] == "Pan"){
        if(ImGui::Button("<Left")){
            camara->rotarSobreCamaraEjeY(true);
        }
        if(ImGui::Button("Right>")){
            camara->rotarSobreCamaraEjeY(false);
        }
    }

    if(items[item_current_idx] == "Tilt"){
        if(ImGui::Button("Up")){
            camara->rotarSobreCamaraEjeX(true);
        }
        if(ImGui::Button("Down")){
            camara->rotarSobreCamaraEjeX(false);
        }
    }

    if(items[item_current_idx] == "Orbit"){
        if(ImGui::Button("North")){
            camara->rotarSobreLookAtEjeX(false);
        }
        if(ImGui::Button("South")){
            camara->rotarSobreLookAtEjeX(true);
        }
        if(ImGui::Button("West")){
            camara->rotarSobreLookAtEjeY(false);
        }
        if(ImGui::Button("East")){
            camara->rotarSobreLookAtEjeY(true);
        }
    }

    ImGui::End();
}

void PAG::VentanaMovimientoCamara::setCamara(PAG::Camara *_camara) {
    this->camara = _camara;
}
