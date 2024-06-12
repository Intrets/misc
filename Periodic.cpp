#include "misc/Periodic.h"

#include <cassert>
#include <algorithm>

namespace misc
{
	Interval::Interval(milliseconds_type period_)
	    : period(period_) {
	}

	bool Interval::run() {
		auto now = std::chrono::steady_clock::now();
		auto triggerTime = this->last + std::chrono::nanoseconds(static_cast<int64_t>(this->period * 1'000'000));
		if (now > triggerTime) {
			this->last = now;
			return true;
		}
		else {
			return false;
		}
	}

	bool Interval::countdown() {
		auto now = std::chrono::steady_clock::now();
		auto triggerTime = this->last + std::chrono::nanoseconds(static_cast<int64_t>(this->period * 1'000'000));
		if (now < triggerTime) {
			return true;
		}
		else {
			return false;
		}
	}

	int64_t Interval::countRuns() {
		auto now = std::chrono::steady_clock::now();

		if (this->last == std::chrono::steady_clock::time_point{}) {
			this->last = now;
			return 1;
		}

		auto p = std::chrono::nanoseconds(static_cast<int64_t>(this->period * 1'000'000));

		auto diff = now - this->last;
		auto count = std::max((long long)0, diff / p);

		this->last += count * p;

		return static_cast<int64_t>(count);
	}

	void Interval::reset() {
		this->last = {};
	}

	void Interval::resetNow() {
		this->last = std::chrono::steady_clock::now();
	}

	int Periods::run() {
		this->period = (this->period + this->countRuns()) % this->periodCount;
		assert(this->period >= 0);

		return this->period;
	}

	void Periods::reset() {
		this->Interval::reset();
		this->period = -1;
	}

	Periods::Periods(milliseconds_type period, int periodCount_)
	    : Interval(period),
	      periodCount(periodCount_) {
	}
}