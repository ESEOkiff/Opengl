#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./engine.hpp"
#include "../renderer/shader/shader.hpp"
#include "../renderer/draw/Renderer.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Engine::Engine(int wHeigh, int wWidth, const char* wTitle, bool isWresizable)
{   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, isWresizable);
    window = glfwCreateWindow(wWidth, wHeigh, wTitle, NULL, NULL);
    
    if (!window)
    {
        std::cout << "Erreur fenetre\n";
        engineState = -1;
        return;
    }
    
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Erreur GLAD\n";
        engineState = -1;
        return;
    }
}

void Engine::run(const int MAX_TRIANGLES, const int FLOATS_PER_TRIANGLE) 
{
    float vertices[] = {
        -0.8f,  0.8f, 0.0f,   // top-left
        -0.8f, -0.8f, 0.0f,   // bottom-left
         0.8f,  0.8f, 0.0f,   // top-right
    };
    //MYTODO : mouve to class mesh and adapt
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
                MAX_TRIANGLES * FLOATS_PER_TRIANGLE * sizeof(float),
                nullptr,
                GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(
        0,          // index
        3,          // nombre de valeurs (x,y,z)
        GL_FLOAT,   // type
        GL_FALSE,   // normalisation
            3*sizeof(float), // taille d'un sommet
            (void*)0
    );
    glEnableVertexAttribArray(0);
    shader = Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    shader.use();



    
    onStart();
    
    while (!glfwWindowShouldClose(window))
    {
        shader.use();
       
        onUpdate();
        onRender();

        glfwPollEvents();
        glfwSwapBuffers(window);

    }
    
    glfwTerminate();
}

void Engine::onRender()
{
    Engine::clear();
    
    renderer.drawRectangle(-0.8f,0.8f, 1.0f,1.0f);
    renderer.drawRectangle(0.8f,-0.8f, 0.1f,0.1f);

    renderer.end();
        
}

void Engine::clear() 
{
    glClearColor(0.0,0.75f,1.0f,0.0);
    glClear(GL_COLOR_BUFFER_BIT);

}



int Engine::getEngineState(){return engineState;}


void Engine::replaceShader(const std::string& vertexPath, const std::string& fragmentPath) 
{
    shader = Shader(vertexPath.c_str(), fragmentPath.c_str());
}

void Engine::onStart() {}
void Engine::onUpdate() {}