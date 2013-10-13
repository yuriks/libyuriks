#pragma once

#include <unordered_map>
#include <string>
#include "Sprite.hpp"

namespace yks {

	struct SpriteDb {
		std::unordered_map<std::string, IntRect> sprite_db;

		IntRect lookup(const std::string& id) const { return sprite_db.at(id); }
		std::vector<IntRect> lookupSequence(const std::string& id_prefix) const;
		void loadFromCsv(const std::string& filename);
	};

}
