#pragma once
#include <GLFW/glfw3.h>

class Input
{
public:
    static void init(GLFWwindow* win)
    {
        window = win;
    }

    static bool isKeyDown(int key)
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

private:
    static GLFWwindow* window;
    
};