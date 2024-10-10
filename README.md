# Prácticas-PAG
## Práctica 3
He realizado bastantes cambios para implementar la practica 3, principalmente dentro de la clase Renderer.
Agregué toda la funcionalidad con los shader programs, como el vertex/fragment shader, el VAO del triangulo, y su VBO e IBO
En UML ahora mismo la aplicación funciona así:

<img src="UMLdiagram.png" width=800px>

Tanto Renderer como GUI son Singletons, Renderer compila y ejecuta el shader program desde creaShaderProgram() y refrescar(), respectivamente.
GUI pinta la interfaz de usuario con el metodo refrescar(), y tiene los métodos setColor() y agregarMensaje(), para el dibujado de las ventanas de
ImGui.

Respecto a la cuestion planteada al final del 3er guión, del triangulo que se escala al tamaño de la ventana, esto ocurre ya que las coordenadas que damos en el VBO para la posicion
de cada vértice, son después de hacer la tranformación de proyección en el espacio normalizado. Las coordenadas de ese espacio hay que traducirlas al espacio de viewport (nuestra bonita ventana),
y esa traducción se hace siguiendo la siguiente formula:

<img src="pr3.png" width=400px>

Luego cuanto mayor sea la ventana de la aplicación mayor serán "w" y "h", por lo que mayor serán las coordenadas de cada punto, y por ello más grande será el triángulo.
