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
#include "input.hpp"

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Engine::Engine(int lwHeigh, int lwWidth, const char* wTitle, bool isWresizable, cameraSettings Camera, bool cursorEnabled)
{
    wHeigh = lwHeigh;
    wWidth = lwWidth;
    
    switch (Camera.Projection)
    {
        case projection::Orthographic:
        projection = glm::ortho(0.0f, (float)wWidth, 0.0f, (float)wHeigh,-1000.0f,1000.0f);
        break;
        
        case projection::Perspective:
        projection = glm::perspective(
            glm::radians(60.0f),                 // FOV
            (float)wWidth / (float)wHeigh,       // aspect ratio
            0.1f,                                // near
            100.0f                               // far
        );
        
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
    
    if(!cursorEnabled) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
    Input::init(window);
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
    float lastTime = 0.0f;
    cam.position = {0, 0, -1.0f};
    glm::mat4 baseTransform = glm::mat4(1.0f); 
    
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(baseTransform));

    onStart();
    
    while (!glfwWindowShouldClose(window))
    {
        shader.use();

        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwSetWindowUserPointer(window, &cam);
        glfwSetCursorPosCallback(window, mouse_callback);

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

    Transform tra2;
    tra2.position = {0, 0, 0}; // 👈 important
    tra2.scale = {1,1,1};
    tra2.rotation = 0;
    
    
    glUniformMatrix4fv(
        glGetUniformLocation(shader.ID, "view"),
        1,
        GL_FALSE,
        glm::value_ptr(cam.getViewMatrix())
    );
    
    
    
    // centered triangle

    renderer.drawTriangleTransformed(
        {{-70, -70, 0}, {1,0,1}},
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

float Engine::getDeltaTime() const
{
    return deltaTime;
}

void Engine::onStart() {}

void Engine::onUpdate() 
{
    Engine::inputHandeler();
}

void Engine::inputHandeler() 
{
    float speed = 200.0f * deltaTime; 
    bool acceleration = Input::isKeyDown(GLFW_KEY_LEFT_SHIFT);
    if (!acceleration) Engine::cameraHandeler(speed);
    else Engine::cameraHandeler(speed*2);

}

void Engine::cameraHandeler(float speed)
{
    glm::vec3 front;
    front.x = cos(glm::radians(cam.pitch)) * cos(glm::radians(cam.yaw));
    front.y = sin(glm::radians(cam.pitch));
    front.z = cos(glm::radians(cam.pitch)) * sin(glm::radians(cam.yaw));
    front = glm::normalize(front);

    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0,1,0)));

    if (Input::isKeyDown(GLFW_KEY_W)) cam.position += front * speed;
    if (Input::isKeyDown(GLFW_KEY_S)) cam.position -= front * speed;

    if (Input::isKeyDown(GLFW_KEY_D)) cam.position += right * speed;
    if (Input::isKeyDown(GLFW_KEY_A)) cam.position -= right * speed;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = 400;
    static float lastY = 300;
    static bool firstMouse = true;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float deltaX = xpos - lastX;
    float deltaY = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    deltaX *= sensitivity;
    deltaY *= sensitivity;

    Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    cam->yaw   += deltaX;
    cam->pitch += deltaY;

    // clamp pitch
    if (cam->pitch > 89.0f) cam->pitch = 89.0f;
    if (cam->pitch < -89.0f) cam->pitch = -89.0f;
}