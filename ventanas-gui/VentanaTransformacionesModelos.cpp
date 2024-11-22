//
// Created by secre on 22/11/2024.
//

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/gtx/transform.hpp"
#include "VentanaTransformacionesModelos.h"

/**
 * Constructor de la clase
 */
PAG::VentanaTransformacionesModelos::VentanaTransformacionesModelos() {
    modelos = nullptr;
}

void PAG::VentanaTransformacionesModelos::refrescarVentana() {
    /**
     * Para cada modelo, cojemos su malla y aplicamos una traslacion
     */
    ImGui::SetNextWindowPos ( ImVec2 (350, 350), ImGuiCond_Once );

    ImGui::Begin("Ventana transformaciones de modelos:");
    ImGui::Text("Pulsa el boton con el modelo que quieres seleccionar:");
    if(modelos != nullptr){
        for(int i = 0 ; i < modelos->size() ; i++){
            char aux = i + 48;
            std::string auxS;
            auxS += "Modelo ";
            auxS.push_back(aux);
            if(ImGui::Button(auxS.c_str())){
                modelos->data()[i]->getMalla()->trasladarMalla(glm::translate(glm::vec3(0.1,0,0)));
            }
        }
    }
    ImGui::End();
}

/**
 * Metodo para agregar la direccion en memoria, del vector con los modelos activos en el Shader Program ;)
 * @param modelo
 */
void PAG::VentanaTransformacionesModelos::agregarModelos(std::vector<Modelo*> *modelos) {
    this->modelos = modelos;
}
