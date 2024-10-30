//
// Created by secre on 29/10/2024.
//

#ifndef PR1_CONSTANTES_H
#define PR1_CONSTANTES_H

/**
* Archivo para almacenar las constantes para el movimiento de la camara
*/

namespace PAG{
    enum tipoMovimiento {Dolly, Crane, Pan, Tilt, Orbit, Zoom};

/**
 * Clase Singleton para consultar el valor del tipo de movimiento desde cualquier parte de la aplicación ;)
 */
    class MovimientoCamara {
    private:
        static MovimientoCamara *instancia;
        MovimientoCamara(): mov(tipoMovimiento::Dolly){}
        tipoMovimiento mov = tipoMovimiento::Dolly; ///< Por defecto es un Dolly
    public:
        /**
         * Metodo para obtener la instancia de la clase
         * @return La instancia
         */
        static MovimientoCamara& getInstancia(){
            if(!instancia){
                instancia = new MovimientoCamara();
            }

            return *instancia;
        }

        ~MovimientoCamara(){
            if(instancia){
                delete instancia;
            }
        }

        /**
         * Metodo para consultar el valor del tipo de movimiento actual seleccionado en la camara
         * @return El tipo de movimiento
         */
        tipoMovimiento getTipoMovimiento(){
            return mov;
        }

        /**
         * Metodo para establecer el tipo de movimiento de la camara
         * @param _mov
         */
        void setTipoMovimiento(tipoMovimiento _mov){
            mov = _mov;
        }
    };
}

#endif //PR1_CONSTANTES_H