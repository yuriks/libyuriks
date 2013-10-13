#pragma once
#include <algorithm>
#include <tuple>
#include <vector>

template <typename T>
struct TupleKey {
	typedef typename std::tuple_element<0, T>::type Key;

	static const Key& get(const T& v) {
		return std::get<0>(v);
	}
};

/** A wrapper around std::vector with functions to insert items keeping the
 * vector in sorted order, as well as looking up and removing items by key. */
template <typename T, typename KeyPred = TupleKey<T>>
struct SortedVector {
	typedef std::vector<T> Storage;
	typedef typename Storage::iterator iterator;
	typedef typename Storage::const_iterator const_iterator;

	typedef typename KeyPred::Key K;

	Storage data;

	iterator insert(const T& val) {
		using std::begin;
		using std::end;

		auto insert_pos = std::lower_bound(begin(data), end(data), val);
		return data.insert(insert_pos, val);
	}

	iterator lookup(const K& key) {
		using std::begin;
		using std::end;

		auto data_end = end(data);
		auto pos = std::lower_bound(begin(data), data_end, key, [](const T& v, const K& k) { return KeyPred::get(v) < k; });
		if (pos != data_end && KeyPred::get(*pos) == key) {
			return pos;
		}
		return data_end;
	}

	bool remove(const K& key) {
		using std::end;

		auto pos = lookup(key);
		if (pos != end(data)) {
			data.erase(pos);
			return true;
		}
		return false;
	}
};
