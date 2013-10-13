#include "csv.hpp"
#include <cassert>

namespace yks {

	std::string getNextCsvField(const std::string& str, std::string::size_type& cur_pos) {
		assert(cur_pos != std::string::npos);

		std::string::size_type start_pos = cur_pos;
		cur_pos = str.find(',', cur_pos);

		std::string::size_type field_len = std::string::npos;
		if (cur_pos != std::string::npos) {
			field_len = cur_pos - start_pos;
			++cur_pos; // Skip past ','
		}

		return str.substr(start_pos, field_len);
	}

}