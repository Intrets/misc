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

#include <cstdint>
#include <cassert>

#include <limits>

constexpr int64_t operator""_i64(unsigned long long i) {
	assert(i < (1llu << 63));
	return static_cast<int64_t>(i);
};

constexpr uint64_t operator""_u64(unsigned long long i) {
	return static_cast<uint64_t>(i);
};

constexpr int32_t operator""_i32(unsigned long long i) {
	assert(i < (1llu << 31));
	return static_cast<int32_t>(i);
};

constexpr uint32_t operator""_u32(unsigned long long i) {
	assert(i < (1llu << 32));
	return static_cast<uint32_t>(i);
};

constexpr int16_t operator""_i16(unsigned long long i) {
	assert(i < (1llu << 15));
	return static_cast<int16_t>(i);
};

constexpr uint16_t operator""_u16(unsigned long long i) {
	assert(i < (1llu << 16));
	return static_cast<uint16_t>(i);
};

constexpr int8_t operator""_i8(unsigned long long i) {
	assert(i < (1llu << 7));
	return static_cast<int8_t>(i);
};

constexpr uint8_t operator""_u8(unsigned long long i) {
	assert(i < (1llu << 8));
	return static_cast<uint8_t>(i);
};
