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
    std::vector<int> indices;
    std::vector<Vertex> vertices;
    unsigned int vao;
};

void create_mesh(const std::vector<core::Vertex>& verts,
                 const std::vector<int>& indices, Mesh& mesh);
void destroy_mesh();
}  // namespace zifmann::game::core

#endif
