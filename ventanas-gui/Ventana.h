//
// Created by secre on 29/10/2024.
//

#ifndef PR1_VENTANA_H
#define PR1_VENTANA_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace PAG{
    class Ventana {
    public:
        virtual void refrescarVentana() = 0;
    };
}


#endif //PR1_VENTANA_H
