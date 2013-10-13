#include "texture.hpp"

#include "stb_image.h"
#include "gl/gl_1_5.h"
#include <memory>
#include <cassert>

namespace yks {

	TextureInfo loadTexture(int width, int height, const uint8_t* data) {
		TextureInfo tex_info;
		tex_info.width = width;
		tex_info.height = height;

		glGenTextures(1, &tex_info.handle.name);

		glBindTexture(GL_TEXTURE_2D, tex_info.handle.name);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		return tex_info;
	}

	TextureInfo loadTexture(const std::string& filename, bool premultiply) {
		int width, height, comp;
		auto data = std::unique_ptr<unsigned char[], void(*)(void*)>(
			stbi_load(filename.c_str(), &width, &height, &comp, 4), &stbi_image_free);
		if (data == nullptr)
			return TextureInfo();

		if (premultiply) {
			unsigned int size = width * height;

			for (unsigned int i = 0; i < size; ++i) {
				unsigned char alpha = data[i*4 + 3];
				for (unsigned int j = 0; j < 3; ++j) {
					data[i*4 + j] = data[i*4 + j] * alpha / 255;
				}
			}
		}

		return loadTexture(width, height, data.get());
	}

}
