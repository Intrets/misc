// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

#pragma once

#ifdef LIB_WGLM
#include <wglm/vec2.hpp>
#endif

#include <sstream>
#include <utility>
#include <vector>

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

#ifdef LIB_WGLM
inline glm::ivec2 floordiv(glm::ivec2 v, int32_t y) {
	return glm::ivec2(floordiv(v.x, y), floordiv(v.y, y));
};
#endif

inline std::pair<int32_t, int32_t> floordivmod(int32_t x, int32_t y) {
	int32_t div = floordiv(x, y);
	int32_t mod = x - div * y;
	return std::make_pair(div, mod);
}

#ifdef LIB_WGLM
inline std::pair<glm::ivec2, glm::ivec2> floordivmod(glm::ivec2 v, int32_t y) {
	auto pair1 = floordivmod(v.x, y);
	auto pair2 = floordivmod(v.y, y);
	return std::make_pair(glm::ivec2(pair1.first, pair2.first), glm::ivec2(pair1.second, pair2.second));
}
#endif

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

#ifdef LIB_WGLM
inline int32_t idot(glm::ivec2 v1, glm::ivec2 v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
#endif

struct hashVoidPtr
{
	std::size_t operator()(void* const& s) const noexcept {
		return std::hash<void*>{}(const_cast<void*>(s));
	}
};

#ifdef LIB_WGLM
inline float norm2(glm::vec2 v) {
	return v.x * v.x + v.y * v.y;
}
#endif

#ifdef LIB_WGLM
inline int32_t norm2(glm::ivec2 v) {
	return v.x * v.x + v.y * v.y;
}
#endif

inline std::streamoff getSize(std::basic_stringstream<char>& b) {
	return b.tellp() - b.tellg();
}
