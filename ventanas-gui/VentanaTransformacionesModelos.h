//
// Created by secre on 22/11/2024.
//

#ifndef PR1_VENTANATRANSFORMACIONESMODELOS_H
#define PR1_VENTANATRANSFORMACIONESMODELOS_H

#include "../Modelo.h"
#include "Ventana.h"

namespace PAG{
    class VentanaTransformacionesModelos: public Ventana{
    private:
        std::vector<Modelo*> *modelos; ///Un vector con los modelos activos en escena
        unsigned int modeloSeleccionado = 0; ///La posicion relativa en el vector de arriba, del modelo seleccionado para aplicar una transformacion

        void seleccionaModelo();
        void seleccionaTransformacion();
        void selectorTraslacion();
        void selectorRotacion();
        void selectorEscalado();
    public:
        VentanaTransformacionesModelos();
        void refrescarVentana() override;
        void agregarModelos(std::vector<Modelo*> *modelos);
    };
}


#endif //PR1_VENTANATRANSFORMACIONESMODELOS_H
