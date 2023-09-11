#ifndef GAME_OBJ_HPP
#define GAME_OBJ_HPP

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <utility>

#include "header.hpp"
#include "mesh.hpp"

namespace zifmann::game::utility {
namespace obj_loader {
struct ObjData {
    std::vector<core::Vertex> verts;
    std::vector<int> indices;
};

inline std::pair<bool, ObjData> load_obj_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return std::make_pair(false, ObjData{});
    }
    char buffer[512];
    char header[8];
    std::vector<vec2> uvs;
    std::vector<vec3> verts;
    std::vector<vec3> normals;
    std::vector<int> indices;
    std::vector<glm::vec<3, glm::vec<3, int>>> triangles;
    std::vector<glm::vec<3, int>> vertex_entries;
    std::vector<core::Vertex> vertex_data;
    try {
        while (!feof(file)) {
            fgets(buffer, 512, file);
            sscanf(buffer, "%s", header);
            if (strncmp(header, "vt", 2) == 0) {
                float u, v;
                sscanf(buffer + 3, "%f %f", &u, &v);
                uvs.push_back({u, v});
            }
            if (strncmp(header, "vn", 2) == 0) {
                float x, y, z;
                sscanf(buffer + 3, "%f %f %f", &x, &y, &z);
                normals.push_back({x, y, z});
            }
            if (strncmp(header, "v", 1) == 0) {
                float x, y, z;
                sscanf(buffer + 2, "%f %f %f", &x, &y, &z);
                verts.push_back({x, y, z});
            }
            if (strncmp(header, "f", 1) == 0) {
                glm::vec<3, int> v1, v2, v3;
                sscanf(buffer + 2, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1.x, &v1.y,
                       &v1.z, &v2.x, &v2.y, &v2.z, &v3.x, &v3.y, &v3.z);
                auto pos =
                    std::find(vertex_entries.begin(), vertex_entries.end(), v1);
                if (pos == std::end(vertex_entries)) {
                    vertex_entries.push_back(v1);
                    indices.push_back(vertex_data.size());
                    vertex_data.push_back(
                        {verts[v1.x - 1], uvs[v1.y - 1], normals[v1.z - 1]});
                } else {
                    indices.push_back(
                        std::distance(vertex_entries.begin(), pos));
                }
                pos =
                    std::find(vertex_entries.begin(), vertex_entries.end(), v2);
                if (pos == std::end(vertex_entries)) {
                    vertex_entries.push_back(v2);
                    indices.push_back(vertex_data.size());
                    vertex_data.push_back(
                        {verts[v2.x - 1], uvs[v2.y - 1], normals[v2.z - 1]});
                } else {
                    indices.push_back(
                        std::distance(vertex_entries.begin(), pos));
                }
                pos =
                    std::find(vertex_entries.begin(), vertex_entries.end(), v3);
                if (pos == std::end(vertex_entries)) {
                    vertex_entries.push_back(v3);
                    indices.push_back(vertex_data.size());
                    vertex_data.push_back(
                        {verts[v3.x - 1], uvs[v3.y - 1], normals[v3.z - 1]});
                } else {
                    indices.push_back(
                        std::distance(vertex_entries.begin(), pos));
                }
            }
        }
        return std::make_pair(true, ObjData{vertex_data, indices});
    } catch (std::exception e) {
        logger::log_error("failed to parse obj model!");
        return std::make_pair(false, ObjData{});
    }
    return std::make_pair(false, ObjData{});
}
}  // namespace obj_loader
}  // namespace zifmann::game::utility

#endif
