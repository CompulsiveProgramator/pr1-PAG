#version 410

uniform vec3 Ia;
uniform vec3 Ka;

vec3 luzAmbiente()
{
    return (Ia * Ka);
}

out vec3 fragColor;

void main()
{
    fragColor = luzAmbiente();
}