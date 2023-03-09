// Crack-Synth - A modular software synth
// Copyright (C) 2022 intrets

#pragma once

#include <chrono>

namespace misc
{
	using picoseconds = std::chrono::duration<int64_t, std::pico>;

	struct QueryTime
	{
		struct Duration
		{
			int64_t time{};

			Duration& operator+=(Duration other) {
				this->time += other.time;
				return *this;
			}

			int64_t count() const {
				return this->time;
			}

			picoseconds toPicoSeconds() const;
		};

		struct TimePoint
		{
			int64_t time{};

			picoseconds timeBetween(TimePoint p2) const;

			Duration toNowRaw() const {
				return { get().time - this->time };
			}

			picoseconds toNow() const {
				return this->timeBetween(get());
			}

			bool operator==(TimePoint other) const {
				return this->time == other.time;
			}
		};

		static int64_t frequency;
		static picoseconds correction;
		static TimePoint get();
	};
}