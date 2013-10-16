#pragma once
#include <cstddef>
#include <cstdint>

namespace yks {

	struct Handle {
		size_t index;
		uint32_t generation;

		Handle()
			: index(SIZE_MAX), generation(-1)
		{}

		Handle(size_t index, uint32_t generation)
			: index(index), generation(generation)
		{}

		bool operator ==(const Handle& o) const {
			return index == o.index && generation == o.generation;
		}

		bool operator !=(const Handle& o) const {
			return !(*this == o);
		}

		bool operator<(const Handle& o) const {
			return index < o.index;
		}

		bool isNull() const {
			return index == SIZE_MAX;
		}
	};

}
