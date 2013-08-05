#pragma once
#include <vector>
#include "math/vec.hpp"

namespace yks {
	void save_srgb_image(const std::vector<yks::vec3>& pixels, int width, int height);
}
