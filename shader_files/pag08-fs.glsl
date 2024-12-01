#version 410

// Los uniforms para las propiedades de la luz ;)
uniform vec3 Ia; // Color ambiental (Solo luz ambiente)
uniform vec3 Id; // Color difuso
uniform vec3 Is; // Colo especular
uniform float exponenteEspecular; // Para tunear el brillo de la luz especular
uniform vec3 lightPosition; // La posicion de la luz (Luz puntual o focal)
uniform vec3 direccion; // La direccion de la luz (Luz direccional o focal)
uniform float angulo; // El angulo de apertura de una luz focal

// Los uniforms para el material
uniform vec3 Ka; // Color ambiental
uniform vec3 Kd; // Color difuso
uniform vec3 Ks; // Color especular

// Varibles que vienen del rasterizador:
in vec4 posicionV;
in vec4 normalV;

subroutine vec3 iluminacion();

subroutine uniform iluminacion metodoIluminacion;

subroutine (iluminacion)
vec3 luzAmbiental()
{
    return Ia * Ka;
}

out vec3 fragColor;

void main()
{
    fragColor = metodoIluminacion();
}