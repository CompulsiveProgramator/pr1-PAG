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
)

# Para que Cmake encuentre los bonitos paquetes:
find_package(opengl_system)
find_package(glad)
find_package(glfw3)
find_package(glm)

# Para poder agregar directamente al main las librerias con <>
target_include_directories(${PROJECT_NAME} PUBLIC glad/include imgui)

# Para que Cmake agregue las librerias "descargadas con Conan" al proyecto
target_link_libraries(${PROJECT_NAME} opengl::opengl glad::glad glfw glm::glm "-static")

# DLL Dynamic Link Libraries se usa para enlazar en tiempo de ejecucion con las librerias de "fuera del proyecto" ???