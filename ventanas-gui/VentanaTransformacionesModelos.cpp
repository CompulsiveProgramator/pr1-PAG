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
    modeloSeleccionado = 0;
}

void PAG::VentanaTransformacionesModelos::refrescarVentana() {
    /**
     * Para cada modelo, cojemos su malla y aplicamos una traslacion
     */

    //Si no hay modelos, no se pinta la ventana ;)
    if(modelos == nullptr){
        return;
    }
    if(modelos->size() == 0){
        return;
    }

    ImGui::SetNextWindowPos ( ImVec2 (350, 350), ImGuiCond_Once );

    //TODO Ventana para trasladar un modelo:
    ImGui::Begin("Ventana transformaciones de modelos:");

    seleccionaModelo();

    seleccionaTransformacion();

    ImGui::End();
}

/**
 * Metodo para agregar la direccion en memoria, del vector con los modelos activos en el Shader Program ;)
 * @param modelo
 */
void PAG::VentanaTransformacionesModelos::agregarModelos(std::vector<Modelo*> *modelos) {
    this->modelos = modelos;
}

/**
 * Boton para seleccionar modelo
 * @return La posicion relativa del modelo seleccionado, en el vector "this->modelos"
 */
void PAG::VentanaTransformacionesModelos::seleccionaModelo() {
    ImGui::Text("Selecciona el modelo:");

    std::vector<std::string> nombresModelos;
    for(int i = 0 ; i < modelos->size() ; i++){
        nombresModelos.push_back(modelos->data()[i]->getNombreModelo());
    }

    if (ImGui::BeginCombo("##selectorModelo", nombresModelos[modeloSeleccionado].c_str())) // Etiqueta del combo
    {
        for (int n = 0; n < nombresModelos.size() ; n++)
        {
            const bool is_selected = (modeloSeleccionado == n);
            if (ImGui::Selectable(nombresModelos[n].c_str(), is_selected))
            {
                modeloSeleccionado = n; // Guarda la opción seleccionada
            }

            // Marca el elemento seleccionado para que esté resaltado
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

/**
 * La parte de la ventana que selecciona el tipo de transformacion, y la aplica
 */
void PAG::VentanaTransformacionesModelos::seleccionaTransformacion() {
    const char* tiposTransformaciones[] = {"Traslacion", "Rotacion", "Escalado"}; //
    static unsigned int tipoTransformacionActual = 0; /// Como es una variable estatica de funcion, solo se declara una vez para todas las ejecuciones ;)

    ImGui::Text("Selecciona el tipo de transformación a aplicar:");
    if (ImGui::BeginCombo("##", tiposTransformaciones[tipoTransformacionActual])) // Etiqueta del combo
    {
        for (int n = 0; n < IM_ARRAYSIZE(tiposTransformaciones); n++)
        {
            const bool is_selected = (tipoTransformacionActual == n);
            if (ImGui::Selectable(tiposTransformaciones[n], is_selected))
            {
                tipoTransformacionActual = n; // Guarda la opción seleccionada
            }

            // Marca el elemento seleccionado para que esté resaltado
            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if(tiposTransformaciones[tipoTransformacionActual] == "Traslacion"){
        selectorTraslacion();
    }
}

/**
 * Parte de la ventana que selecciona el tipo de traslacion
 */
void PAG::VentanaTransformacionesModelos::selectorTraslacion() {
    const char* tiposTraslaciones[] = {"X","Y","Z"};
    static unsigned int tipoTraslacionActual = 0;

    if(ImGui::BeginCombo("##t", tiposTraslaciones[tipoTraslacionActual]))
    {
        for( int n = 0 ; n < IM_ARRAYSIZE(tiposTraslaciones) ; n++ )
        {
            const bool is_selected = (tipoTraslacionActual == n);
            if(ImGui::Selectable(tiposTraslaciones[n], is_selected))
            {
                tipoTraslacionActual = n;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    if(tiposTraslaciones[tipoTraslacionActual] == "X")
    {
        static bool inputs_step = true;
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
        static float valorTraslacion = 0; //Para ver cual es el valor de la traslacion del Drag
        float min = -1, max = 1; //Para decir el rango maximo de movimiento de x[-1, 1]
        ImGui::DragScalar("##d",     ImGuiDataType_Float,  &valorTraslacion, 0.005f,  &min, &max, "%f");

        //Para aplicar la traslacion al modelo seleccionado
        if(ImGui::Button("Aplicar"))
        {
            modelos->data()[modeloSeleccionado]->getMalla()->trasladarMalla(glm::translate(glm::vec3(valorTraslacion, 0, 0)));
        }
    }
}
