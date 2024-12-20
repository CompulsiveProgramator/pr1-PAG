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
    modeloSeleccionado = 0;
}

void PAG::VentanaTransformacionesModelos::refrescarVentana() {
    /**
     * Para cada modelo, cojemos su malla y aplicamos una traslacion
     */

    //Si no hay modelos, no se pinta la ventana ;)

    if(modelos.size() == 0){
        return;
    }

    ImGui::SetNextWindowPos ( ImVec2 (350, 350), ImGuiCond_Once );

    ImGui::Begin("Ventana transformaciones de modelos:");

    seleccionaModelo();

    seleccionaTransformacion();

    if(ImGui::Button("Eliminar modelo seleccionado"))
    {
        eliminarModelo = true;
    }else{
        eliminarModelo = false;
    }

    ImGui::End();
}

/**
 * Metodo para agregar la direccion en memoria, del vector con los modelos activos en el Shader Program ;)
 * @param modelo
 */
void PAG::VentanaTransformacionesModelos::agregarModelos(std::vector<Modelo*> &_modelos) {
    this->modelos = _modelos;
}

/**
 * Boton para seleccionar modelo
 * @return La posicion relativa del modelo seleccionado, en el vector "this->modelos"
 */
void PAG::VentanaTransformacionesModelos::seleccionaModelo() {
    ImGui::Text("Selecciona el modelo:");

    std::vector<std::string> nombresModelos;
    for(int i = 0 ; i < modelos.size() ; i++){
        nombresModelos.push_back(modelos[i]->getNombreModelo());
    }

    // Esto es para cuando se borra el ultimo elemento del vector de modelos, ya que modeloSeleccionado pasaria a estar fuera del rango legal ! ;)
    if(modeloSeleccionado >= modelos.size())
    {
        modeloSeleccionado = 0; //Volvemos al inicial por defecto
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
    }else if(tiposTransformaciones[tipoTransformacionActual] == "Rotacion"){
        selectorRotacion();
    }else if(tiposTransformaciones[tipoTransformacionActual] == "Escalado"){
        selectorEscalado();
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

    static bool inputs_step = true;
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
    static float valorTraslacion = 0; //Para ver cual es el valor de la traslacion del Drag
    float min = -1, max = 1; //Para decir el rango maximo de movimiento de x[-1, 1]
    ImGui::DragScalar("##d",     ImGuiDataType_Float,  &valorTraslacion, 0.005f,  &min, &max, "%f");

    if(ImGui::Button("Aplicar"))
    {
        if(tiposTraslaciones[tipoTraslacionActual] == "X"){
            modelos[modeloSeleccionado]->getMalla()->trasladarMalla(glm::translate(glm::vec3(valorTraslacion, 0, 0)));
        }else if(tiposTraslaciones[tipoTraslacionActual] == "Y"){
            modelos[modeloSeleccionado]->getMalla()->trasladarMalla(glm::translate(glm::vec3(0, valorTraslacion, 0)));
        }else if(tiposTraslaciones[tipoTraslacionActual] == "Z"){
            modelos[modeloSeleccionado]->getMalla()->trasladarMalla(glm::translate(glm::vec3(0, 0, valorTraslacion)));
        }
    }

}

/**
 * Parte de la ventana que permite aplicar rotaciones al modelo seleccionado
 */
void PAG::VentanaTransformacionesModelos::selectorRotacion() {
    const char* tipoRotacion[] = {"X", "Y", "Z"};
    static unsigned int tipoRotacionActual = 0;

    if(ImGui::BeginCombo("##t", tipoRotacion[tipoRotacionActual]))
    {
        for(int n = 0 ; n < IM_ARRAYSIZE(tipoRotacion) ; n++ )
        {
            const bool is_selected = (tipoRotacionActual == n);
            if(ImGui::Selectable(tipoRotacion[n], is_selected))
            {
                tipoRotacionActual = n;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    static bool inputs_step = true;
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
    static float gradosRotacion = 0; //Para ver cual es el valor de la rotacion del Drag
    float min = -90, max = 90; //Para decir el rango maximo de movimiento de x[-1, 1]
    ImGui::DragScalar("##d", ImGuiDataType_Float, &gradosRotacion, 0.05f, &min, &max, "%f");

    if(ImGui::Button("Aplicar"))
    {
        if(tipoRotacion[tipoRotacionActual] == "X"){
            modelos[modeloSeleccionado]->getMalla()->rotarMalla(glm::rotate(glm::radians(gradosRotacion), glm::vec3(1, 0, 0)));
        }else if(tipoRotacion[tipoRotacionActual] == "Y"){
            modelos[modeloSeleccionado]->getMalla()->rotarMalla(glm::rotate(glm::radians(gradosRotacion), glm::vec3(0, 1, 0)));
        }else if(tipoRotacion[tipoRotacionActual] == "Z"){
            modelos[modeloSeleccionado]->getMalla()->rotarMalla(glm::rotate(glm::radians(gradosRotacion), glm::vec3(0, 0, 1)));
        }
    }
}

/**
 * Parte de la ventana que hace el escalado del objeto en escena
 */
void PAG::VentanaTransformacionesModelos::selectorEscalado() {
    const char* tipoEscalado[] = {"X", "Y", "Z", "Uniforme"};
    static unsigned int tipoEscaladoActual = 0;

    if(ImGui::BeginCombo("##s", tipoEscalado[tipoEscaladoActual]))
    {
        for(int n = 0 ; n < IM_ARRAYSIZE(tipoEscalado) ; n++ )
        {
            const bool is_selected = (tipoEscaladoActual == n);
            if(ImGui::Selectable(tipoEscalado[n], is_selected))
            {
                tipoEscaladoActual = n;
            }

            if (is_selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    static bool inputs_step = true;
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
    static float valorEscalado = 1; //Para ver cual es el valor de la rotacion del Drag
    float min = 0.5, max = 2; //Para decir el rango maximo de movimiento de x[-1, 1]
    ImGui::DragScalar("##d", ImGuiDataType_Float, &valorEscalado, 0.005f, &min, &max, "%f");

    if(ImGui::Button("Aplicar"))
    {
        if(tipoEscalado[tipoEscaladoActual] == "X"){
            modelos[modeloSeleccionado]->getMalla()->escalarMalla(glm::scale(glm::vec3(valorEscalado, 1, 1)));
        }else if(tipoEscalado[tipoEscaladoActual] == "Y"){
            modelos[modeloSeleccionado]->getMalla()->escalarMalla(glm::scale(glm::vec3(1, valorEscalado, 1)));
        }else if(tipoEscalado[tipoEscaladoActual] == "Z"){
            modelos[modeloSeleccionado]->getMalla()->escalarMalla(glm::scale(glm::vec3(1, 1, valorEscalado)));
        }else if(tipoEscalado[tipoEscaladoActual] == "Uniforme"){
            modelos[modeloSeleccionado]->getMalla()->escalarMalla(glm::scale(glm::vec3(valorEscalado, valorEscalado, valorEscalado)));
        }
    }
}

unsigned int PAG::VentanaTransformacionesModelos::getModeloSeleccionado() {
    return modeloSeleccionado;
}

bool PAG::VentanaTransformacionesModelos::getEliminarModelo() {
    return eliminarModelo;
}
