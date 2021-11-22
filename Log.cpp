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

#include "Log.h"

namespace misc
{
	void Log::putLine(std::string str) {
		std::lock_guard<std::mutex> lock(this->mtx);
		this->lines.push_back(str);
	}

	std::vector<std::string> Log::getLines() {
		std::lock_guard<std::mutex> lock(this->mtx);
		auto res = this->lines;
		this->lines.clear();
		return res;
	}

	void Log::putStreamLine(std::stringstream ss) {
		this->putLine(ss.str());
	}
}
