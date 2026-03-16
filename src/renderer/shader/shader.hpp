#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    Shader() = default;
    void use();
};

#endif