#pragma once

#include <vector>
#include "gl/gl_assert.hpp"
#include "gl/Buffer.hpp"
#include "./Sprite.hpp"
#include "math/vec.hpp"
#include "math/mat.hpp"
#include <memory>

namespace yks {

	struct VertexData {
		float pos_x, pos_y;
		float tex_s, tex_t;
		uint8_t color[4];

		static void setupVertexAttribs();
	};

	struct SpriteBufferIndices {
		std::vector<uint16_t> indices;
		unsigned int index_count = 0;

		gl::Buffer ibo;

		SpriteBufferIndices();
		void update(unsigned int sprite_count);
	};

	struct SpriteBuffer {
		std::vector<VertexData> vertices;

		unsigned int sprite_count = 0;
		gl::Buffer vbo;
		vec2i texture_size = { { -1, -1 } };

		SpriteBuffer();

		void clear();
		void append(const Sprite& spr);

		void draw(SpriteBufferIndices& indices) const;
	};

}
