//
// Created by secre on 22/11/2024.
//

#ifndef PR1_VENTANASELECTORMODELO_H
#define PR1_VENTANASELECTORMODELO_H

#include "Ventana.h"
#include <vector>
#include <iostream>

#include "imfilebrowser.h"

namespace PAG{
    class VentanaSelectorModelo: public Ventana{
    private:
        ImGui::FileBrowser fileDialog;
        std::string localizacionFichero; //El string con la ruta relativa al modelo seleccionado
    public:
        VentanaSelectorModelo();
        void refrescarVentana() override;
        std::string getLocalizacionFichero();
    };
}

#endif //PR1_VENTANASELECTORMODELO_H
