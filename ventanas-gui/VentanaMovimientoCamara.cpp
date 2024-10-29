//
// Created by secre on 29/10/2024.
//

#include "VentanaMovimientoCamara.h"

void PAG::VentanaMovimientoCamara::refrescarVentana() {
    const char* items[] = { "Dolly", "Crane"};
    static int item_current_idx = 0; // Índice de la opción seleccionada
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
}

void PAG::VentanaMovimientoCamara::setCamara(PAG::Camara *_camara) {
    this->camara = _camara;
}
