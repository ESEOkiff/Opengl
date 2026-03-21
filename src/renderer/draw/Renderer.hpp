#ifndef _Renderer_
#define _Renderer_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer
{
public:
    void drawTriangle (float x1, float y1, float x2, float y2, float x3, float y3);
    void drawRectangle(float x, float y, float width, float height);
    void frame();
    void begin();
    void init(const unsigned int MAX_TRIANGLES, const unsigned int FLOATS_PER_TRIANGLE);

private:
    unsigned int VAO, VBO;
    int currentOffset = 0;
};

#endif