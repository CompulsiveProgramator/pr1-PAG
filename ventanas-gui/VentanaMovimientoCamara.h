//
// Created by secre on 29/10/2024.
//

#ifndef PR1_VENTANAMOVIMIENTOCAMARA_H
#define PR1_VENTANAMOVIMIENTOCAMARA_H

#include "Ventana.h"
#include "../Constantes.h"
#include "../Camara.h"

namespace PAG{
    class VentanaMovimientoCamara: public Ventana{
    private:
        Camara *camara;

    public:
        void refrescarVentana() override;
        void setCamara(Camara *_camara);
    };
}

#endif //PR1_VENTANAMOVIMIENTOCAMARA_H
