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

#pragma	once

#include <mutex>
#include <chrono>
#include <unordered_map>
#include <string>

#include "PeriodAverage.h"
#include "Option.h"

namespace misc
{
	using Duration = std::chrono::duration<double>;
	using TimePoint = std::chrono::system_clock::time_point;

	struct Timing
	{
		PeriodAvarage<Duration, TimePoint, Duration> history;
		Duration timing;
		std::optional<TimePoint> maybeStart;

		Timing() : history(5, std::chrono::milliseconds(500)), timing(0.0), maybeStart(std::nullopt) {
		};
	};


	class Timer
	{
	public:
		std::mutex mtx;

		std::unordered_map<std::string, Timing> timings;

		void startTiming(std::string timing);
		void endTiming(std::string timing);
		void newTiming(std::string timing);

		std::vector<std::string> print();
	};
}
