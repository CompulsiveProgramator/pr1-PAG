cmake_minimum_required(VERSION 3.27)
project(Pr1)

set(CMAKE_CXX_STANDARD 17)

file( GLOB GLAD_FILES glad/src/*.c ) # Para agregar como un nombre al add executables los archivos
file( GLOB IMGUI_FILES imgui/*.cpp)

add_executable(Pr1 main.cpp
        utilities/Renderer.cpp
        utilities/Renderer.h
        ${GLAD_FILES}
        ${IMGUI_FILES}
        utilities/lodepng.cpp
        utilities/GUI.cpp
        utilities/GUI.h
        utilities/ShaderProgram.cpp
        utilities/ShaderProgram.h
        utilities/Camara.cpp
        utilities/Camara.h
        utilities/Constantes.h
        ventanas-gui/VentanaSeleccionColor.cpp
        ventanas-gui/VentanaSeleccionColor.h
        ventanas-gui/VentanaLog.cpp
        ventanas-gui/VentanaLog.h
        ventanas-gui/Ventana.h
        ventanas-gui/VentanaSeleccionShaderProgram.cpp
        ventanas-gui/VentanaSeleccionShaderProgram.h
        ventanas-gui/VentanaMovimientoCamara.cpp
        ventanas-gui/VentanaMovimientoCamara.h
        utilities/Constantes.cpp
        utilities/Malla.cpp
        utilities/Malla.h
        utilities/Modelo.cpp
        utilities/Modelo.h
        ventanas-gui/VentanaSelectorModelo.cpp
        ventanas-gui/VentanaSelectorModelo.h
        ventanas-gui/VentanaTransformacionesModelos.cpp
        ventanas-gui/VentanaTransformacionesModelos.h
        utilities/Material.cpp
        utilities/Material.h
        ventanas-gui/VentanaParametrosCamara.cpp
        ventanas-gui/VentanaParametrosCamara.h
        utilities/Luz.cpp
        utilities/Luz.h
        utilities/Textura.cpp
        utilities/Textura.h
)

# Para que Cmake encuentre los bonitos paquetes:
find_package(opengl_system)
find_package(glfw3)
find_package(glm)

# Los dos siguiente comandos de CMake son los que explico Fran, para poder usar la biblioteca compilada de assimp, con su archivo .dll ;)

# Este comando es para crear una variable, con la ruta del archivo .dll
#set(ASSIMP_DLL_PATH "${CMAKE_SOURCE_DIR}/Bibliotecas_DLL")

# Enlazamos la .dll de Assimp con nuestro proyecto
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#       COMMAND ${CMAKE_COMMAND} -E copy_if_different
#       "${ASSIMP_DLL_PATH}/libassimp-5d.dll"
#       $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#add_subdirectory(assimp) # Esto le dice a CMake que busque un Cmakelist.txt en el subdirectorio de assimp, para que tambien se haga la build de assimp ;)

# Ahora, agregamos al ejecutable de la "libreria" de assimp, al del proyecto principal
target_link_libraries(${PROJECT_NAME} PUBLIC opengl::opengl glfw glm::glm)

# Para RenderDoc, poner -static en target_link_libraries() al final para que el ejecutable del proyecto tenga una "copia" de todas las
# librerias externas/internas ( .dll ) y así el ejecutable es más grande, pero, podemos llevarnoslo a donde queramos!!!

# PUBLIC es para que si hacemos un ejecutable que dependa de este, necesite las librerias de este tambien

# Agregamos al ejecutable de nuestro programa, los directorios donde se encuentran los archivos .h , para que puedan ser encontrados por nuestro ejecutable
target_include_directories(${PROJECT_NAME} PUBLIC glad/include imgui)



# DLL Dynamic Link Libraries es el archivo compilado de una biblioteca, que podemos incluir en otro proyecto para usarlo
# Lo invento Windows
# Para mas info : https://es.wikipedia.org/wiki/Biblioteca_de_enlace_din%C3%A1mico