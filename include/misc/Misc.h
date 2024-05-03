// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

#pragma once

#include <sstream>
#include <utility>
#include <vector>

#define FORWARD_STRUCT(namespaces, name) \
	namespace namespaces \
	{ \
		struct name; \
	}

#define DEFAULT_COPY(T) \
	T(const T&) = default; \
	T& operator=(const T&) = default;
#define NO_COPY(T) \
	T(const T&) = delete; \
	T& operator=(const T&) = delete;
#define DEFAULT_MOVE(T) \
	T(T&&) = default; \
	T& operator=(T&&) = default;
#define NO_MOVE(T) \
	T(T&&) = delete; \
	T& operator=(T&&) = delete;
#define DEFAULT_COPY_MOVE(T) DEFAULT_COPY(T) DEFAULT_MOVE(T)
#define NO_COPY_MOVE(T) NO_COPY(T) NO_MOVE(T)

inline int32_t floordiv(int32_t x, int32_t y) {
	return (x + (x < 0)) / y - (x < 0);
}

inline std::pair<int32_t, int32_t> floordivmod(int32_t x, int32_t y) {
	int32_t div = floordiv(x, y);
	int32_t mod = x - div * y;
	return std::make_pair(div, mod);
}

template<class T>
inline bool indexInVector(size_t const i, std::vector<T> const& V) {
	return i >= 0 && i < V.size();
}

template<class T>
inline T* index(std::integral auto i, std::vector<T>& V) {
	if (i >= 0 && std::cmp_less(i, V.size())) {
		return &V[i];
	}
	else {
		return nullptr;
	}
}

inline bool periodic(int32_t val, int32_t on, int32_t off, int32_t offset = 0) {
	return ((val + offset) % (on + off)) <= on;
}

template<class T, size_t s>
inline bool indexInArray(size_t const i, std::array<T, s>& A) {
	return i >= 0 && i < s;
}

struct hashVoidPtr
{
	std::size_t operator()(void* const& s) const noexcept {
		return std::hash<void*>{}(const_cast<void*>(s));
	}
};

inline std::streamoff getSize(std::basic_stringstream<char>& b) {
	return b.tellp() - b.tellg();
}

inline constexpr auto modulus(std::integral auto a, std::integral auto b) {
	if constexpr (std::is_signed_v<std::remove_cv_t<decltype(a)>>) {
		if (a < 0) {
			return (b - ((-a) % b)) % b;
		}
		else {
			return a % b;
		}
	}
	else {
		return a % b;
	}
}
