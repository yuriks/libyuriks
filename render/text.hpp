#pragma once

#include <string>
#include "SpriteBuffer.hpp"

namespace yks {

	struct FontInfo {
		char first_char;
		int char_w;
		int char_h;
		int img_x, img_y;
		int grid_w, grid_h; // In characters

		FontInfo(char first_char, int char_w, int char_h, int img_x, int img_y, int grid_w, int grid_h)
			: first_char(first_char), char_w(char_w), char_h(char_h),
			img_x(img_x), img_y(img_y), grid_w(grid_w), grid_h(grid_h)
		{ }
	};

	enum class TextAlignment {
		left, right, center
	};

	int measureStringWidth(const std::string& text, const FontInfo& font);
	void drawString(int x, int y, const std::string& text, SpriteBuffer& buffer, const FontInfo& font, const Color& color);
	void drawString(int x, int y, const std::string& text, SpriteBuffer& buffer, const FontInfo& font, TextAlignment alignment, const Color& color);

}
