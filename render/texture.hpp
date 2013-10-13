#pragma once

#include "gl/Texture.hpp"
#include <string>
#include <cstdint>

namespace yks {

	struct TextureInfo {
		gl::Texture handle;
		int width, height;

		TextureInfo() : width(0), height(0) { }

		TextureInfo(TextureInfo&& o)
			: handle(std::move(o.handle)), width(o.width), height(o.height)
		{ }

		TextureInfo& operator =(TextureInfo&& o) {
			handle = std::move(o.handle);
			width = o.width;
			height = o.height;
			return *this;
		}

	private:
		NONCOPYABLE(TextureInfo);
	};

	TextureInfo loadTexture(int width, int height, const uint8_t* data);
	TextureInfo loadTexture(const std::string& filename, bool premultiply = true);

}
