//
// Created by secre on 22/11/2024.
//

#include "VentanaSelectorModelo.h"

/**
 * Constructor de la clase
 */
PAG::VentanaSelectorModelo::VentanaSelectorModelo(): fileDialog() {
    fileDialog.SetTitle("Selector modelo .obj");
    fileDialog.SetTypeFilters({".obj"});
}

/**
 * Metodo para refrescar la ventana
 */
void PAG::VentanaSelectorModelo::refrescarVentana() {
    ImGui::SetNextWindowPos ( ImVec2 (350, 50), ImGuiCond_Once );

    if(ImGui::Begin("##")){
        if(ImGui::Button("open file dialog"))
            fileDialog.Open();
    }
    ImGui::End();

    fileDialog.Display();

    if(fileDialog.HasSelected())
    {
        localizacionFichero = fileDialog.GetSelected().string();
        fileDialog.ClearSelected();
    }else{
        localizacionFichero = "";
    }
}

/**
 * Metodo para obtener la localizacino del fichero de modelo como un string
 * @return
 */
std::string PAG::VentanaSelectorModelo::getLocalizacionFichero() {
    return localizacionFichero;
}
