#pragma once

#include <type_traits>
#include <utility>

namespace yks {

template <typename T>
class Optional {
public:
	Optional()
		: present(false)
	{
		update_debug_ptr();
	}

	Optional(const Optional& o) {
		if (o.present) {
			new (&storage) T(*o.get_pointer());
		}
		present = o.present;
		update_debug_ptr();
	}

	Optional(Optional&& o) {
		if (o.present) {
			new (&storage) T(std::move(*o.get_pointer()));
		}
		present = o.present;
		update_debug_ptr();
	}

	~Optional() {
		if (present) {
			get_pointer()->~T();
		}
	}

	Optional& operator=(const Optional& o) {
		if (present) {
			if (o.present) {
				*get_pointer() = *o.get_pointer();
			} else {
				get_pointer()->~T();
			}
		} else {
			if (o.present) {
				new (&storage) T(*o.get_pointer());
			}
		}
		present = o.present;
		update_debug_ptr();

		return *this;
	}

	template <typename... Args>
	void emplace(Args&&... args)
	{
		if (present) {
			get_pointer()->~T();
		}
		new (&storage) T(std::forward<Args>(args)...);
		present = true;
		update_debug_ptr();
	}

	explicit operator bool() const { return present; }

	const T& operator* () const { return *get_pointer(); }
	      T& operator* ()       { return *get_pointer(); }
	const T* operator->() const { return  get_pointer(); }
	      T* operator->()       { return  get_pointer(); }

	template <typename U>
	T value_or(U&& value) const {
		return present ? *get_pointer() : std::move(value);
	}

private:
	typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type storage;
	bool present;
#if _DEBUG
	const T* debug_ptr;
#endif

	void update_debug_ptr() {
#if _DEBUG
		debug_ptr = present ? static_cast<const T*>(static_cast<const void*>(&storage)) : nullptr;
#endif
	}

	const T* get_pointer() const {
		assert(present);
		return static_cast<const T*>(static_cast<const void*>(&storage));
	}

	T* get_pointer() {
		assert(present);
		return static_cast<T*>(static_cast<void*>(&storage));
	}
};

template <typename T, typename... Args>
Optional<T> make_optional(Args&&... args) {
	Optional<T> optional;
	optional.emplace(std::forward<Args>(args)...);
	return optional;
}

}
