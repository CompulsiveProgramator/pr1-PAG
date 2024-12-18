// FRAGMENT SHADER
#version 410

in salidaVS
{  vec3 posicionV;
   vec3 normalV;
   vec2 cTexturaV;
} entrada;

uniform vec3 Ks; // Coeficiente especular material
uniform float exponenteEspecular; // Exponente especular
uniform vec3 Id; // Luz difusa
uniform vec3 Is; // Luz especular
uniform vec3 lightPosition; // Posicion de la luz

uniform sampler2D muestreador;   // Sampler para comunicar con la unidad de textura

out vec4 colorFragmento;

vec3 luzPuntual ()
{  vec3 color = texture ( muestreador, entrada.cTexturaV ).rgb;   // Acceso a la textura. Descarta el valor de alfa
   vec3 n = normalize ( entrada.normalV );

   vec3 l = normalize (lightPosition - entrada.posicionV );
   vec3 v = normalize ( -entrada.posicionV );
   vec3 r = reflect ( -l, n );

   vec3 colorD = Id * color * max (dot (l, n ), 0 );   // Uso del color tomado de la textura
   //vec3 colorS = Is * Ks.rgb * pow (max (dot (r, v ), 0 ), exponenteEspecular);

   return ( color );
}

void main ()
{  colorFragmento = vec4 ( luzPuntual(), 1 );
}