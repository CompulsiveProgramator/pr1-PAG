cmake_minimum_required(VERSION 3.27)
project(Pr1)

set(CMAKE_CXX_STANDARD 17)

file( GLOB GLAD_FILES glad/src/*.c ) # Para agregar como un nombre al add executables los archivos
file( GLOB IMGUI_FILES imgui/*.cpp)

add_executable(Pr1 main.cpp
        Renderer/Renderer.cpp
        Renderer/Renderer.h
        ${GLAD_FILES}
        ${IMGUI_FILES}
        GUI.cpp
        GUI.h
        ShaderProgram.cpp
        ShaderProgram.h
        Camara.cpp
        Camara.h
        Constantes.h
        ventanas-gui/VentanaSeleccionColor.cpp
        ventanas-gui/VentanaSeleccionColor.h
        ventanas-gui/VentanaLog.cpp
        ventanas-gui/VentanaLog.h
        ventanas-gui/Ventana.h
        ventanas-gui/VentanaSeleccionShaderProgram.cpp
        ventanas-gui/VentanaSeleccionShaderProgram.h
        ventanas-gui/VentanaMovimientoCamara.cpp
        ventanas-gui/VentanaMovimientoCamara.h
        Constantes.cpp
        Malla.cpp
        Malla.h
        Modelo.cpp
        Modelo.h
)

# Para que Cmake encuentre los bonitos paquetes:
find_package(opengl_system)
find_package(glad)
find_package(glfw3)
find_package(glm)

# Los dos siguiente comandos de CMake son los que explico Fran, para poder usar la biblioteca compilada de assimp, con su archivo .dll ;)

# Este comando es para crear una variable, con la ruta del archivo .dll
set(ASSIMP_DLL_PATH "${CMAKE_SOURCE_DIR}/Bibliotecas_DLL")

# Enlazamos la .dll de Assimp con nuestro proyecto
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${ASSIMP_DLL_PATH}/libassimp-5d.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_subdirectory(assimp)
target_link_libraries(${PROJECT_NAME} assimp::assimp)

# Para poder agregar directamente al main las librerias con <>
target_include_directories(${PROJECT_NAME} PUBLIC glad/include imgui)

# Para que Cmake agregue las librerias "descargadas con Conan" al proyecto
target_link_libraries(${PROJECT_NAME} opengl::opengl glad::glad glfw glm::glm "-static")

# -static Hacemos que se enlace de forma estatica toodo en el proyecto

# DLL Dynamic Link Libraries se usa para enlazar en tiempo de ejecucion con las bibliotecas del proyecto
# asi el ejecutable del programa es más chikito
# Ya que si compilamos y enlazamos toodas las bibliotecas de una aplicación en un solo ejecutable, este puede ser enormeeeeee
# Para mas info : https://es.wikipedia.org/wiki/Biblioteca_de_enlace_din%C3%A1mico