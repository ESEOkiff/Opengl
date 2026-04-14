#include "Renderer.hpp"
#include <iostream>
#include <cmath>
#include "../../utils.hpp"
#include "../../engine/transform.hpp"
void Renderer::drawTriangleTransformed(point p1, point p2, point p3, const Transform& t)
{
    point vertices[] = {
        {applyTransform(p1.coor, t), p1.colors},
        {applyTransform(p2.coor, t), p2.colors},
        {applyTransform(p3.coor, t), p3.colors}
    };

    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(vertices), vertices);
    currentOffset += sizeof(vertices);
}

void Renderer::drawTriangleTransformed(coordinates cp1, coordinates cp2, coordinates cp3, color color, const Transform& t)
{

    point vertices[] = {
        {applyTransform(cp1, t),color},
        {applyTransform(cp2, t),color},
        {applyTransform(cp3, t),color}
    };

    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(vertices), vertices);

    currentOffset += sizeof(vertices);
}

void Renderer::drawRectangleTransformed(float x, float y, float width, float height, color color, const Transform& t)
{
    if (width <=0 || height <=0) {return;}
    Renderer::drawTriangleTransformed({{x,y,0},color},{{x+width,y,0},color},{{x,y-height,0},color},t);
    Renderer::drawTriangleTransformed({{x+width,y-height,0},color},{{x+width,y,0},{0,0,0}},{{x,y-height,0},color},t);
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
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Renderer::drawCircleTransformed(float cx, float cy, float radius, int segments, color c, const Transform& t)
{
    for (int i = 0; i < segments; i++)
    {
        float angle1 = (float)i / segments * 2.0f * M_PI;
        float angle2 = (float)(i + 1) / segments * 2.0f * M_PI;

        float x1 = cx + cos(angle1) * radius;
        float y1 = cy + sin(angle1) * radius;

        float x2 = cx + cos(angle2) * radius;
        float y2 = cy + sin(angle2) * radius;

        drawTriangleTransformed({{x1,y1,0},c},{{x2,y2,0},c}, {{cx,cy,0},c},t);
    }
}