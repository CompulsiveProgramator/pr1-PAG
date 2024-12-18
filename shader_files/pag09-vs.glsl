// VERTEX SHADER
#version 410

layout (location = 0) in vec3 posicion;   // Atributo 0
layout (location = 1) in vec3 normal;     // Atributo 1
layout (location = 2) in vec2 cTextura;   // Atributo 2

uniform mat4 matrizModeladoVisionPerspectiva;
uniform mat4 matrizModeladoVision;

out salidaVS
{  vec3 posicionV;
   vec3 normalV;
   vec2 cTexturaV;
} salida;

void main ()
{  salida.posicionV = vec3 ( matrizModeladoVision * vec4 ( posicion, 1 ) );
   salida.normalV = vec3 ( matrizModeladoVision * vec4 ( normal, 0 ) );
   salida.cTexturaV = cTextura;   // Las coordenadas de textura se pasan tal cual al fragment shader
   gl_Position = matrizModeladoVisionPerspectiva * vec4 ( posicion, 1 );
}