#version 410

layout ( location = 0 ) in vec3 p; // La posicion
layout ( location = 1 ) in vec3 n; // La normal del vertice

uniform mat4 matrizModeladoVisionPerspectiva;
uniform mat4 matrizModeladoVision;

// Las variables transformadas en el espacio de vision, que van al rasterizador, y de el
// van interpoladas a cada fragmento del fragment shader ;)
out vec3 posicion;
out vec3 normal;

void main()
{
    normal = vec3( matrizModeladoVision * vec4(n, 0) );
    posicion = vec3( matrizModeladoVision * vec4(p, 1) );
    gl_Position = matrizModeladoVisionPerspectiva * vec4(posicion, 1);
}