#include "Renderer.hpp"
#include <iostream>
#include "../../utils.hpp"

void Renderer::drawTriangle(point p1, point p2, point p3)
{

    point vertices[] = {
        p1,
        p2,
        p3
    };

    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(vertices), vertices);

    currentOffset += sizeof(vertices);
}

void Renderer::drawTriangle(coordinates cp1, coordinates cp2, coordinates cp3, color color)
{

    point vertices[] = {
        {cp1,color},
        {cp2,color},
        {cp3,color}
    };

    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(vertices), vertices);

    currentOffset += sizeof(vertices);
}

void Renderer::drawRectangle(float x, float y, float width, float height, color color)
{
    if (width <=0 || height <=0) {return;}
    Renderer::drawTriangle({{x,y,0},color},{{x+width,y,0},color},{{x,y-height,0},color});
    Renderer::drawTriangle({{x+width,y-height,0},color},{{x+width,y,0},{0,0,0}},{{x,y-height,0},color});
}

void Renderer::frame()
{
    glBindVertexArray(VAO);

    int vertexCount = currentOffset / (6 * sizeof(float));

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    //std::cout << "Vertices: " << vertexCount << std::endl;
    currentOffset = 0;
}    

void Renderer::init(const unsigned int MAX_TRIANGLES, const unsigned int FLOATS_PER_TRIANGLE) 
{
        //MYTODO : mouve to class mesh and adapt
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
                MAX_TRIANGLES * FLOATS_PER_TRIANGLE * sizeof(float),
                nullptr,
                GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(point),
        (void*)0
    );
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(point),
        (void*)(sizeof(coordinates))
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void Renderer::begin(color clearcolor, float alpha)
{
    Renderer::clear( clearcolor.r, clearcolor.g, clearcolor.b, alpha );
    currentOffset = 0;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Renderer::clear(float r, float g, float b, float a) 
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);

}