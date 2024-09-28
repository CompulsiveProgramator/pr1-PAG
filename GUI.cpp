//
// Created by secre on 28/09/2024.
//

#include "GUI.h"

/**
 * Constructor por defecto de la clase
 */
PAG::GUI::GUI() {

}

/**
 * Destructor de la clase
 */
PAG::GUI::~GUI() {

}

/**
 * Metodo para obtener la unica instancia de la clase
 * @return
 */
PAG::GUI *PAG::GUI::getInstancia() {
    if(!instancia){
        instancia = new GUI();
    }

    return instancia;
}
