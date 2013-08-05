#pragma once

#include <cstdint>
#include <cmath>

namespace yks {
	inline float srgb_from_linear(float x) {
		return x <= 0.0031308f ?
			12.92f * x :
			1.055f * std::pow(x, 1.0f/2.4f) - 0.055f;
	}

	inline uint8_t byte_from_linear(float x) {
		return uint8_t(srgb_from_linear(x) * 255.0f + 0.5f);
	}
}