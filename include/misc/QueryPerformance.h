// Crack-Synth - A modular software synth
// Copyright (C) 2022 intrets

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