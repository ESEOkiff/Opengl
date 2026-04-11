cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)


set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include)

add_executable(app
    src/main.cpp
    src/engine/engine.cpp
    src/renderer/shader/shader.cpp
    src/renderer/mesh/Mesh.cpp
    src/renderer/draw/Renderer.cpp
    src/engine/transform.cpp
    src/debuging/errorReporting.cpp
    src/engine/input.cpp
)

target_link_libraries(app 
    OpenGL::GL
    glfw
    glad
)
