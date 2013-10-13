#pragma once
#include <string>

namespace yks {
	std::string getNextCsvField(const std::string& str, std::string::size_type& cur_pos);
}
