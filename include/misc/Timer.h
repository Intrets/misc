#pragma	once

#include <mutex>

#include "PeriodAverage.h"
#include "Option.h"

namespace misc
{
	using Duration = std::chrono::duration<double>;
	using TimePoint = std::chrono::system_clock::time_point;

	TimePoint getTime() {
		return std::chrono::system_clock::now();
	}

	Duration getDurationSince(TimePoint point) {
		return point - getTime();
	}

	struct Timing
	{
		PeriodAvarage<Duration> history;
		Duration timing;
		std::optional<TimePoint> maybeStart;

		Timing() : history(5, 0.5), timing(0.0), maybeStart(std::nullopt) {
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
