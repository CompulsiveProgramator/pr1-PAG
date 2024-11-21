//
// Created by secre on 19/11/2024.
//

#include "Modelo.h"

/**
 * Constructor de la clase, que inicializa el modelo usando Assimp !
 * @param pathToModel El camino al archivo que se quiere abrir
 */
PAG::Modelo::Modelo(std::string pathToModel) {
    std::cout << pathToModel << std::endl;

    /*ToDo Comprobar que funciona correctamente la libreria .dll, accediendo al objeto de la clase escena para ver si ha leido correctamente el archivo .obj del directorio
     * que le pasa el ShaderProgram
     */
    Assimp::Importer importer; //Creamos el objeto que importa archivos .obj

    ///Aqui obtenemos la EEDD de Assimp, que contiene los datos almacenados en el .obj
    /*
     * Los flags son respectivamente para que todos los vertices iguales los una, para que triangule los poligonos si hay poligonos con mas de 3 vertices,
     * y el ultimo para que genere normales si no las especificamos en el .obj
    */
    const aiScene *scene = importer.ReadFile(pathToModel, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    malla = new Malla();
}

PAG::Malla *PAG::Modelo::getMalla() {
    return malla;
}
