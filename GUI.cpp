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
    this->window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext ();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui_ImplGlfw_InitForOpenGL ( this->window, true );
    ImGui_ImplOpenGL3_Init ();
}

/**
 * Destructor de la clase
 */
PAG::GUI::~GUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext ();
    std::cout << "aaaa";
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

    Renderer *instanciaRender = Renderer::getInstancia(this->window);

    // Ventana para pillar el color de fondo:
    ImGui::SetNextWindowPos ( ImVec2 (10, 10), ImGuiCond_Once );

    ImGui::Begin("Color picker del fondo");
    float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.80f;
    ImGui::SetNextItemWidth(w);
    GLfloat *color = instanciaRender->getColorFondo();
    ImGui::Text("Selecciona el color de fondo:");
    ImGui::ColorPicker3("##MyColor##6", (float*) color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
    instanciaRender->setColorFondo(color);
    ImGui::End();

    //ToDo Ventana de control de mensajes
    ImGui::SetNextWindowPos ( ImVec2 (600, 10), ImGuiCond_Once );

    ImGui::Begin("Mensajes consola");
    for(int i = 0 ; i < log.size() ; i++){
        ImGui::Text(log[i].c_str());
    }
    ImGui::End();


    // Aquí va el dibujado de la escena con instrucciones OpenGL
    instanciaRender->refrescar();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData ( ImGui::GetDrawData() );
}

/**
 * Metodo usado para postear una entrada al blog
 * @param cad La cadena que se va a agregar al log
 */
void PAG::GUI::postEntradaLog(std::string cad)
{
    log.push_back(cad);
}
