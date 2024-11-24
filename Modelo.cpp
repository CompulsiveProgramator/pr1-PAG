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

    /**
     * Cuando OBJ loader lee un .obj como el de vaca.obj, primero mira cuantas caras tiene y lo multiplica por 3 para saber el numero de vertices/indices
     * luego es cuando segun lo que pone en cada cara, para un vertice coje una posicion, textura y normal ;)
     */

    objl::Mesh &mesh = loader.LoadedMeshes[0];

    nombreModelo = mesh.MeshName;

    vector<GLfloat> posicionVertices;
    vector<GLfloat> color;
    vector<unsigned int> indices;

    unsigned int counter = 0;

    //Leemos la posicion/color de cada vertice
    while(counter < mesh.Vertices.size())
    {
        //Metemos la posicion del vertice:
        posicionVertices.push_back(mesh.Vertices[counter].Position.X);
        posicionVertices.push_back(mesh.Vertices[counter].Position.Y);
        posicionVertices.push_back(mesh.Vertices[counter].Position.Z);

        //Metemos la coordenada de textura como color: todo Para la práctica 7 de texturas corregirlo ;)
        color.push_back(1);
        color.push_back(1);
        color.push_back(0);

        counter++;
    }

    counter = 0;
    while(counter < mesh.Indices.size()){
        indices.push_back(mesh.Indices[counter]);
        counter++;
    }

    malla = new Malla(posicionVertices, color, indices);
}

PAG::Modelo::~Modelo() {
    delete malla;
}

PAG::Malla *PAG::Modelo::getMalla() {
    return malla;
}

/**
 * Getter del atributo nombre modelo
 * @return
 */
std::string PAG::Modelo::getNombreModelo() {
    return nombreModelo;
}
