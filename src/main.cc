#include "transform.hpp"
#include "window.hpp"
#ifdef linux
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "logger.hpp"
#include "mesh.hpp"
#include "obj.hpp"
#include "shader.hpp"

using namespace zifmann::logger;
using namespace zifmann::game::core;
using namespace zifmann::game::utility;

using Window = GLFWwindow*;

bool running = true;
Mesh mesh;
shader::ProgramID shader_prog;

void exit_game(int code) {
    glfwTerminate();
    exit(code);
}

void load_data() {
    auto mesh_data = obj_loader::load_obj_file("cube.obj");
    auto res = shader::load_shader_program("vert.glsl", "frag.glsl");
    if (!res.first) {
        log_error("couldnt load shader file!");
        exit_game(1);
    }
    shader_prog = res.second;
    log_debug("prog: %d", shader_prog);
    if (!mesh_data.first) {
        log_error("couldnt load obj file!");
        exit_game(1);
    }
    create_mesh(mesh_data.second.verts, mesh_data.second.indices, mesh);
}

void key_callback_handler(Window w, int key, int scancode, int actions,
                          int mod) {
    if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
        running = false;
    }
}

int main() {
    if (!glfwInit()) {
        log_error("failed to initialize glfw! exiting...");
        exit(1);
    }
    auto window = zifmann::game::core::create_window(
        {WindowSettings::WindowMode::Windowed, 800, 640, true, "I like bagels",
         4, 6, GLFW_OPENGL_CORE_PROFILE});
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback_handler);
    load_data();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Transform transform;
    mat4 matrix = mat4(1);
    while (running) {
        glfwPollEvents();
        glClearColor(1.0f, 0.8f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_prog);
        glBindVertexArray(0);
        glBindVertexArray(mesh.vao);
        transform.rotation_angles.y += 0.1f;
        transform.rotation_angles.z += 0.1f;
        auto loc = glGetUniformLocation(shader_prog, "model");
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(get_model_matrix(transform)));
        glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
    }
    close_window(window);
    glfwTerminate();
    return 0;
}
