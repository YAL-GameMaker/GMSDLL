#pragma once
#include "stdafx.h"

template<typename T> class tiny_array {
	T* _data;
	size_t _size;
	size_t _capacity;

	bool add_impl(T value) {
		if (_size >= _capacity) {
			auto new_capacity = _capacity * 2;
			auto new_data = realloc_arr(_data, _capacity);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::add", sizeof(T) * new_capacity);
				return false;
			}
			for (size_t i = _capacity; i < new_capacity; i++) new_data[i] = {};
			_data = new_data;
			_capacity = new_capacity;
		}
		_data[_size++] = value;
		return true;
	}
public:
	tiny_array() { }
	tiny_array(size_t capacity) { init(capacity); }
	inline void init(size_t capacity = 4) {
		if (capacity < 1) capacity = 1;
		_size = 0;
		_capacity = capacity;
		_data = malloc_arr<T>(capacity);
	}
	inline void free() {
		if (_data) {
			::free(_data);
			_data = nullptr;
		}
	}

	size_t size() { return _size; }
	size_t capacity() { return _capacity; }
	T* data() { return _data; }

	bool resize(size_t newsize, T value = {}) {
		if (newsize > _capacity) {
			auto new_data = realloc_arr(_data, newsize);
			if (new_data == nullptr) {
				trace("Failed to reallocate %u bytes in tiny_array::resize", sizeof(T) * newsize);
				return false;
			}
			_data = new_data;
			_capacity = newsize;
		}
		for (size_t i = _size; i < newsize; i++) _data[i] = value;
		for (size_t i = _size; --i >= newsize;) _data[i] = value;
		_size = newsize;
		return true;
	}

	#ifdef tiny_cpp17
	template<class... Args>
	inline bool add(Args... values) {
		return (add_impl(values) && ...);
	}
	#else
	inline void add(T value) {
		add_impl(value);
	}
	#endif

	bool remove(size_t index, size_t count = 1) {
		size_t end = index + count;
		if (end < _size) memcpy_arr(_data + start, _data + end, _size - end);
		_size -= end - index;
		return true;
	}

	bool set(T* values, size_t count) {
		if (!resize(count)) return false;
		memcpy_arr(_data, values, count);
		return true;
	}
	template<size_t count> inline bool set(T(&values)[count]) {
		return set(values, count);
	}

	T operator[] (size_t index) const { return _data[index]; }
	T& operator[] (size_t index) { return _data[index]; }
};