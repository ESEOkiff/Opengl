#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "./engine.hpp"
#include "../renderer/shader/shader.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

Engine::Engine() 
{   
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, 0);
    window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    
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

    

    
    while (!glfwWindowShouldClose(window))
    {
        shader.use();
        float angle = glfwGetTime();
        
        float c = cos(angle);
        float s = sin(angle);
        
        float rotation[16] = {
            c,  s, 0, 0,
            -s,  c, 0, 0,
            0,  0, 1, 0,
            0,  0, 0, 1
        };
        
        
        unsigned int loc = glGetUniformLocation(shader.ID,"rotation");

        if(loc == -1)
            std::cout << "uniform rotation introuvable\n";

        glUniformMatrix4fv(loc,1,GL_FALSE,rotation);
        
        render();

    }
    
    glfwTerminate();
}

void Engine::render()
{
    glClearColor(0.0,0.75f,1.0f,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 4);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int Engine::getEngineState(){return engineState;}
