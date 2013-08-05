#pragma once
#include "./vec.hpp"
#include "./mat.hpp"

namespace yks {

	struct Ray {
		vec3 origin;
		vec3 direction;

		inline vec3 operator()(float t) const {
			return origin + direction*t;
		}
	};

	inline Ray operator*(const mat4& m, const Ray& r) {
		return Ray{
			mvec3(m * mvec4(r.origin, 1.0f)),
			mvec3(m * mvec4(r.direction, 0.0f))
		};
	}

}
