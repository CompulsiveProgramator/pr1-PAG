//
// Created by secre on 19/11/2024.
//

#include "Modelo.h"

#include "OBJ_Loader.h"

/**
 * Constructor de la clase, que inicializa el modelo usando Assimp !
 * @param pathToModel El camino al archivo que se quiere abrir
 */
PAG::Modelo::Modelo(std::string pathToModel) {
    /*
     * OBJ loader carga el archivo .obj en una variable loader
     *
     * Usa una estructura de datos que contiene un mesh, y este mesh tiene un vector de "Vertex" y de "indices"
     * Un Vertex es un struct que contiene un vertice, con su posicion, coordenada de textura y normal
     */

    using namespace std;

    cout << pathToModel << std::endl;

    objl::Loader loader;
    if(!loader.LoadFile(pathToModel)){
        cout << "No se pudo cargar el archivo";
    }

    objl::Mesh &mesh = loader.LoadedMeshes[0];

    vector<GLfloat> posicionVertices;
    vector<GLfloat> color;
    vector<unsigned int> indices;

    /// Pillamos las posiciones de cada vertice ;)
    for(int i = 0 ; i < mesh.Vertices.size() ; i++){
        posicionVertices.push_back(mesh.Vertices[i].Position.X);
        posicionVertices.push_back(mesh.Vertices[i].Position.Y);
        posicionVertices.push_back(mesh.Vertices[i].Position.Z);

        cout << mesh.Vertices[i].Position.X << " " << mesh.Vertices[i].Position.Y << " " << mesh.Vertices[i].Position.Z << endl;
    }

    /// Le damos un color fijo a cada vertice todo Hacer que lo coja del .obj
    for(int i = 0 ; i < mesh.Vertices.size() ; i++){
        color.push_back(0.0);
        color.push_back(0.0);
        color.push_back(1.0); //Metemos un azul
    }

    for(int i = 0 ; i < mesh.Indices.size() ; i++){
        indices.push_back(mesh.Indices[i]);
    }

    malla = new Malla(posicionVertices, color, indices);
}

PAG::Modelo::~Modelo() {
    delete malla;
}

PAG::Malla *PAG::Modelo::getMalla() {
    return malla;
}
