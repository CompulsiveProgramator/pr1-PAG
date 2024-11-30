#version 410

// Para este fragment shader, usamos mi primera subrutina!
// para elegir con que color se pinta el pixel

// El color difuso del material
uniform vec3 colorDifuso;

// Este es el nombre de la subrutina
subroutine vec3 calcularColor();

// Con este uniform seleccionamos la implemtacion desde el Shader Program
subroutine uniform calcularColor metodoColorElegido;


subroutine(calcularColor)
vec3 colorRojo()
{
        return vec3(1.0, 0.0, 0.0);
}

subroutine(calcularColor)
vec3 colorDifuso()
{
        return colorDifuso; //Este es el color difuso, del material asignado al modelo ;)
}

out vec3 colorFragmento;

void main()
{
    colorFragmento = metodoColorElegido();
}