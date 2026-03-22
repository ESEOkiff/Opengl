#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "./engine.hpp"
#include "../renderer/shader/shader.hpp"
#include "../renderer/draw/Renderer.hpp"
#include "../utils.hpp"



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
    renderer.init(MAX_TRIANGLES, FLOATS_PER_TRIANGLE);

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
    renderer.begin();
    
    renderer.drawTriangle(
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // rouge
        {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // vert
        {{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}}  // bleu
    );

    renderer.frame();
        
}





int Engine::getEngineState(){return engineState;}


void Engine::replaceShader(const std::string& vertexPath, const std::string& fragmentPath) 
{
    shader = Shader(vertexPath.c_str(), fragmentPath.c_str());
}

void Engine::onStart() {}
void Engine::onUpdate() {}