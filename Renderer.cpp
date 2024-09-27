//
// Created by secre on 27/09/2024.
//

#include <GL/gl.h>
#include "Renderer.h"

namespace PAG
{
    Renderer* PAG::Renderer::instancia = nullptr;

    /**
     * Constructor por defecto vacio
     */
    Renderer::Renderer() {

    }

    Renderer::~Renderer() {
    }

    /**
    * Metodo para obtener la instancia de la clase
    * @return
    */
    Renderer *PAG::Renderer::getInstancia() {
        if(!instancia){
            instancia = new Renderer();
        }
        return instancia;
    }

    /**
     * Metodo para refrescar la ventana
     */
    void Renderer::refrescar() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}




