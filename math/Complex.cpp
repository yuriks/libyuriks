#include "Complex.hpp"

#include <numeric>
#include "util.hpp"

namespace yks {

	vec2 slerp(vec2 a, vec2 b, float t) {
		// Cobbled together from
		// http://number-none.com/product/Understanding%20Slerp,%20Then%20Not%20Using%20It/index.html

		// If either vector is NaN, return the other
		if (!(b == b)) return a;
		if (!(a == a)) return b;

		// If vectors are LD, jiggle b a bit and normalize
		if (linearly_dependent(a, b)) {
			b[0] += 1e-3f*a[0];
			b[1] -= 1e-3f*a[1];
			b = normalized(b);
		}

		float cos_theta = dot(a, b);
		float theta = std::acos(clamp(0.0f, cos_theta, 1.0f));

		// If both orientations are the same, theta is 0.
		if (theta < 1e-3f) {
			return a;
		}

		if (cos_theta > 0.9995f) {
			return nlerp(a, b, t);
		} else {
			float theta_t = theta * t;

			vec2 c = normalized(b - a*cos_theta);
			return a*std::cos(theta_t) + c*std::sin(theta_t);
		}
	}

	vec2 rotateTowards(vec2 a, vec2 b, float max_angle) {
		// Based on https://github.com/slembcke/Chipmunk-Physics/blob/master/src/cpVect.c

		// If either vector is NaN, return the other
		if (!(b == b)) return a;
		if (!(a == a)) return b;

		// If vectors are LD, jiggle b a bit and normalize
		if (linearly_dependent(a, b)) {
			b[0] += 1e-3f*a[0];
			b[1] -= 1e-3f*a[1];
			b = normalized(b);
		}

		float cos_theta = dot(a, b);
		float theta = std::acos(clamp(0.0f, cos_theta, 1.0f));

		// If both orientations are the same, theta is 0.
		if (theta < 1e-3f) {
			return a;
		}

		float t = std::min(max_angle, theta) / theta;

		if (cos_theta > 0.9995f) {
			return nlerp(a, b, t);
		} else {
			float theta_t = theta * t;

			vec2 c = normalized(b - a*cos_theta);
			return a*std::cos(theta_t) + c*std::sin(theta_t);
		}
	}
}
