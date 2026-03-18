#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./engine.hpp"
#include "../renderer/shader/shader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Engine::Engine(int wHeigh, int wWidth, bool isWresizable)
{   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, isWresizable);
    window = glfwCreateWindow(wWidth, wHeigh, "OpenGL", NULL, NULL);
    
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

void Engine::run() 
{
    float vertices[] = {
        -0.8f,  0.8f, 0.0f,   // top-left
        -0.8f, -0.8f, 0.0f,   // bottom-left
         0.8f,  0.8f, 0.0f,   // top-right
         0.8f, -0.8f, 0.0f    // bottom-right
    };
    
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
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

    }
    
    glfwTerminate();
}

void Engine::onRender()
{
    glClearColor(0.0,0.75f,1.0f,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int Engine::getEngineState(){return engineState;}


void Engine::replaceShader(const std::string& vertexPath, const std::string& fragmentPath) 
{
    shader = Shader(vertexPath.c_str(), fragmentPath.c_str());
}

void drawRectangle(float x1,float y1, float x2, float y2, float x3, float y3) 
{
    
}