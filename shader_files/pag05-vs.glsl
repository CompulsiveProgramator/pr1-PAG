#version 410

layout (location = 0) in vec3 posicion;
layout (location = 1) in vec3 color;

uniform mat4 matrizModeladoVision;
uniform mat4 matrizModeladoVisionPerspectiva;

out vec3 colorF;

void main()
{
    gl_Position = matrizModeladoVisionPerspectiva * vec4(posicion, 1);
    colorF = color;
}