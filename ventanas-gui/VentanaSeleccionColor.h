//
// Created by secre on 29/10/2024.
//

#ifndef PR1_VENTANASELECCIONCOLOR_H
#define PR1_VENTANASELECCIONCOLOR_H

#include "GL/gl.h" //Solo para el color de fondo de la ventana de color
#include "Ventana.h"

namespace PAG{
    /**
     * Clase para la ventana de seleccion de color
     */
    class VentanaSeleccionColor: public Ventana{
    private:
        GLfloat *color = nullptr;
    public:
        VentanaSeleccionColor() = default;
        void refrescarVentana() override;
        void setColor(GLfloat *_color) {
            this->color = _color;
        }
    };
}


#endif //PR1_VENTANASELECCIONCOLOR_H
