cmake_minimum_required(VERSION 3.27)
project(Pr1)

set(CMAKE_CXX_STANDARD 17)

file( GLOB GLAD_FILES glad/src/*.c ) # Para agregar como un nombre al add executables los archivos
file( GLOB IMGUI_FILES imgui/*.cpp)

add_executable(Pr1 main.cpp
        Renderer.cpp
        Renderer.h
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
        Modelo.cpp
        Modelo.h
)

# Para que Cmake encuentre los bonitos paquetes:
find_package(opengl_system)
find_package(glad)
find_package(glfw3)
find_package(glm)
find_package(assimp)

# Para poder agregar directamente al main las librerias con <>
target_include_directories(${PROJECT_NAME} PUBLIC glad/include imgui)

# Para que Cmake agregue las librerias "descargadas con Conan" al proyecto
target_link_libraries(${PROJECT_NAME} opengl::opengl glad::glad glfw glm::glm assimp::assimp "-static")

# -static Hacemos que se enlace de forma estatica toodo en el proyecto

# DLL Dynamic Link Libraries se usa para enlazar en tiempo de ejecucion con las bibliotecas del proyecto
# asi el ejecutable del programa es más chikito
# Ya que si compilamos y enlazamos toodas las bibliotecas de una aplicación en un solo ejecutable, este puede ser enormeeeeee
# Para mas info : https://es.wikipedia.org/wiki/Biblioteca_de_enlace_din%C3%A1mico