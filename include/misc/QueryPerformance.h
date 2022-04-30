// Crack-Synth - A modular software synth
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

#include <chrono>

namespace misc
{
	using picoseconds = std::chrono::duration<int64_t, std::pico>;

	struct QueryTime
	{
		struct TimePoint
		{
			int64_t time;

			picoseconds timeBetween(TimePoint p2);

			picoseconds operator-(TimePoint p2) {
				return p2.timeBetween(*this);
			}

			picoseconds toNow() const {
				return get() - *this;
			}
		};

		static int64_t frequency;
		static picoseconds correction;
		static TimePoint get();
	};
}