#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <cmath>

#include "../debuging/errorReporting.h"
#include "./engine.hpp"
#include "../renderer/shader/shader.hpp"
#include "../renderer/draw/Renderer.hpp"
#include "../utils.hpp"
#include "transform.hpp"


Engine::Engine(int lwHeigh, int lwWidth, const char* wTitle, bool isWresizable, enum projection lProjection)
{
    wHeigh = lwHeigh;
    wWidth = lwWidth;
    
    switch (lProjection)
    {
        case projection::Orthographic:
        projection = glm::ortho(0.0f, (float)wWidth, 0.0f, (float)wHeigh,-1.0f,1.0f);
        break;
        
        case projection::Perspective:
        projection = glm::perspective(0.0f,(float)wWidth,0.0f,(float)wHeigh);
        break;
        
        default:
        break;
    }
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, isWresizable);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    window = glfwCreateWindow(lwWidth, lwHeigh, wTitle, NULL, NULL);
    glm::mat4 baseTransform = glm::mat4(1.0f);
    
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
    //enableReportGlErrors();
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

    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "projection"),
        1,
        GL_FALSE,
        glm::value_ptr(projection)
    );
    onStart();
    
    while (!glfwWindowShouldClose(window))
    {
        shader.use();
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(baseTransform));
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
    float t = glfwGetTime() * speed;

    float scale = 0.5f + 0.1f * sin(t) + 0.7;

    // Assure que le uniform "transform" du vertex shader n'est pas indéfini.

    Transform tra;
    tra.position = {400, 300};   // centre écran
    tra.scale = {1, 1};          // IMPORTANT pour pixels
    tra.rotation = glfwGetTime();

    Transform tra2;
    tra2.position = {400, 300};   // centre écran
    tra2.scale = {1, 1};          // IMPORTANT pour pixels
    tra2.rotation = -glfwGetTime();
    
    
    // centered triangle
    renderer.drawTriangleTransformed(
        {{-70, -70, 0}, {1,0,0}},
        {{ 70, -70, 0}, {0,1,0}},
        {{ 0,  70, 0}, {0,0,1}},
        tra
    );    
    renderer.drawTriangleTransformed(
        {{-70, -70, 0}, {1,0,0}},
        {{ 70, -70, 0}, {0,1,0}},
        {{ 0,  70, 0}, {0,0,1}},
        tra2
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