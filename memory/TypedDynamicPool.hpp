#pragma once
#include "DynamicPool.hpp"
#include <type_traits>

namespace yks {

	/** Manages a pool of objects, providing persistent handles to them. */
	template <typename T>
	struct TypedDynamicPool : DynamicPool {
		static_assert(std::is_trivially_copyable<T>::value, "T must be trivially copyable");

		TypedDynamicPool()
			: DynamicPool(sizeof(T))
		{}

		Handle insert(const T& object) {
			return insert(static_cast<const void*>(&object));
		}

		template <typename... Args>
		Handle emplace(Args&&... params) {
			Handle h;
			void* inserted;
			std::tie(h, inserted) = DynamicPool::insert(nullptr);
			new (inserted) T(std::forward<Args>(params)...);
			return h;
		}

		T* operator[] (const Handle h) {
			return static_cast<T*>(DynamicPool::operator[](h));
		}

		const T* operator[] (const Handle h) const {
			return static_cast<const T*>(DynamicPool::operator[](h));
		}
	};

}
