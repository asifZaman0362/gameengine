#ifndef GAME_MESH_HPP
#define GAME_MESH_HPP

#include <glm/gtc/type_ptr.hpp>
#include <vector>

using glm::vec3, glm::vec2;

namespace zifmann::game::core {
    struct Vertex {
        vec3 position;
        vec2 uv;
        vec3 normal;
    };

    struct Mesh {
        std::vector<vec3> vertices;
        std::vector<vec2> uvs;
        std::vector<vec3> normals;
        std::vector<int> indices;
    };
}

#endif
