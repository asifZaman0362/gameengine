#include "mesh.hpp"

#include "header.hpp"

namespace zifmann::game::core {
void create_mesh(const std::vector<Vertex>& verts,
                 const std::vector<unsigned int>& indices, Mesh& mesh) {
    auto vcount = verts.size();
    auto tcount = indices.size();
    float* vertices = new float[8 * vcount];
    int i = 0;
    for (auto vert : verts) {
        vertices[i] = vert.position.x;
        vertices[i + 1] = vert.position.y;
        vertices[i + 2] = vert.position.z;
        vertices[i + 3] = vert.uv.x;
        vertices[i + 4] = vert.uv.y;
        vertices[i + 5] = vert.normal.x;
        vertices[i + 6] = vert.normal.y;
        vertices[i + 7] = vert.normal.z;
        i += 8;
    }
    unsigned int vao, ebo, vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * vcount, (void*)vertices,
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * tcount,
                 (void*)&indices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    mesh.indices = indices;
    mesh.vertices = verts;
    mesh.vao = vao;
}
}  // namespace zifmann::game::core
