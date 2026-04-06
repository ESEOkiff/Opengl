#ifndef _UTILS_
#define _UTILS_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/transform.hpp"


struct coordinates 
{
    float x{0};
    float y{0};
    float z{0};
};

struct color
{
    float r{0};
    float g{0};
    float b{0};
};

struct point 
{
    coordinates coor {0,0,0};
    color colors{0,0,0};
};



struct DrawCommand {
    point p1, p2, p3;
    Transform transform;
};

enum class projection
{
    Orthographic,
    Perspective
};



#endif