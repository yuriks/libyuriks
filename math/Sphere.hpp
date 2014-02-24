#pragma once
#include "./vec.hpp"
#include "./Ray.hpp"
#include "Optional.hpp"

namespace yks {
	Optional<float> intersect_with_sphere(const vec3& origin, float radius, const Ray& r);

	/// Generates an uniformly distributed point on the surface of the unit
	/// sphere centered on 0.  a and b are two numbers in [0,1).
	vec3 uniform_point_on_sphere(float a, float b);
}
