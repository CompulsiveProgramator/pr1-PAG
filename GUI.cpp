//
// Created by secre on 28/09/2024.
//

#include "GUI.h"

PAG::GUI* PAG::GUI::instancia = nullptr; //Para inicializar la instancia como nula

/**
 * Constructor por defecto de la clase, que inicializa toodo para que ImGui funcione
 * @param window Es la ventana sobre la que se pintará la GUI
 */
PAG::GUI::GUI() {

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
