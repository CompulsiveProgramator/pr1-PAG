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
        bool seguirMovimientoRaton = false; //Variable para gestionar si seguimos o no, el movimiento del raton para mover la camara
    public:
        void refrescarVentana() override;
        void setCamara(Camara *_camara);
        bool getSeguirMovimientoRaton();
    };
}

#endif //PR1_VENTANAMOVIMIENTOCAMARA_H
