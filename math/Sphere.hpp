#pragma once
#include "./vec.hpp"
#include "./Ray.hpp"
#include "Optional.hpp"

namespace yks {
	struct Sphere {
		vec3 origin;
		float radius;

		Sphere(vec3 origin, float radius)
			: origin(origin), radius(radius)
		{}
	};

	Optional<float> intersect(const Sphere& sphere, const Ray r);
}
