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

#include "StringHelpers.h"

namespace misc
{
	void split(size_t n, std::string const& in, std::vector<std::string>& out, char c, bool emptySegments, bool keepSplitChars) {
		if (n <= 0) {
			n = in.size() + 1;
		}

		auto it = in.begin();

		while (it != in.end()) {
			auto prev = it;
			it = std::find(it, in.end(), c);

			if (it == in.end()) {
				out.emplace_back(prev, it);
				break;
			}

			if (prev != it || emptySegments) {
				if (keepSplitChars) {
					out.emplace_back(prev, it + 1);
				}
				else {
					out.emplace_back(prev, it);
				}

			}
			++it;

			if (out.size() == n) {
				out.emplace_back(it, in.end());
				return;
			}
		}
	}

	std::vector<std::string> split(size_t n, std::string const& in, char c, bool emptySegments, bool keepSplitChars) {
		std::vector<std::string> out;
		split(n, in, out, c, emptySegments, keepSplitChars);
		return out;
	}

	std::string join(std::vector<std::string> const& in, std::optional<char> c) {
		if (in.size() == 0) {
			return "";
		}
		std::stringstream out;
		for (int32_t i = 0; i < in.size() - 1; i++) {
			out << in[i];
			if (c.has_value()) {
				out << c.value();
			}
		}
		out << in.back();

		return out.str();
	}

	std::string_view trim(std::string_view in, std::string_view c) {
		auto start = in.find_first_not_of(c);
		auto end = in.find_last_not_of(c);
		if (start == c.npos || end == c.npos) {
			return in;
		}
		else {
			return in.substr(start, end - start + 1);
		}
	}
}
