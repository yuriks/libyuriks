#pragma once

#include <array>
#include "math/vec.hpp"
#include <cstdint>

namespace yks {

	struct Color {
		uint8_t r, g, b, a;
	};

	inline Color makeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		Color c = {r, g, b, a};
		return c;
	}

	static const Color color_white = {255, 255, 255, 255};

	struct IntRect {
		int x, y;
		int w, h;
	};

	struct Sprite {
		yks::vec2i pos;
		IntRect img;
		Color color = Color{255, 255, 255, 255};

		void setImg(int x, int y, int w, int h) {
			img.x = x; img.y = y;
			img.w = w; img.h = h;
		}

		void setPos(int x_, int y_) {
			pos[0] = x_; pos[1] = y_;
		}

		void setPos(const yks::vec2 v) {
			pos = v.typecast<int>();
		}
	};

}
