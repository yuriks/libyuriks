#include "output.hpp"
#include <cmath>
#include <cstdint>
#include <vector>
#include "math/vec.hpp"
#include "stb_image_write.h"
#include "util.hpp"
#include "./srgb.hpp"

namespace yks {

static std::vector<uint8_t> encode_srgb(const std::vector<yks::vec3> fdata) {
	std::vector<uint8_t> bdata(fdata.size() * 3);
	for (size_t i = 0; i < fdata.size(); ++i) {
		bdata[i*3 + 0] = byte_from_linear(clamp(0.0f, fdata[i][0], 1.0f));
		bdata[i*3 + 1] = byte_from_linear(clamp(0.0f, fdata[i][1], 1.0f));
		bdata[i*3 + 2] = byte_from_linear(clamp(0.0f, fdata[i][2], 1.0f));
	}
	return bdata;
}

void save_srgb_image(const std::vector<yks::vec3>& pixels, int width, int height) {
	std::vector<uint8_t> image_byte_data = encode_srgb(pixels);
	stbi_write_png("output.png", width, height, 3, image_byte_data.data(), 0);
}

}
