#version 410

layout ( location = 0 ) in vec3 posicion;
layout ( location = 1 ) in vec3 normal;

uniform mat4 matrizModeladoVisionPerspectiva;
uniform mat4 matrizModeladoVision;

// Las variables transformadas en el espacio de vision, que van al rasterizador, y de el
// van interpoladas a cada fragmento del fragment shader ;)
out vec4 posicionV;
out vec4 normalV;

void main()
{
    normalV = matrizModeladoVision * vec4(normal, 0);
    posicionV = matrizModeladoVision * vec4(posicion, 1);
    gl_Position = matrizModeladoVisionPerspectiva * vec4(posicion, 1);
}