//
// Created by secre on 29/10/2024.
//

#ifndef PR1_CONSTANTES_H
#define PR1_CONSTANTES_H

/**
* Archivo para almacenar las constantes para el movimiento de la camara
*/

enum MovimientoCamara {Dolly, Crane, Pan, Tilt, Orbit, Zoom};

/**
 * Variable para ver el tipo de movimiento seleccionado
 */
static MovimientoCamara movimientoCamara = MovimientoCamara::Dolly;

//ToDo el main.cpp y VentanaMovimientoCamara.cpp no comparten la misma variable de arriba

#endif //PR1_CONSTANTES_H