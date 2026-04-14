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

struct cameraSettings 
{
    enum projection Projection{projection::Orthographic};
    bool mouvable{false};
};

struct Camera
{
    glm::vec3 position {0.0f, 0.0f, 3.0f};

    float yaw   = -90.0f; // IMPORTANT pour regarder vers -Z
    float pitch = 0.0f;

    float zoom = 1.0f;

    glm::mat4 getViewMatrix() const
    {
        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));

        front = glm::normalize(front);

        return glm::lookAt(
            position,
            position + front,
            glm::vec3(0, 1, 0)
        );
    }
};


#endif