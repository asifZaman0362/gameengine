#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <cstdint>
#include "header.hpp"

namespace zifmann::game::core {
    using Window = GLFWwindow*;

    struct WindowSettings {
        enum class WindowMode {
            Windowed,
            Fullscreen
        } window_mode;
        int width;
        int height;
        bool vsync;
        char window_title[64];
        uint8_t version_major;
        uint8_t version_minor;
        uint32_t gl_profile;
    };

    Window create_window(const WindowSettings&);
    void close_window(Window);

}

#endif
