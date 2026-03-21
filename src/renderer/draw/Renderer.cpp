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
void Renderer::end()
{
    glBindVertexArray(VAO);

    int vertexCount = currentOffset / (3 * sizeof(float));

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    //std::cout << "Vertices: " << vertexCount << std::endl;
    currentOffset = 0;
}    
