// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

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
