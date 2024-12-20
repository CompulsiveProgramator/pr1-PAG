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
in vec3 posicion;
in vec3 normal;

subroutine vec3 iluminacion();

subroutine uniform iluminacion metodoIluminacion;

subroutine (iluminacion)
vec3 luzAmbiental()
{
    return Ia * Ka;
}

subroutine (iluminacion)
vec3 luzPuntual()
{
        vec3 n = normalize( normal ); // La normal
        vec3 l = normalize( lightPosition - posicion ); // Vector que va a la fuente de luz
        //Como la camara esta en el (0,0), el vector que va desde el punto a la camara es -posicion
        vec3 v = normalize( -posicion ); // El vector posicion del observador
        vec3 r = reflect( -l, n ); // El rebote de la luz

        vec3 diffuse = ( Id * Kd * max(dot(l,n), 0.0) );
        vec3 specular;

        specular = ( Is * Ks * pow( max(dot(v,r), 0.0) , exponenteEspecular ) );

        return diffuse + specular;
}

subroutine (iluminacion)
vec3 luzDireccional()
{
    vec3 n = normalize( normal ); // La normal
    vec3 l = normalize( -direccion ); // Vector que va a la fuente de luz
    //Como la camara esta en el (0,0), el vector que va desde el punto a la camara es -posicion
    vec3 v = normalize( -posicion ); // El vector posicion del observador
    vec3 r = reflect( -l, n ); // El rebote de la luz

    vec3 diffuse = ( Id * Kd * max(dot(l,n), 0.0) );
    vec3 specular;

    specular = ( Is * Ks * pow( max(dot(v,r), 0.0) , exponenteEspecular ) );

    return diffuse + specular;
}

subroutine (iluminacion)
vec3 luzFocal()
{
    vec3 n = normalize( normal );
    vec3 l = normalize( lightPosition - posicion ); // El vector que va de la posicion de la luz a la del fragment a iluminar !!!
    vec3 v = normalize( -posicion ); //La posicion de la camara (0, 0) tras la transformacion de vision ;)
    vec3 r = reflect ( -l, n ); // El rebote de la luz del foco
    vec3 d = normalize( direccion ); // La direccion del foco

    // dot(d, -l) es el coseno entre la direccion del foco y la del objeto ya que de "d" y "-l" estan normalizados
    if( dot(d, -l) < cos(angulo) )
    {
        return vec3(0, 0, 0);
    }else{
        vec3 diffuse = ( Id * Kd * max(dot(l,n), 0.0) );
        vec3 specular;
        specular = ( Is * Ks * pow( max(dot(v,r), 0.0) , exponenteEspecular ) );

        return diffuse + specular;
    }
}

out vec3 fragColor;

void main()
{
    fragColor = metodoIluminacion();
}