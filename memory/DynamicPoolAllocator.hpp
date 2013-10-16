#pragma once

#include <cstdint>

namespace yks {

	struct DynamicPoolAllocator {
		DynamicPoolAllocator(size_t object_size);
		DynamicPoolAllocator(const DynamicPoolAllocator& o);
		~DynamicPoolAllocator();
		DynamicPoolAllocator& operator =(const DynamicPoolAllocator& o);

		size_t getObjectSize() const;

		size_t size() const;
		size_t capacity() const;
		void reserve(size_t num);

		void* push_back();
		void* push_back(const void* src_data);
		void pop_back();
		void copy(size_t from, size_t to);

		void* begin() { return data_begin; }
		void* end() { return data_end; }
		const void* begin() const { return data_begin; }
		const void* end() const { return data_end; }

		void* operator [](size_t i);
		const void* operator [](size_t i) const;

	private:
		size_t object_size;
		uint8_t* data_begin;
		uint8_t* data_end;
		uint8_t* data_alloc_end;

		void expand(size_t new_capacity_bytes);
		void expand();
	};

}
