#pragma once

#include <chrono>

namespace misc
{
	struct Interval
	{
		using milliseconds_type = float;

		static constexpr milliseconds_type seconds(auto v) {
			return static_cast<milliseconds_type>(v) * 1000;
		}

		static constexpr milliseconds_type milliseconds(auto v) {
			return static_cast<milliseconds_type>(v);
		}

		milliseconds_type period;
		std::chrono::steady_clock::time_point last{};

		Interval() = delete;
		Interval(milliseconds_type period_);
		~Interval() = default;

		bool run();
		bool countdown();
		int64_t countRuns();
		void reset();
		void resetNow();
	};

	struct Periods : Interval
	{
		int periodCount = 0;
		int period = -1;

		int run();
		void reset();

		Periods() = delete;
		Periods(milliseconds_type period, int periodCount_);
		~Periods() = default;
	};
}