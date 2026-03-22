#ifndef _ENGINE_
#define _ENGINE_

#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include "../renderer/shader/shader.hpp"
#include "../renderer/draw/Renderer.hpp"
#include "../renderer/mesh/Mesh.hpp"
#include "../utils.hpp"



class Engine
{
    public:
        Engine(int wHeigh = 600, int wWidth = 800,const char* wTitle = "Window",  bool isWresizable = 0);
        void run(const int MAX_TRIANGLES = 1000, const int FLOATS_PER_TRIANGLE = 9);
        int getEngineState();
        void replaceShader(const std::string& vertexPath, const std::string& fragmentPath);
        void drawTriangle(float x1,float y1, float x2, float y2, float x3, float y3);
        void drawRectangle(float x,float y, float width, float height);

        protected:
        GLFWwindow* window;

        
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        
    private:
        int engineState{0};
        Shader shader;
        unsigned int VBO;
        unsigned int VAO;
        Renderer renderer;


    
};



#endif
