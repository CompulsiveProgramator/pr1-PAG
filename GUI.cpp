//
// Created by secre on 28/09/2024.
//

#include "GUI.h"

PAG::GUI* PAG::GUI::instancia = nullptr; //Para inicializar la instancia como nula

/**
 * Constructor por defecto de la clase, que inicializa toodo para que ImGui funcione
 * @param window Es la ventana sobre la que se pintará la GUI
 */
PAG::GUI::GUI(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL ( window, true );
    ImGui_ImplOpenGL3_Init ();
}

/**
 * Destructor de la clase
 */
PAG::GUI::~GUI() {

}

/**
 * Metodo para obtener la unica instancia de la clase
 * @return
 */
PAG::GUI *PAG::GUI::getInstancia(GLFWwindow *window) {
    if(!instancia){
        instancia = new GUI(window);
    }

    return instancia;
}

/**
 * Metodo usado para pintar la GUI sobre el viewport de OpenGL ;)
 */
void PAG::GUI::refrescar() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    Renderer *instanciaRender = Renderer::getInstancia();

    // Se dibujan los controles de Dear ImGui
    //ToDo Control de color de fondo en triangulo RGB
    float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.80f;
    ImGui::SetNextItemWidth(w);
    GLfloat *color = instanciaRender->getColorFondo();
    ImGui::ColorPicker3("##MyColor##6", (float*) color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
    instanciaRender->setColorFondo(color);

    //ToDo Ventana de control de mensajes

    // Aquí va el dibujado de la escena con instrucciones OpenGL
    PAG::Renderer::getInstancia()->refrescar();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
}
