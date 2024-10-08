#include <iostream>
#include <cstdlib>

// IMPORTANTE: El include de GLAD debe estar siempre ANTES de el de GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"
#include "GUI.h"

/*
 * Los callbacks estan en el main para GLFW, y desde ellos llamamos a Renderer y GUI respectivamente
 */

/**
 * Callback llamado si hay un error en GLFW
 * @param _errno El error
 * @param desc
 */
void error_callback ( int errno, const char* desc ) {
    std::string aux (desc);
    std::cout << "Error de GLFW número " << errno << ": " << aux << std::endl;
    std::string cad = "Error de GLFW número " + std::to_string(errno) + ": " + aux + "\n";
    PAG::GUI::getInstancia().agregarMensaje(cad);
}

/**
 * Callback llamado cuando redimensionamos la pantalla
 * @param window
 */
void window_refresh_callback ( GLFWwindow *window ) {
    PAG::Renderer::getInstancia().refrescar();
    glfwSwapBuffers(window); //La funcion para intercambiar los buffers, y que no haya parpadeo
    std::string aux = "Termina el callback de refresco\n";
    PAG::GUI::getInstancia().agregarMensaje(aux);
}

/**
 * Callback llamado cuando redimensionamos la pantalla
 * El framebuffer es un "mapa de bits" que representa los pixeles de la ventana de la app
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback ( GLFWwindow *window, int width, int height ) {
    std::string aux;
    aux = "Framebuffer llamado\n";
    PAG::GUI::getInstancia().agregarMensaje(aux);
    PAG::Renderer::getInstancia().modificarTamañoVentana(width, height);
}

/**
 * Callback llamado cuando pulsamos una tecla del teclado
 * @param window
 * @param key
 * @param scancode
 * @param action
 * @param mods
 */
void key_callback ( GLFWwindow *window, int key, int scancode, int action, int mods ) {
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        ImGuiIO& io = ImGui::GetIO();
        io.AddKeyEvent(ImGuiKey_Escape, true);
    }
}

/**
 * Callback llamado cuando pulsamos el clic del raton
 * @param window
 * @param button
 * @param action
 * @param mods
 */
void mouse_button_callback ( GLFWwindow *window, int button, int action, int mods ) {
    if ( action == GLFW_PRESS )
    {
        std::string cad = "Pulsado el boton: ";
        cad.push_back(char(button + 48));
        cad += "\n";
        PAG::GUI::getInstancia().agregarMensaje(cad);
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button, GLFW_PRESS);
    }
    else if ( action == GLFW_RELEASE )
    {
        std::string cad = "Soltado el boton: ";
        cad.push_back(char(button + 48)); //Para hacer la conversion a caracter
        cad += "\n";
        PAG::GUI::getInstancia().agregarMensaje(cad);
        ImGuiIO& io = ImGui::GetIO();
        io.AddMouseButtonEvent(button, GLFW_RELEASE);
    }


}

/**
 * Callback llamado cuando movemos la rueda del raton
 * @param window
 * @param xoffset
 * @param yoffset
 */
void scroll_callback ( GLFWwindow *window, double xoffset, double yoffset ) {
    std::string cad;
    //Para convertir de int,float,double a string, usar std::to_string(). Se puede usar desde C++ 11
    cad = "Movida la rueda del raton" + std::to_string(xoffset) + " unidades en horizontal y " + std::to_string(yoffset) + " unidades en vertical\n";
    PAG::GUI::getInstancia().agregarMensaje(cad);

    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseWheelEvent(xoffset, yoffset);
}

int main()
{
    std::cout << "Starting Application PAG - Prueba 03" << std::endl;

    // - Este callback hay que registrarlo ANTES de llamar a glfwInit
    glfwSetErrorCallback ( (GLFWerrorfun) error_callback);

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

    // - Registramos los callbacks que responderán a los eventos principales
    glfwSetWindowRefreshCallback ( window, window_refresh_callback );
    glfwSetFramebufferSizeCallback ( window, framebuffer_size_callback );
    glfwSetKeyCallback ( window, key_callback );
    glfwSetMouseButtonCallback ( window, mouse_button_callback );
    glfwSetScrollCallback ( window, scroll_callback );

    /// Inicialización  de DearIMGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    ///Obtenemos las instancias de los Singletons:
    PAG::Renderer instanciaRenderer = PAG::Renderer::getInstancia();
    PAG::GUI instanciaGUI = PAG::GUI::getInstancia();

    instanciaGUI.setColor(instanciaRenderer.getColorFondo());

    /// Llamamos al shader program y creamos el modelo que se le pasara
    try{
        instanciaRenderer.creaShaderProgram();
    }catch (std::string &message){
        PAG::GUI::getInstancia().agregarMensaje(message); //Importantisimo llamar el metodo getInstancia() cada vez que queramos acceder a la instancia del Singleton
        //instanciaGUI.agregarMensaje() no funciona aqui curiosamente ;3
    }
    instanciaRenderer.creaModelo();

    instanciaRenderer.inicializaOpenGL(); //Inicializamos los parametros globales de OpenGL
    //Ciclo de eventos
    while ( !glfwWindowShouldClose ( window ) )
    {
        instanciaRenderer.refrescar(); //Primero se dibuja el Renderer
        instanciaGUI.refrescar(); //La GUI se dibuja lo ultimo, porque es lo que mas arriba está ;)

        //Para ver lo que se ha pintado en la llamada de justo arriba
        glfwSwapBuffers ( window );

        // - Obtiene y organiza los eventos pendientes, tales como pulsaciones de
        // teclas o de ratón, etc. Siempre al final de cada iteración del ciclo
        // de eventos y después de glfwSwapBuffers(window);
        glfwPollEvents ();
    }

    // - Una vez terminado el ciclo de eventos, liberar recursos, etc.
    std::cout << "Finishing application pag prueba" << std::endl;

    /// Liberamos los recursos de ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext ();

    glfwDestroyWindow ( window ); // - Cerramos y destruimos la ventana de la aplicación.
    window = nullptr;
    glfwTerminate (); // - Liberamos los recursos que ocupaba GLFW.
}