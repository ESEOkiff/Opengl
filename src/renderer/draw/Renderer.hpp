#ifndef _Renderer_
#define _Renderer_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../utils.hpp"
#include "../../engine/transform.hpp"



class Renderer
{
public:
    void drawTriangleTransformed (point p1, point p2, point p3, const Transform& transform);
    void drawTriangleTransformed (coordinates cp1, coordinates cp2, coordinates cp3, color color);
    void drawRectangleTransformed(float x, float y, float width, float height, color color = {});
    void drawCircleTransformed(float cx, float cy, float radius, int segments, color c);
    void frame();
    void begin(color clearcolor = {}, float alpha = 0.0f);
    void init(const unsigned int MAX_TRIANGLES, const unsigned int FLOATS_PER_TRIANGLE);
    void clear(float r = 0.0, float g = 0.0f, float b = 0.0f, float a = 0.0f);

private:
    unsigned int VAO, VBO;
    int currentOffset = 0;
};

#endif