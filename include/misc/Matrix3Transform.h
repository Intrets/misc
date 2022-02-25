// misc - A C++ library with many bad things
// Copyright (C) 2022  Intrets
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#ifndef LIB_WGLM
#pragma message("optional library WGLM not found but header file Matrix3Transform.h included")
#else
#include <wglm/glm.hpp>

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
