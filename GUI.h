//
// Created by secre on 28/09/2024.
//

#ifndef PR1_GUI_H
#define PR1_GUI_H

namespace PAG{
    /**
     * Clase segun patron SINGLETON para gestionar las ventanas de la interfaz grafica
     * Muy chula para controlar variables de nuestra aplicacion ;)
     */
    class GUI {
    private:
        static GUI* instancia;
        GUI();
    public:
        virtual ~GUI();
        static GUI* getInstancia();
    };
}



#endif //PR1_GUI_H
