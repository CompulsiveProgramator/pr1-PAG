//
// Created by secre on 18/12/2024.
//

#ifndef PR1_TEXTURA_H
#define PR1_TEXTURA_H

#include <vector>

namespace PAG{
    /**
     * Clase que contiene la imagen de la textura
     */
    class Textura {
    private:
        std::vector<unsigned char> imagen;
        unsigned ancho, alto; // El ancho y alto de la imagen
    public:
        Textura();
        std::vector<unsigned char> getImagen();

        unsigned getAncho();
        unsigned getAlto();
    };
}



#endif //PR1_TEXTURA_H
