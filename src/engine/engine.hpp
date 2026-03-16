#ifndef _ENGINE_
#define _ENGINE_

#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../renderer/shader/shader.hpp"


class Engine
{
    public:
        Engine(int wHeigh = 600, int wWidth = 800, bool isWresizable = 0);
        void run();
        int getEngineState();
        
    private:
        void update();
        void render();
        
        GLFWwindow* window;
        unsigned int shaderProgram;
        int engineState{0};
        Shader shader;
    
};

#endif