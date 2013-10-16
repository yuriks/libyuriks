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

	///////////////////////////////////////////////////////////

	SpriteMatrix& SpriteMatrix::loadIdentity() {
		m[0] = m[3] = 1.0f;
		m[1] = m[2] = 0.0f;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::multiply(const SpriteMatrix& l) {
		SpriteMatrix r = *this;

		m[0] = l.m[0]*r.m[0] + l.m[1]*r.m[2];
		m[1] = l.m[0]*r.m[1] + l.m[1]*r.m[3];
		m[2] = l.m[2]*r.m[0] + l.m[3]*r.m[2];
		m[3] = l.m[2]*r.m[1] + l.m[3]*r.m[3];

		return *this;
	}

	SpriteMatrix& SpriteMatrix::rotate(Complex z) {
		float sin_t = z.i;
		float cos_t = z.r;

		SpriteMatrix rotate_m = {{
			cos_t, -sin_t,
			sin_t, cos_t
		}};

		return multiply(rotate_m);
	}

	SpriteMatrix& SpriteMatrix::scale(float x, float y) {
		m[0] *= x;
		m[1] *= x;
		m[2] *= y;
		m[3] *= y;

		return *this;
	}

	SpriteMatrix& SpriteMatrix::shear(float x, float y) {
		SpriteMatrix r = *this;

		m[0] = r.m[0] + x*r.m[2];
		m[1] = r.m[1] + x*r.m[3];
		m[2] = y*r.m[0] + r.m[2];
		m[3] = y*r.m[1] + r.m[3];

		return *this;
	}

	void SpriteMatrix::transform(float* x, float* y) {
		float m0x = m[0] * *x;
		float m1y = m[1] * *y;
		float m2x = m[2] * *x;
		float m3y = m[3] * *y;

		*x = m0x + m1y;
		*y = m2x + m3y;
	}

	///////////////////////////////////////////////////////////

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
			unsigned short base_i = i * 4;

			indices.push_back(base_i + 0);
			indices.push_back(base_i + 1);
			indices.push_back(base_i + 3);

			indices.push_back(base_i + 3);
			indices.push_back(base_i + 1);
			indices.push_back(base_i + 2);
		}

		index_count = sprite_count;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort)*indices.size(), indices.data(), GL_STREAM_DRAW);

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
		float img_x = spr.img.x / static_cast<float>(texture_size[0]);
		float img_w = spr.img.w / static_cast<float>(texture_size[0]);
		float img_y = spr.img.y / static_cast<float>(texture_size[1]);
		float img_h = spr.img.h / static_cast<float>(texture_size[1]);

		VertexData v;
		v.color[0] = spr.color.r;
		v.color[1] = spr.color.g;
		v.color[2] = spr.color.b;
		v.color[3] = spr.color.a;

		v.pos_x = static_cast<float>(spr.pos[0]);
		v.pos_y = static_cast<float>(spr.pos[1]);
		v.tex_s = img_x;
		v.tex_t = img_y;
		vertices.push_back(v);

		v.pos_x = static_cast<float>(spr.pos[0] + spr.img.w);
		v.tex_s = img_x + img_w;
		vertices.push_back(v);

		v.pos_y = static_cast<float>(spr.pos[1] + spr.img.h);
		v.tex_t = img_y + img_h;
		vertices.push_back(v);

		v.pos_x = static_cast<float>(spr.pos[0]);
		v.tex_s = img_x;
		vertices.push_back(v);

		sprite_count += 1;
	}

	void SpriteBuffer::append(const Sprite& spr, const SpriteMatrix& matrix) {
		assert(texture_size[0] >= 0 && texture_size[1] >= 0);
		float img_x = spr.img.x / static_cast<float>(texture_size[0]);
		float img_w = spr.img.w / static_cast<float>(texture_size[0]);
		float img_y = spr.img.y / static_cast<float>(texture_size[1]);
		float img_h = spr.img.h / static_cast<float>(texture_size[1]);

		VertexData v;
		v.color[0] = spr.color.r;
		v.color[1] = spr.color.g;
		v.color[2] = spr.color.b;
		v.color[3] = spr.color.a;

		float x = spr.img.w / 2.0f;
		float y = spr.img.h / 2.0f;

		float m0x = matrix.m[0] * x;
		float m1y = matrix.m[1] * y;
		float m2x = matrix.m[2] * x;
		float m3y = matrix.m[3] * y;

		v.pos_x = spr.pos[0] - m0x - m1y;
		v.pos_y = spr.pos[1] - m2x - m3y;
		v.tex_s = img_x;
		v.tex_t = img_y;
		vertices.push_back(v);

		v.pos_x = spr.pos[0] + m0x - m1y;
		v.pos_y = spr.pos[1] + m2x - m3y;
		v.tex_s = img_x + img_w;
		vertices.push_back(v);

		v.pos_x = spr.pos[0] + m0x + m1y;
		v.pos_y = spr.pos[1] + m2x + m3y;
		v.tex_t = img_y + img_h;
		vertices.push_back(v);

		v.pos_x = spr.pos[0] - m0x + m1y;
		v.pos_y = spr.pos[1] - m2x + m3y;
		v.tex_s = img_x;
		vertices.push_back(v);

		sprite_count += 1;
	}

	void SpriteBuffer::draw(SpriteBufferIndices& indices) const {
		YKS_CHECK_GL_PARANOID;

		indices.update(sprite_count);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.name);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*vertices.size(), vertices.data(), GL_STREAM_DRAW);
		VertexData::setupVertexAttribs();
		glDrawElements(GL_TRIANGLES, sprite_count * 6, GL_UNSIGNED_SHORT, nullptr);

		YKS_CHECK_GL_PARANOID;
	}

}
