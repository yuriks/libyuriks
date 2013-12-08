#pragma once

#include <cstdint>
#include <cmath>
#include "math/vec.hpp"
#include "math/mat.hpp"

namespace yks {
	inline float srgb_from_linear(float x) {
		return x <= 0.0031308f ?
			12.92f * x :
			1.055f * std::pow(x, 1.0f/2.4f) - 0.055f;
	}

	inline float linear_from_srgb(float x) {
		return x <= 0.04045 ?
			x / 12.92f :
			std::pow((x + 0.055f) / 1.055f, 2.4f);
	}

	inline uint8_t byte_from_linear(float x) {
		return uint8_t(srgb_from_linear(x) * 255.0f + 0.5f);
	}

	const mat3 XYZ_from_sRGB = {{
		{0.4124f, 0.3576f, 0.1805f},
		{0.2126f, 0.7152f, 0.0722f},
		{0.0193f, 0.1192f, 0.9505f}
	}};

	const mat3 sRGB_from_XYZ = {{
		{ 3.2406f, -1.5372f, -0.4986f},
		{-0.9689f,  1.8758f,  0.0415f},
		{ 0.0557f, -0.2040f,  1.0570f}
	}};

	inline vec3 xyY_from_XYZ(const vec3& XYZ) {
		float sum = 1.0f / (XYZ[0] + XYZ[1] + XYZ[2]);
		return mvec3(XYZ[0] * sum, XYZ[1] * sum, XYZ[1]);
	}

	inline vec3 XYZ_from_xyY(const vec3& xyY) {
		float Yy = xyY[2] / xyY[1];
		return mvec3(Yy * xyY[0], xyY[2], Yy * (1.0f - xyY[0] - xyY[1]));
	}
}