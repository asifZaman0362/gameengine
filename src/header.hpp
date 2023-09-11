#ifndef GAME_HEADER_HPP
#define GAME_HEADER_HPP

#ifdef __APPLE__
#define GL_SUPPRESS_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#else
#define GLFW_INCLUDE_NONE
#endif
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdint.h>
#include "logger.hpp"

#endif
