#pragma once
#include <cmath>
#include <cassert>
#include "vec.hpp"

namespace yks {

	struct Complex {
		float r, i;

		Complex() : r(1), i(0) {}
		Complex(float r, float i) : r(r), i(i) {}
		Complex(vec2 v) : r(v[0]), i(v[1]) {}

		static Complex from_angle(float radians) {
			return Complex(std::cos(radians), std::sin(radians));
		}

		inline vec2 as_vec() const {
			return vec2{{r, i}};
		}
	};

	inline Complex operator*(const Complex& a, const Complex& b) {
		return Complex(a.r*b.r - a.i*b.i, a.i*b.r + a.r*b.i);
	}

	inline Complex conjugate(const Complex& z) {
		return Complex(z.r, -z.i);
	}

	inline bool linearly_dependent(const vec2 a, const vec2 b) {
		return a[0]*b[1] - a[1]*b[0] < 1e-4f;
	}

	vec2 slerp(vec2 a, vec2 b, float t);
	vec2 rotateTowards(vec2 a, vec2 b, float max_angle);

}
