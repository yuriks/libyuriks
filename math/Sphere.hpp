#pragma once
#include "./vec.hpp"
#include "./Ray.hpp"
#include "Optional.hpp"

namespace yks {
	Optional<float> intersect(const vec3& origin, float radius, const Ray& r);
}
