#version 410

layout ( location = 0 ) posicion;

uniform mat4 matrizModeladoVisionPerspectiva;

void main()
{
    gl_Position = matrizModeladoVisionPerspectiva * vec4(posicion, 1);
}