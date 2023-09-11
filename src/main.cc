#include "window.hpp"
#ifdef linux
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "logger.hpp"

using namespace zifmann::logger;
using namespace zifmann::game::core;

using Window = GLFWwindow*;

bool running = true;

void key_callback_handler(Window w, int key, int scancode, int actions, int mod) {
    if (key == GLFW_KEY_ESCAPE && actions == GLFW_PRESS) {
        running = false;
    }
}

int main() {
    if (!glfwInit()) {
        log_error("failed to initialize glfw! exiting...");
        exit(1);
    }
    auto window = zifmann::game::core::create_window({ WindowSettings::WindowMode::Windowed, 800, 640, true, "I like bagels", 4, 6, GLFW_OPENGL_CORE_PROFILE});
    if (!window) {
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback_handler);
    while (running) {
        glfwPollEvents();
        glClearColor(1.0f, 0.8f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
    close_window(window);
    glfwTerminate();
    return 0;
}
