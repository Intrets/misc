// misc - A C++ library with many bad things
// Copyright (C) 2021  Intrets
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

#ifdef LIB_WGLM
#include <wglm/glm.hpp>

#include <istream>
#include <ostream>

// vec2

inline std::ostream& operator<<(std::ostream& out, const glm::vec2& v) {
	out << v.x << " " << v.y;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::vec2& v) {
	in >> v.x >> v.y;
	return in;
}

// vec3

inline std::ostream& operator<<(std::ostream& out, const glm::vec3& v) {
	out << v.x << " " << v.y << " " << v.z;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::vec3& v) {
	in >> v.x >> v.y >> v.z;
	return in;
}

// vec 4

inline std::ostream& operator<<(std::ostream& out, const glm::vec4& v) {
	out << v.x << " " << v.y << " " << v.z << " " << v.w;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::vec4& v) {
	in >> v.x >> v.y >> v.z >> v.w;
	return in;
}

// ivec2

inline std::ostream& operator<<(std::ostream& out, const glm::ivec2& v) {
	out << v.x << " " << v.y;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::ivec2& v) {
	in >> v.x >> v.y;
	return in;
}

// ivec3

inline std::ostream& operator<<(std::ostream& out, const glm::ivec3& v) {
	out << v.x << " " << v.y << " " << v.z;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::ivec3& v) {
	in >> v.x >> v.y >> v.z;
	return in;
}

// ivec 4

inline std::ostream& operator<<(std::ostream& out, const glm::ivec4& v) {
	out << v.x << " " << v.y << " " << v.z << " " << v.w;
	return out;
}

inline std::istream& operator>>(std::istream& in, glm::ivec4& v) {
	in >> v.x >> v.y >> v.z >> v.w;
	return in;
}
#endif