#version 410

//El color ambiental de la luz
uniform vec3 Ia;

//El colo ambiental del material
uniform vec3 Ka;

// Para obtener el color segun el modelo de reflexion "ambiental"
vec3 luzA()
{
    return Ia * Ka;
}

out vec3 fragColor;

void main()
{
    fragColor = luzA();
}