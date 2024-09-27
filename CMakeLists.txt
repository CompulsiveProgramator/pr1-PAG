cmake_minimum_required(VERSION 3.27)
project(Pr1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Pr1 main.cpp
        Renderer.cpp
        Renderer.h
)

# Para que Cmake encuentre los bonitos paquetes:
find_package(opengl_system)
find_package(glad)
find_package(glfw3)

# Para que Cmake agregue las librerias al proyecto
target_link_libraries(${PROJECT_NAME} opengl::opengl glad::glad glfw)