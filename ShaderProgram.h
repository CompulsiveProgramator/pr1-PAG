//
// Created by secre on 11/10/2024.
//

#ifndef PR1_SHADERPROGRAM_H
#define PR1_SHADERPROGRAM_H

#define GLM_ENABLE_EXPERIMENTAL

#include "Camara.h"
#include "Modelo.h"
#include "Luz.h"

namespace PAG{
    enum ModosVisualizacion{
        ALAMBRE,
        SOLIDO
    };

    class ShaderProgram {
    private:
        GLuint idSP = 0; //Id del shader program
        std::string nombreFicheros; /// El nombre de los ficheros ( solo parte inicial, EJ: pag03 , y asi sacamos el pag03-vs.glsl y el pag03-fs.glsl ;) )
        Camara *camara = nullptr; /// El puntero para la camara virtual de la ventana
        std::vector<Modelo*> modelos; /// El puntero a nuestro modelo!
        std::vector<Luz> luces;
        ModosVisualizacion modoVisualizacion = SOLIDO;

        void elegirModoVisualizacion();
        void pasarUniformMV(glm::mat4 &matrizMV);
        void pasarUniformMVP(glm::mat4 &matrizMVP);
    public:
        ShaderProgram(std::string &nombreFicheros, Camara *camara);
        ~ShaderProgram();
        void ejecutarSP();
        void creaShaderProgram(); ///Este es el que hay que llamar desde fuera

        //Para compilar un shader al completo:
        void crearSP(GLuint &handler);
        std::string leerShaderSource(std::string filename);
        GLuint creaShaderObject(GLenum shaderType);
        void compilarShaderObject(std::string shaderSourceString, GLuint shaderHandler, GLenum shaderType);
        void enlazarSP(GLuint handler, std::string filename);

        void agregarModelo(std::string localizacion);
        std::vector<Modelo*>* getModelos();
        void eliminarModelo(unsigned int posicion);
        void setModoVisualizacion(ModosVisualizacion modo);
    };
}

#endif //PR1_SHADERPROGRAM_H
