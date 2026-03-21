#include "Renderer.hpp"
#include <iostream>

void Renderer::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    float vertices[] = {
        x1, y1, 0.0f,
        x2, y2, 0.0f,
        x3, y3, 0.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sizeof(vertices), vertices);

    currentOffset += sizeof(vertices);
}

void Renderer::drawRectangle(float x, float y, float width, float height)
{
    if (width <=0 || height <=0) {return;}
    Renderer::drawTriangle(x,y,x+width,y,x,y-height);
    Renderer::drawTriangle(x+width,y-height,x+width,y,x,y-height);
}
void Renderer::frame()
{
    glBindVertexArray(VAO);

    int vertexCount = currentOffset / (3 * sizeof(float));

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
        0,          // index
        3,          // nombre de valeurs (x,y,z)
        GL_FLOAT,   // type
        GL_FALSE,   // normalisation
            3*sizeof(float), // taille d'un sommet
            (void*)0
    );
    
    glEnableVertexAttribArray(0);
}

void Renderer::begin()
{
    currentOffset = 0;

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}