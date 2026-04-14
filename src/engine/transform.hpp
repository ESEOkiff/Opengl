// transform.hpp
#pragma once
#include <glm/glm.hpp>
#include "../renderer/shader/shader.hpp"

struct coordinates; // forward declaration to avoid cycle with utils.hpp

class Transform {
public:
    glm::vec3 position = {0,0,0};
    glm::vec3 scale = {1,1,1};
    float rotation = 0; // radians
    Transform() = default;

    Transform identity();

    glm::mat4 getMatrix() const;
    void apply(const Shader& shader, const char* uniformName = "transform") const;
};
coordinates applyTransform(const coordinates& p, const Transform& t);


