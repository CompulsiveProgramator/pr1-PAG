//
// Created by secre on 29/10/2024.
//

#include "VentanaSeleccionColor.h"

void PAG::VentanaSeleccionColor::refrescarVentana() {
    ImGui::SetNextWindowPos ( ImVec2 (10, 10), ImGuiCond_Once );
    ImGui::Begin("Color picker del fondo");
    float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.80f;
    ImGui::SetNextItemWidth(w);
    ImGui::Text("Selecciona el color de fondo:");
    ImGui::ColorPicker3("##MyColor##6", (float*) color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
    ImGui::End();
}
