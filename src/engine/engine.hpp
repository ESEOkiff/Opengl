#ifndef _ENGINE_
#define _ENGINE_

#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../renderer/shader/shader.hpp"
#include "../renderer/mesh/Mesh.hpp"


class Engine
{
    public:
        Engine(int wHeigh = 600, int wWidth = 800, bool isWresizable = 0);
        void run();
        int getEngineState();
        void replaceShader(const std::string& vertexPath, const std::string& fragmentPath);
        void drawTriangle(float x1,float y1, float x2, float y2, float x3, float y3);
        void drawRectangle(float x,float y, float width, float height);

        protected:
        GLFWwindow* window;

        
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        void basicRender();
        
    private:
        int engineState{0};
        Shader shader;
        unsigned int VBO;
        unsigned int VAO;


    
};

#endif
