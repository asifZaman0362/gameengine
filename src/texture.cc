#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "header.hpp"
#include "logger.hpp"
#include "texture.hpp"

namespace zifmann::game::core {
    namespace texture {
        unsigned int load_image(const char* filename) {
            int x, y, n;
            unsigned char* data = stbi_load(filename, &x, &y, &n, 0);
            if (data == nullptr) {
                logger::log_error("failed to load texture!");
                return 0;
            }
            unsigned int textureId;
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
            return textureId;
        }
    }
}
