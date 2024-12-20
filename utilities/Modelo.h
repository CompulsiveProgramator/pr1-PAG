//
// Created by secre on 19/11/2024.
//

#ifndef PR1_MODELO_H
#define PR1_MODELO_H

#include <iostream>
#include "Malla.h"
#include "Material.h"

namespace PAG{
    /**
     * Clase que contiene un modelo, con solo un objeto de la clase Malla
     * Se comunica directamente con la clase Renderer
     * Usa al bonito Assimp para cargar los archivos .obj
     */
    class Modelo {
    private:
        Malla *malla = nullptr;
        Material material;
        std::string nombreModelo;
    public:
        Modelo(std::string pathToModel);
        ~Modelo();
        Malla* getMalla();
        std::string getNombreModelo();
        void operator=(Modelo &otro);
        Material* getMaterial();
    };
}



#endif //PR1_MODELO_H
