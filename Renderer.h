//
// Created by secre on 27/09/2024.
//

#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <glad/glad.h>
#include <GL/gl.h>
#include <iostream>
#include "glm/mat4x4.hpp"
#include "ShaderProgram.h"

///El espacio de nombres para las prácticas de Programación de Aplicaciones Gráficas
namespace PAG{
    /**
     * Clase que sigue el patron SINGLETON para renderizar
     */
    class Renderer {
    private:
        static Renderer* instancia; //Para el patron Singleton
        Renderer(); //El constructor es privado, para que no se puedan crear instancias desde fuera
        GLfloat colorFondo[4];
        std::string nombreSP; //El nombre del shader program
        ShaderProgram *shaderProgram = nullptr;

    public:
        virtual ~Renderer();
        static Renderer& getInstancia(); //Para obtener la instancia desde fuera
        void refrescar();
        GLfloat *getColorFondo();
        void setColorFondo(const GLfloat color[4]);
        void modificarTamañoVentana(int width, int height);
        void inicializaOpenGL();
        void setNombreShaderProgram(std::string nombreF);
    };
}

#endif //PR1_RENDERER_H