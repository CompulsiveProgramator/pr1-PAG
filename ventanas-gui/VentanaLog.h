//
// Created by secre on 29/10/2024.
//

#ifndef PR1_VENTANALOG_H
#define PR1_VENTANALOG_H

#include "Ventana.h"
#include <vector>
#include <iostream>

namespace PAG{
    class VentanaLog: public Ventana {
    private:
        std::vector<std::string> log;
    public:
        VentanaLog();
        void refrescarVentana() override;
        void agregarMensajeLog(std::string &cad) { //ToDo Ver porque no se agregan correctamente los mensajes al log
            log.push_back(cad);
        }
    };
}

#endif //PR1_VENTANALOG_H
