#include "Timer.h"

#include <sstream>
#include <iomanip>

namespace misc
{
	TimePoint getTime() {
		return std::chrono::system_clock::now();
	}

	Duration getDurationSince(TimePoint point) {
		return point - getTime();
	}

	void Timer::startTiming(std::string timingName) {
		std::lock_guard<std::mutex> guard(this->mtx);

		auto it = this->timings.find(timingName);
		if (it == this->timings.end()) {
			return;
		}
		it->second.maybeStart = getTime();
	}

	void Timer::endTiming(std::string timingName) {
		auto time = getTime();

		std::lock_guard<std::mutex> guard(this->mtx);

		auto it = this->timings.find(timingName);
		if (it == this->timings.end()) {
			return;
		}

		auto& timing = it->second;
		if (timing.maybeStart.has_value()) {
			timing.timing += time - timing.maybeStart.value();
			timing.maybeStart = std::nullopt;
		}
	}

	void Timer::newTiming(std::string timingName) {
		std::lock_guard<std::mutex> guard(this->mtx);

		auto [it, b] = this->timings.insert({ timingName, Timing() });
		auto& timing = it->second;
		if (!b) {
			timing.history.insert(timing.timing, getTime());
			timing.timing = Duration(0);
		}
		timing.maybeStart = getTime();
	}

	std::vector<std::string> Timer::print() {
		std::vector<std::string> res;
		std::stringstream out;
		out << std::setprecision(3);

		size_t pad = 0;
		for (auto& p : this->timings) {
			pad = std::max(pad, p.first.size());
		}

		for (auto& p : this->timings) {
			Duration average = p.second.history.getAvarege(5);
			std::string perSecond;
			if (average <= Duration(1e-5)) {
				perSecond = "many";
			}
			else {
				perSecond = std::to_string(static_cast<int32_t>(Duration(1.0) / average));
			}
			out << std::setw(pad) << p.first << ": " << std::setw(7) << average * 1000.0 << "ms | " << perSecond << "/s";
			res.push_back(out.str());
			out.str(std::string());
		}

		return res;
	}
}