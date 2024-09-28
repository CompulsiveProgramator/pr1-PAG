//
// Created by secre on 27/09/2024.
//

#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

///El espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG{
    /**
     * Clase que sigue el patron SINGLETON para renderizar
     */
    class Renderer {
    private:
        static Renderer* instancia; //Para el patron Singleton
        Renderer();

    public:
        virtual ~Renderer();
        static Renderer* getInstancia(); //Para obtener la instancia desde fuera
        void refrescar();
    };
}



#endif //PR1_RENDERER_H
