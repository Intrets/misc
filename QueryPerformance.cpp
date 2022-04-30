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

#include "QueryPerformance.h"

#include <ratio>

#if (defined(WIN32) || defined(_WIN32) || defined (_WIN64)|| defined(__WIN32__) || defined(__WINDOWS__)) && !defined(__CYGWIN__)

#include <Windows.h>

namespace misc
{
	int64_t QueryTime::frequency = [] {
		LARGE_INTEGER value;
		QueryPerformanceFrequency(&value);
		return value.QuadPart;
	}();

	picoseconds QueryTime::correction = [] {
		constexpr auto N = 100'000;

		int64_t total{ 0 };
		for (size_t i = 0; i < N; i++) {
			auto begin = get().time;
			auto end = get().time;

			total += end - begin;
		}

		return picoseconds(total * 1'000'000'000'000 / frequency / N);
	}();

	QueryTime::TimePoint QueryTime::get() {
		LARGE_INTEGER value;
		QueryPerformanceCounter(&value);
		return { .time = value.QuadPart };
	}

	picoseconds QueryTime::TimePoint::timeBetween(TimePoint p2) {
		return picoseconds((p2.time - this->time) * 1'000'000'000'000i64 / frequency) - correction;
	}
}
#else
namespace misc
{
	picoseconds QueryTime::correction = [] {
		constexpr auto N = 100'000;

		int64_t total{ 0 };
		for (size_t i = 0; i < N; i++) {
			auto begin = get().time;
			auto end = get().time;

			total += end - begin;
		}

		return misc::picoseconds(total / N);
	}();

	QueryTime::TimePoint QueryTime::get() {
		return { .time = std::chrono::duration_cast<misc::picoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count() };
	}

	picoseconds QueryTime::TimePoint::timeBetween(TimePoint p2) {
		return picoseconds(p2.time - this->time) - correction;
	}
}
#endif
