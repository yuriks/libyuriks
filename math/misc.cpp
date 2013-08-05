#include "misc.hpp"
#include <cmath>

namespace yks {

	int solve_quadratic(const float a, const float b, const float c, float& x1, float& x2) {
		const float delta = b*b - 4*a*c;

		if (delta < 0) {
			return 0;
		} else if (delta == 0) {
			x1 = -b / (2*a);
			return 1;
		} else {
			const float sqrt_delta = std::sqrt(delta);
			x1 = (-b - sqrt_delta) / (2*a);
			x2 = (-b + sqrt_delta) / (2*a);
			return 2;
		}
	}

}
