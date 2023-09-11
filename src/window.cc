#include "window.hpp"

#include <GLFW/glfw3.h>

namespace zifmann::game::core {
Window create_window(const WindowSettings& settings) {
    const auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidmode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, settings.gl_profile);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    Window window;
    if (settings.window_mode == WindowSettings::WindowMode::Fullscreen)
        window = glfwCreateWindow(vidmode->width, vidmode->height,
                                  settings.window_title, monitor, nullptr);
    else
        window = glfwCreateWindow(settings.width, settings.height,
                                  settings.window_title, nullptr, nullptr);
    if (!window) {
        logger::log_error("could not create window!");
        return nullptr;
    }

    if (settings.vsync) {
        glfwSwapInterval(0);
    }

    return window;
}

void close_window(Window window) {
    glfwDestroyWindow(window);
}
}  // namespace zifmann::game::core
