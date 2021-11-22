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

#include <sstream>
#include <vector>
#include <optional>
#include <string_view>

namespace misc
{
	// split string on spaces
	// maximum number of n splits, n <= 0 -> no limit
	void split(size_t n, std::string const& in, std::vector<std::string>& out, char c = ' ', bool emptySegments = false, bool keepSplitChars = false);
	std::vector<std::string> split(size_t n, std::string const& in, char c = ' ', bool emptySegments = false, bool keepSplitChars = false);

	std::string join(std::vector<std::string> const& in, std::optional<char> c = std::nullopt);

	using namespace std::literals;
	std::string_view trim(std::string_view in, std::string_view c = "\n "sv);
}