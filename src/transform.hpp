#ifndef GAME_TRANSFORM_HPP
#define GAME_TRANSFORM_HPP

#include <glm/gtc/type_ptr.hpp>

#include "header.hpp"

namespace zifmann::game::core {
using glm::vec3, glm::mat4, glm::vec2;

constexpr vec3 UP = vec3(0, 1, 0);
constexpr vec3 RIGHT = vec3(1, 0, 0);
constexpr vec3 FORWARD = vec3(0, 0, 1);

struct Transform {
    vec3 translation { 0, 0, 0 };
    vec3 rotation_angles { 0, 0, 0 };
    vec3 scale { 1, 1, 1 };
};

inline mat4 get_model_matrix(const Transform& transform) {
    mat4 matrix(1.0);
    matrix = glm::translate(matrix, transform.translation);
    matrix = glm::scale(matrix, transform.scale);
    matrix = glm::rotate(matrix, transform.rotation_angles.x, RIGHT);
    matrix = glm::rotate(matrix, transform.rotation_angles.y, UP);
    matrix = glm::rotate(matrix, transform.rotation_angles.z, FORWARD);
    return matrix;
}

}  // namespace zifmann::game::core

#endif
