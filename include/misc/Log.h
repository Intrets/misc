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

#include <mutex>
#include <vector>
#include <string>
#include <sstream>

namespace misc
{
	class Log
	{
	private:
		std::mutex mtx;

		std::vector<std::string> lines;

	public:
		void putLine(std::string str);

		// returns a copy of the lines and clears the lines
		std::vector<std::string> getLines();

		void putStreamLine(std::stringstream ss);
	};
}
