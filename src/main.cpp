#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "/home/raphael/Bureau/programmation/projet informatique/projet informatique pur/C++/ressources/generalIncludes/math/math/includes/vec.hpp"
std::string readFile(const char* path);





using namespace myMath;
int main()
{
    Engine e;
    if (e.getEngineState() == -1) 
    {
        std::cout <<"Ereur lors de l'inisialisation"<<std::endl;
        return -1;
    }

    e.run();
    return 0;
}

