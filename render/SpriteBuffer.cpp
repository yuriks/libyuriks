#include "SpriteBuffer.hpp"

#include "gl/gl_1_5.h"
#include "gl/gl_assert.hpp"
#include <cassert>

namespace yks {

	void VertexData::setupVertexAttribs() {
		YKS_CHECK_GL_PARANOID;

		glVertexPointer(2, GL_FLOAT, sizeof(VertexData), reinterpret_cast<void*>(offsetof(VertexData, pos_x)));
		glEnableClientState(GL_VERTEX_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), reinterpret_cast<void*>(offsetof(VertexData, tex_s)));
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VertexData), reinterpret_cast<void*>(offsetof(VertexData, color)));
		glEnableClientState(GL_COLOR_ARRAY);

		YKS_CHECK_GL_PARANOID;
	}

	SpriteBufferIndices::SpriteBufferIndices() {
		YKS_CHECK_GL_PARANOID;

		glGenBuffers(1, &ibo.name);

		YKS_CHECK_GL_PARANOID;
	}

	void SpriteBufferIndices::update(unsigned int sprite_count) {
		YKS_CHECK_GL_PARANOID;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.name);
		if (index_count >= sprite_count)
			return;

		indices.reserve(sprite_count * 6);
		for (unsigned int i = index_count; i < sprite_count; ++i) {
			uint16_t base_i = uint16_t(i * 4);

			indices.push_back(base_i + 0);
			indices.push_back(base_i + 1);
			indices.push_back(base_i + 3);

			indices.push_back(base_i + 3);
			indices.push_back(base_i + 1);
			indices.push_back(base_i + 2);
		}

		index_count = sprite_count;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * indices.size(), indices.data(), GL_STREAM_DRAW);

		YKS_CHECK_GL_PARANOID;
	}

	SpriteBuffer::SpriteBuffer() {
		YKS_CHECK_GL_PARANOID;

		glGenBuffers(1, &vbo.name);

		YKS_CHECK_GL_PARANOID;
	}

	void SpriteBuffer::clear() {
		vertices.clear();
		sprite_count = 0;
	}

	void SpriteBuffer::append(const Sprite& spr) {
		assert(texture_size[0] >= 0 && texture_size[1] >= 0);

		float spr_w = static_cast<float>(spr.img.w);
		float spr_h = static_cast<float>(spr.img.h);

		float img_x = spr.img.x / static_cast<float>(texture_size[0]);
		float img_w = spr.img.w / static_cast<float>(texture_size[0]);
		float img_y = spr.img.y / static_cast<float>(texture_size[1]);
		float img_h = spr.img.h / static_cast<float>(texture_size[1]);

		VertexData v;
		v.color[0] = spr.color.r;
		v.color[1] = spr.color.g;
		v.color[2] = spr.color.b;
		v.color[3] = spr.color.a;

		auto p = spr.mat.transform(mvec2(0.f, 0.f));
		v.pos_x = p[0];
		v.pos_y = p[1];
		v.tex_s = img_x;
		v.tex_t = img_y;
		vertices.push_back(v);

		p = spr.mat.transform(mvec2(spr_w, 0.f));
		v.pos_x = p[0];
		v.pos_y = p[1];
		v.tex_s = img_x + img_w;
		vertices.push_back(v);

		p = spr.mat.transform(mvec2(spr_w, spr_h));
		v.pos_x = p[0];
		v.pos_y = p[1];
		v.tex_t = img_y + img_h;
		vertices.push_back(v);

		p = spr.mat.transform(mvec2(0.f, spr_h));
		v.pos_x = p[0];
		v.pos_y = p[1];
		v.tex_s = img_x;
		vertices.push_back(v);

		sprite_count += 1;
	}

	void SpriteBuffer::draw(SpriteBufferIndices& indices) const {
		YKS_CHECK_GL_PARANOID;

		indices.update(sprite_count);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.name);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertices.size(), vertices.data(), GL_STREAM_DRAW);
		VertexData::setupVertexAttribs();
		glDrawElements(GL_TRIANGLES, sprite_count * 6, GL_UNSIGNED_SHORT, nullptr);

		YKS_CHECK_GL_PARANOID;
	}

}
