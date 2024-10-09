//
// Created by secre on 27/09/2024.
//

#ifndef PR1_RENDERER_H
#define PR1_RENDERER_H

#include <glad/glad.h>
#include <GL/gl.h>
#include <iostream>

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
        GLuint idVS = 0; //Id del vertex shader
        GLuint idFS = 0; //Id del fragment shader
        GLuint idSP = 0; //Id del shader program
        GLuint idVAO = 0; //Id del Vertex Array Object
        GLuint idVBO = 0; //Id del Vertex Buffer Object
        GLuint idIBO = 0; //Id del Index Buffer Object

    public:
        virtual ~Renderer();
        static Renderer& getInstancia(); //Para obtener la instancia desde fuera
        void refrescar();
        GLfloat *getColorFondo();
        void setColorFondo(const GLfloat color[4]);

        //Para los callbacks del main:
        void modificarTamañoVentana(int width, int height);

        //Para la practica 3:
        void creaShaderProgram();
        void creaModelo();
        void inicializaOpenGL();

        //Para compilar un shader al completo:
        GLuint crearSP(); //Devuelve el handler
        std::string leerShaderSource(std::string filename); //Devuelve el string del shader source
        GLuint creaShaderObject(GLenum shaderType); //Devuelve el shader handler
        void compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler);
        void enlazarSP(GLuint handler, GLuint shaderHandler);

    };
}



#endif //PR1_RENDERER_H
