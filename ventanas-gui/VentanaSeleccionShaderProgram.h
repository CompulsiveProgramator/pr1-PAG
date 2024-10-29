//
// Created by secre on 29/10/2024.
//

#ifndef PR1_VENTANASELECCIONSHADERPROGRAM_H
#define PR1_VENTANASELECCIONSHADERPROGRAM_H

#include "Ventana.h"
#include "iostream"
#include <imgui_stdlib.h>

namespace PAG{
    class VentanaSeleccionShaderProgram: public Ventana {
    private:
        std::string nombreShaderProgram;
        bool botonPulsado;
    public:
        VentanaSeleccionShaderProgram();
        void refrescarVentana() override;
        const std::string &getNombreShaderProgram() const;
        bool isBotonPulsado() const;
    };
}



#endif //PR1_VENTANASELECCIONSHADERPROGRAM_H
