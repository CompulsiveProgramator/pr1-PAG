# Prácticas-PAG
### Autor: Adrián González Almansa
### Curso 24/25
## Práctica 3
He realizado bastantes cambios para implementar la practica 3, principalmente dentro de la clase Renderer.
Agregué toda la funcionalidad con los shader programs, como el vertex/fragment shader, el VAO del triangulo, y su VBO e IBO.
En UML ahora mismo la aplicación funciona así:

<img src="images/pr2UML.png" width=800px>

Tanto Renderer como GUI son Singletons, Renderer compila y ejecuta el shader program desde creaShaderProgram() y refrescar(), respectivamente.
GUI pinta la interfaz de usuario con el metodo refrescar(), y tiene los métodos setColor() y agregarMensajeLog(), para el dibujado de las ventanas de
ImGui.

Respecto a la cuestion planteada al final del 3er guión, del triangulo que se escala al tamaño de la ventana, esto ocurre ya que las coordenadas que damos en el VBO para la posicion
de cada vértice, son después de hacer la tranformación de proyección en el espacio normalizado. Las coordenadas de ese espacio hay que traducirlas al espacio de viewport (nuestra bonita ventana),
y esa traducción se hace siguiendo la siguiente formula:

<img src="images/pr3.png" width=400px>

Luego cuanto mayor sea la ventana de la aplicación mayor serán "w" y "h", por lo que mayor serán las coordenadas de cada punto, y por ello más grande será el triángulo.

## Práctica 4
Para esta práctica solo hemos tenido que desacoplar de la clase Renderer el funcionamiento del Shader Program,
y para ello he creado una clase llamada ShaderProgram que se encarga de ello. Incluye el funcionamiento del 
Vertex Shader y del Fragment Shader en su interior, pero en la siguiente práctica desacoplaré esto. El UML con la idea del proyecto actual es el siguiente:

<img src="images/pr4UML.png" width=900px>

## Práctica 5
Para esta práctica hemos tenido que implementar una camara virtual, que se puede mover con el ratón, teclado y con controles
de ImGui

He movido los archivos de shaders (tanto vertex como fragment) a una carpeta llamada "shader_files", por lo que para usar el programa "pag03" hay que hacer lo siguiente:
<img src="images/imagen_como_usar_ventana_shader_program.png" width=1080px>

Una vez hecho lo anterior, he creado la clase PAG::Camara que alberga todo el funcionamiento de la camara, y esta clase se comunica con la clase ShaderProgram para 
poder hacer las transformaciones necesarias de visión y perspectiva, en el modelo que se va a dibujar. Desde los callbacks del main se comunica a la cámara de 
la aplicación el movimiento que ha de hacer (dolly, crane, ...), concretamente desde los callbacks para desplazamiento del raton, y para pulsar una tecla, que son
cursorPosition_callback() y key_callback() respectivamente.
Esto lo hago ya que así cuando ocurra un evento se notifica automaticamente a la cámara, que es como debe ser

La idea de comunicar los movimientos a la cámara directamente desde el main, lo veo lo más sencillo de entender y más simple posible

Para las ventanas de la aplicación, he creado una clase abstracta llamada "Ventana", y de esta heredan todas las ventanas que he creado con ImGui, siendo la última
la de gestion de movimiento de cámara, con un simple selector de tipo de movimiento, y botones para actualizarla:

<img src="images/ventana_movimiento_camara.png">

La version actual en un diagrama de clases UML de la aplicación, es la siguiente:

<img src="images/pr5UML.png">


## Práctica 6
Vamos a por esta práctica, que consiste en desacoplar del Shader Program el funcionamiento del modelo. Para ello, voy a empezar haciendo una clase PAG::Modelo
que contenga por supuesto, los datos como vertices, normales, y matriz de modelado que definen al modelo.