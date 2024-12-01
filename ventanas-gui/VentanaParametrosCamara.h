//
// Created by secre on 01/12/2024.
//

#ifndef PR1_VENTANAPARAMETROSCAMARA_H
#define PR1_VENTANAPARAMETROSCAMARA_H

#include "Ventana.h"
#include "../Camara.h"

namespace PAG{
    /**
     * Ventana para consultar los parametros de la camara
     * - Posicion
     * - Look at
     * - Fov Y
     * - Znear y zfar
     */
    class VentanaParametrosCamara: public Ventana{
    private:
        Camara *camara = nullptr;
    public:
        void refrescarVentana() override;
        VentanaParametrosCamara();
        void asociarCamara(Camara *_camara);
    };
}



#endif //PR1_VENTANAPARAMETROSCAMARA_H
