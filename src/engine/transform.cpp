// transform.cpp
#include "transform.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "../utils.hpp"

glm::mat4 Transform::getMatrix() const {
    glm::mat4 m(1.0f);
    m = glm::translate(m, position);
    m = glm::rotate(m, rotation, glm::vec3(0,0,1));
    m = glm::scale(m, scale);
    return m;
}

void Transform::apply(const Shader& shader, const char* uniformName) const {
    glm::mat4 m = getMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniformName), 1, GL_FALSE, glm::value_ptr(m));
}

coordinates applyTransform(const coordinates& p, const Transform& t)
{
    float c = cos(t.rotation);
    float s = sin(t.rotation);

    float x = p.x * t.scale.x;
    float y = p.y * t.scale.y;

    float xr = x * c - y * s;
    float yr = x * s + y * c;

    return {
        xr + t.position.x,
        yr + t.position.y,
        p.z
    };
}

Transform Transform::identity()
{
    Transform t;
    t.position = {0, 0, 0};
    t.rotation = 0;
    t.scale = {1, 1, 1};
    return t;
}