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



Engine::Engine(int lwHeigh, int lwWidth, const char* wTitle, bool isWresizable)
{   
    wHeigh = lwHeigh;
    wWidth = lwWidth;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, isWresizable);
    window = glfwCreateWindow(lwWidth, lwHeigh, wTitle, NULL, NULL);
    
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

    float left = 0;
    float right = wWidth;
    float bottom = 0;
    float top = wHeigh;

    float projection[16] = {
        2/(right-left), 0, 0, 0,
        0, 2/(top-bottom), 0, 0,
        0, 0, -1, 0,
        -(right+left)/(right-left),
        -(top+bottom)/(top-bottom),
        0, 1
    };
    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "projection"),
        1,
        GL_FALSE,
        projection
    );

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
    renderer.begin({}, 1.0f);
    glUniform1f(glGetUniformLocation(shader.ID, "time"), glfwGetTime());
    glUniform2f(glGetUniformLocation(shader.ID, "resolution"), 800, 600);   
    float speed = 3.0f;
    float t = glfwGetTime() * speed  ;

    float scale = 0.5f + 0.1f * sin(t)+0.7;
    float r = pow((sin(t) + 1.0f) / 2.0f, 1.5f);
    float g = pow((sin(t + 2.0f) + 1.0f) / 2.0f, 1.5f);
    float b = pow((sin(t + 4.0f) + 1.0f) / 2.0f, 1.5f);
    renderer.drawTriangle(
        {{400 - 100*scale, 300 - 100*scale, 0.0f}, {r,g,b}},
        {{400 + 100*scale, 300 - 100*scale, 0.0f}, {g,b,r}}, 
        {{400,             300 + 100*scale, 0.0f}, {b,r,g}}  
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