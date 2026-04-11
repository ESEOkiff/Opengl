#ifndef _ENGINE_
#define _ENGINE_

#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>

#include <string>
#include "../renderer/shader/shader.hpp"
#include "../renderer/draw/Renderer.hpp"
#include "../renderer/mesh/Mesh.hpp"
#include "../utils.hpp"



class Engine
{
    public:
        Engine(int wHeigh = 600, int wWidth = 800,const char* wTitle = "Window",  bool isWresizable = 0, cameraSettings Camera = {});
        void run(const int MAX_TRIANGLES = 1000, const int FLOATS_PER_TRIANGLE = 9);
        int getEngineState();
        void replaceShader(const std::string& vertexPath, const std::string& fragmentPath);
        float getDeltaTime() const;
        void cameraHandeler(float speed = 200.0f);
        
        protected:
        GLFWwindow* window;
        
        
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        virtual void inputHandeler(); 
        
    private:
        int engineState{0};
        Shader shader;
        unsigned int VBO;
        unsigned int VAO;
        Renderer renderer;
        int wHeigh, wWidth;
        glm::mat4 projection;
        Camera cam;
        float deltaTime{0.0f};



    
};



#endif
