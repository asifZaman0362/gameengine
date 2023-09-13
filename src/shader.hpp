#ifndef GAME_SHADER_HPP
#define GAME_SHADER_HPP
#include <utility>
#include <vector>
#include "header.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace zifmann::game::core {
    namespace shader {
        using ShaderID = unsigned int;    
        using ProgramID = unsigned int;

        std::pair<bool, ProgramID> load_shader_program(const char* vert_shader_path, const char* frag_shader_path);
        void unload_shader_program(ProgramID);
        template<size_t N, typename T>
        void set_shader_uniform(ShaderID shader, const char* name, const glm::vec<N, T>& val);
        void set_shader_uniform_matrix(ShaderID shader, const char* name, const glm::mat4&);
    }
}

#endif
