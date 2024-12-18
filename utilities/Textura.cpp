//
// Created by secre on 18/12/2024.
//

#include <stdexcept>
#include "lodepng.h"
#include "Textura.h"

/**
 * Constructor por defecto de la textura
 *
 * Por ahora, se carga manualmente la textura
 */
PAG::Textura::Textura() {
    std::string rutaDeFichero = "../imagenes_textura/vaca_texture.png";

    unsigned error = lodepng::decode (imagen, ancho, alto, rutaDeFichero);

    if (error)
    {
        std::string mensaje = rutaDeFichero + " no se pudo cargar";
        throw std::runtime_error ( mensaje );
    }

    // La textura se carga del revés, así que vamos a darle la vuelta
    unsigned char *imgPtr = &imagen[0];
    int numeroDeComponentesDeColor = 4; //rgba
    int incrementoAncho = ancho * numeroDeComponentesDeColor; // Ancho en bytes
    unsigned char* top = nullptr;
    unsigned char* bot = nullptr;
    unsigned char temp = 0;
    for (int i = 0; i < alto / 2; i++)
    {
        top = imgPtr + i * incrementoAncho;
        bot = imgPtr + (alto- i- 1) * incrementoAncho;
        for (int j = 0; j < incrementoAncho; j++)
        {
            temp = *top;
            *top = *bot;
            *bot = temp;
            ++top;
            ++bot;
        }
    }

}

/**
 * Getter de la imagen leida
 * @return
 */
std::vector<unsigned char> PAG::Textura::getImagen() {
    return imagen;
}

/**
 * Para ver el ancho de la imagen
 * @return
 */
unsigned PAG::Textura::getAncho() {
    return ancho;
}

/**
 * Para ver el alto de la imagen
 * @return
 */
unsigned PAG::Textura::getAlto() {
    return alto;
}

