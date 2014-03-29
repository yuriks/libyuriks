#pragma once

#include <cstdint>
#include "./SpriteMatrix.hpp"

namespace yks {

	struct Color {
		uint8_t r, g, b, a;
	};

	static const Color color_white = { 255, 255, 255, 255 };

	struct IntRect {
		int x, y;
		int w, h;
	};

	struct Sprite {
		SpriteMatrix mat;
		IntRect img;
		Color color = color_white;
	};

}
