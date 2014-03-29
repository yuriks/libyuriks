#pragma once

#include "math/Complex.hpp"
#include "math/vec.hpp"
#include "math/mat.hpp"

namespace yks {

	struct SpriteMatrix {
		mat<2, 3> m;

		SpriteMatrix();

		SpriteMatrix& identity();
		SpriteMatrix& multiply(const SpriteMatrix& l);
		SpriteMatrix& rotate(Complex z);
		SpriteMatrix& rotate(float radians) { return rotate(Complex::from_angle(radians)); }
		SpriteMatrix& scale(vec2 s);
		SpriteMatrix& scale(float s) { return scale(mvec2(s, s)); }
		SpriteMatrix& shear(vec2 s);
		SpriteMatrix& translate(vec2 v);

		vec2 transform(vec2 p) const;
	};

}
