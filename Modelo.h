//
// Created by secre on 19/11/2024.
//

#ifndef PR1_MODELO_H
#define PR1_MODELO_H

#include "Malla.h"
#include <iostream>

namespace PAG{
    /**
     * Clase que contiene un modelo, con solo un objeto de la clase Malla
     * Se comunica directamente con la clase Renderer
     * Usa al bonito Assimp para cargar los archivos .obj
     */
    class Modelo {
    private:
        Malla *malla = nullptr;
    public:
        Modelo(std::string pathToModel);
        ~Modelo();
        Malla* getMalla();
    };
}



#endif //PR1_MODELO_H
