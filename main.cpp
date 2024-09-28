#include <iostream>
#include <cstdlib>

// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

///Los callbacks:

//Funcion para el primer ejercicio de la practica
void ajustar_color_pantalla( GLFWwindow *window, double xoffset, double yoffset);

// - Esta función callback será llamada cuando GLFW produzca algún error
void error_callback ( int errno, const char* desc )
{
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
}

// - Esta función callback será llamada cada vez que el área de dibujo
// OpenGL deba ser redibujada.
void window_refresh_callback ( GLFWwindow *window )
{
    PAG::Renderer::getInstancia()->refrescar(); ///Para la 2da practica, usamos el Renderer

    // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
    // intercambia el buffer back (que se ha estado dibujando) por el
    // que se mostraba hasta ahora front. Debe ser la última orden de
    // este callback
    glfwSwapBuffers ( window );
    std::cout << "Refresh callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se cambie el tamaño
// del área de dibujo OpenGL.
void framebuffer_size_callback ( GLFWwindow *window, int width, int height )
{
    glViewport ( 0, 0, width, height );
    std::cout << "Resize callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse una tecla
// dirigida al área de dibujo OpenGL.
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    { glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    std::cout << "Key callback called" << std::endl;
}

// - Esta función callback será llamada cada vez que se pulse algún botón
// del ratón sobre el área de dibujo OpenGL.
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods )
{
    if ( action == GLFW_PRESS )
    { std::cout << "Pulsado el boton: " << button << std::endl;
    }
    else if ( action == GLFW_RELEASE )
    { std::cout << "Soltado el boton: " << button << std::endl;
    }
}

// - Esta función callback será llamada cada vez que se mueva la rueda
// del ratón sobre el área de dibujo OpenGL.
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset )
{
    std::cout << "Movida la rueda del raton " << xoffset
            << " Unidades en horizontal y " << yoffset
            << " unidades en vertical" << std::endl;

    ajustar_color_pantalla( window, xoffset, yoffset);
}

/**
 * Funcion para ajustar el color de la pantalla segun el movimiento del raton. Si vamos arriba se vuelve mas roja, y si vamos hacia abajo se vuelve menos rojo
 * @param window La ventana
 * @param xoffset El desplazamiento horizontal (No lo usamos)
 * @param yoffset El desplazamiento vertical
 */
void ajustar_color_pantalla( GLFWwindow *window, double xoffset, double yoffset){
    //Si es arriba la ponemos roja, y si vamos abajo la ponemos verde
    GLfloat color[4]; // El color a poner en la pantalla, glfloat es el tipo de dato usado para almacenar flotantes en OpenGL
    glGetFloatv(GL_COLOR_CLEAR_VALUE, color); // Esta funcion glGetFloatv, nos pasa el valor localizado en la direccion de memoria del primer parametro, al segundo parametro ;)

    if(yoffset > 0){
        color[0] += 0.01;
        color[0] > 1.0 ? color[0] = 1.0 : color[0] = color[0];
        //color[1] += 0.1;
        //color[1] > 1.0 ? color[1] = 1.0 : color[1] = color[1];
        //color[2] += 0.01;
        //color[2] > 1.0 ? color[2] = 1.0 : color[2] = color[2];
        //Para la opacidad
        //color[3] += 0.1;
        //color[3] > 1.0 ? color[3] = 1.0 : color[3] = color[3];
    }else{
        color[0] -= 0.01;
        color[0] < 0.0 ? color[0] = 0.0 : color[0] = color[0];
        //color[1] -= 0.1;
        //color[1] < 0.0 ? color[1] = 0.0 : color[1] = color[1];
        //color[2] -= 0.01;
        //color[2] > 0.0 ? color[2] = 0.0 : color[2] = color[2];
        //color[3] -= 0.1;
        //color[3] > 0.0 ? color[3] = 0.0 : color[3] = color[3];
    }

    glClearColor(color[0], color[1], color[2], color[3]);
}

int main()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;



    std::cout << "Starting Application PAG - Prueba 01" << std::endl;

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback );

    // - Inicializa GLFW. Es un proceso que sólo debe realizarse una vez en la aplicación
    if ( glfwInit () != GLFW_TRUE )
    { std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // - Definimos las características que queremos que tenga el contexto gráfico
    // OpenGL de la ventana que vamos a crear. Por ejemplo, el número de muestras o el
    // modo Core Profile.
    glfwWindowHint ( GLFW_SAMPLES, 4 ); // - Activa antialiasing con 4 muestras.
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // - Esta y las 2
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 ); // siguientes activan un contexto
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 ); // OpenGL Core Profile 4.1.

    // - Definimos el puntero para guardar la dirección de la ventana de la aplicación y
    // la creamos
    GLFWwindow *window;

    // - Tamaño, título de la ventana, en ventana y no en pantalla completa,
    // sin compartir recursos con otras ventanas.
    window = glfwCreateWindow ( 1024, 576, "PAG Introduction", nullptr, nullptr );

    // - Comprobamos si la creación de la ventana ha tenido éxito.
    if ( window == nullptr )
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
        return -2;
    }

    // - Hace que el contexto OpenGL asociado a la ventana que acabamos de crear pase a
    // ser el contexto actual de OpenGL para las siguientes llamadas a la biblioteca
    glfwMakeContextCurrent ( window );

    // - Ahora inicializamos GLAD.
    if ( !gladLoadGLLoader ( (GLADloadproc) glfwGetProcAddress ) )
    {
        std::cout << "GLAD initialization failed" << std::endl;
        glfwDestroyWindow ( window ); // - Liberamos los recursos que ocupaba GLFW.
        window = nullptr;
        glfwTerminate ();
        return -3;
    }

    // - Interrogamos a OpenGL para que nos informe de las propiedades del contexto
    // 3D construido.
    std::cout << glGetString ( GL_RENDERER ) << std::endl
              << glGetString ( GL_VENDOR ) << std::endl
            << glGetString ( GL_VERSION ) << std::endl
            << glGetString ( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );

    // - Establecemos un gris medio como color con el que se borrará el frame buffer.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glClearColor ( 0.6, 0.6, 0.6, 1.0 );

    // - Le decimos a OpenGL que tenga en cuenta la profundidad a la hora de dibujar.
    // No tiene por qué ejecutarse en cada paso por el ciclo de eventos.
    glEnable ( GL_DEPTH_TEST );

    // Aquí "window" es el puntero a la ventana GLFW (GLFWwindow*)
    ImGui_ImplGlfw_InitForOpenGL ( window, true );
    ImGui_ImplOpenGL3_Init ();

    // - Ciclo de eventos de la aplicación. La condición de parada es que la
    // ventana principal deba cerrarse. Por ejemplo, si el usuario pulsa el
    // botón de cerrar la ventana (la X).
    while ( !glfwWindowShouldClose ( window ) )
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Se dibujan los controles de Dear ImGui
        // Aquí va el dibujado de la escena con instrucciones OpenGL
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );

        ImGui::SetNextWindowPos( ImVec2 (10, 10), ImGuiCond_Once);

        if ( ImGui::Begin ( "Mensajes" ) )
        { // La ventana está desplegada
            ImGui::SetWindowFontScale ( 1.0f ); // Escalamos el texto si fuera necesario
            // Pintamos los controles
        }
        // Si la ventana no está desplegada, Begin devuelve false
        ImGui::End ();

        // - GLFW usa un doble buffer para que no haya parpadeo. Esta orden
        // intercambia el buffer back (en el que se ha estado dibujando) por el
        // que se mostraba hasta ahora (front).
        glfwSwapBuffers ( window );

        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents ();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application pag prueba" << std::endl;

    ///Para Im_Gui se liberan los recursos
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext ();

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
}