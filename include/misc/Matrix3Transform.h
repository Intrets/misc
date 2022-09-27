// misc - A C++ library with many bad things
// Copyright (C) 2022 intrets

#pragma once

#ifndef LIB_WGLM
#pragma message("optional library WGLM not found but header file Matrix3Transform.h included")
#else
#include <wglm/mat3x3.hpp>

namespace misc::mat3
{
	inline glm::mat3 from_mat4(glm::mat4 const& m) {
		return glm::mat3(
			m[0][0], m[0][1], m[0][3],
			m[1][0], m[1][1], m[1][3],
			m[3][0], m[3][1], m[3][3]
		);
	}

	inline glm::mat3 scale(float s) {
		return glm::mat3(
			s, 0.0f, 0.0f,
			0.0f, s, 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}

	inline glm::mat3 scale(glm::vec2 s) {
		return glm::mat3(
			s.x, 0.0f, 0.0f,
			0.0f, s.y, 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}

	inline glm::mat3 rotate(float a) {
		float const s = std::sin(a);
		float const c = std::cos(a);
		return glm::mat3(
			c, -s, 0.0f,
			s, c, 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}

	inline glm::mat3 translate(glm::vec2 p) {
		return glm::mat3(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			p.x, p.y, 1.0f
		);
	}

	inline glm::mat3 rotate_translate(glm::vec2 p, float a) {
		float const s = std::sin(a);
		float const c = std::cos(a);
		return glm::mat3(
			c, -s, 0.0f,
			s, c, 0.0f,
			p.x, p.y, 1.0f
		);
	}
}
#endif
