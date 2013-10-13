#include "SpriteDb.hpp"
#include <fstream>
#include <cassert>
#include "csv.hpp"

namespace yks {

	void SpriteDb::loadFromCsv(const std::string& filename) {
		std::fstream f(filename);
		assert(f); // TODO: ERROR_CHECK

		std::string line;
		while (std::getline(f, line)) {
			std::string::size_type pos = 0;

			std::string id = getNextCsvField(line, pos);

			IntRect r;
			r.x = std::stoi(getNextCsvField(line, pos));
			r.y = std::stoi(getNextCsvField(line, pos));
			r.w = std::stoi(getNextCsvField(line, pos));
			r.h = std::stoi(getNextCsvField(line, pos));

			sprite_db.insert(std::make_pair(id, r));
		}
	}

	std::vector<IntRect> SpriteDb::lookupSequence(const std::string& id_prefix) const {
		std::vector<IntRect> seq;
		int frame = 1;

		auto i = sprite_db.find(id_prefix + std::to_string(frame));
		while (i != sprite_db.end()) {
			seq.push_back(i->second);
			++frame;
			i = sprite_db.find(id_prefix + std::to_string(frame));
		}

		return seq;
	}

}
