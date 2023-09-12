#include "shader.hpp"

#include <cstring>
#include <fstream>
#include <utility>

namespace zifmann::game::core {
namespace shader {

std::pair<bool, ProgramID> load_shader_program(
    const char* vertex_shader_path, const char* fragment_shader_path) {
    std::pair<bool, ProgramID> result;

    std::ifstream vertex_shader_source_file(vertex_shader_path);
    if (!vertex_shader_source_file.is_open()) {
        logger::log_error("failed to load vertex shader source file!");
        return std::make_pair(false, 0);
    }
    std::istreambuf_iterator<char> it{vertex_shader_source_file}, end;
    std::string buffer(it, end);
    logger::log_debug("vertex shader: \n%s", buffer.c_str());
    size_t len = vertex_shader_source_file.tellg();
    ShaderID vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertex_shader) {
        logger::log_error("failed to create vertex shader!");
        return std::make_pair(false, 0);
    }
    const char* source = buffer.c_str();
    glShaderSource(vertex_shader, 1, &source, 0);
    glCompileShader(vertex_shader);
    int res = 0;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, info_log);
        logger::log_error("failed to compile vertex shader!\n%s", info_log);
        return std::make_pair(false, 0);
    }

    std::ifstream fragment_shader_source_file(fragment_shader_path);
    if (!fragment_shader_source_file.is_open()) {
        logger::log_error("failed to load fragment shader source file!");
        return std::make_pair(false, 0);
    }
    buffer.clear();
    it = std::istreambuf_iterator{fragment_shader_source_file};
    end = std::istreambuf_iterator<char>{};
    buffer = std::string(it, end);
    logger::log_debug("frag: %s", buffer.c_str());
    len = fragment_shader_source_file.tellg();
    ShaderID fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragment_shader) {
        logger::log_error("failed to create fragment shader!");
        return std::make_pair(false, 0);
    }
    const char* source_2 = buffer.c_str();
    glShaderSource(fragment_shader, 1, &source_2, 0);
    glCompileShader(fragment_shader);
    res = 0;
    memset(info_log, 0, 512);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, info_log);
        logger::log_error("failed to compile fragment shader!\n%s", info_log);
        return std::make_pair(false, 0);
    }

    ProgramID program = glCreateProgram();
    if (!program) {
        logger::log_error("failed to create shader program!");
        return std::make_pair(false, 0);
    }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        logger::log_error("failed to link shader program!\n%s", info_log);
        return std::make_pair(false, 0);
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    result.first = true;
    result.second = program;

    return result;
}

void unload_shader_program(ProgramID program) { glDeleteProgram(program); }
}  // namespace shader
}  // namespace zifmann::game::core
