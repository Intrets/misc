// Crack-Synth - A modular software synth
// Copyright (C) 2022 intrets

#include "QueryPerformance.h"

#include <ratio>

#if (defined(WIN32) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WINDOWS__)) && !defined(__CYGWIN__)

#include <Windows.h>

namespace misc
{
	int64_t QueryTime::frequency = [] {
		LARGE_INTEGER value;
		QueryPerformanceFrequency(&value);
		return value.QuadPart;
	}();

#ifdef DEBUG_BUILD
	picoseconds QueryTime::correction = picoseconds(0);
#else
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
#endif

	QueryTime::TimePoint QueryTime::get() {
		LARGE_INTEGER value;
		QueryPerformanceCounter(&value);
		return { .time = value.QuadPart };
	}

	picoseconds QueryTime::TimePoint::timeBetween(TimePoint p2) const {
		return picoseconds((p2.time - this->time) * 1'000'000'000'000i64 / frequency) - correction;
	}

	picoseconds QueryTime::Duration::toPicoSeconds() const {
		return picoseconds(this->time * 1'000'000'000'000i64 / frequency);
	}
}
#else
namespace misc
{
    int64_t QueryTime::frequency = {};

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

	picoseconds QueryTime::TimePoint::timeBetween(TimePoint p2) const {
		return picoseconds(p2.time - this->time) - correction;
	}

    picoseconds QueryTime::Duration::toPicoSeconds() const {
        return picoseconds(this->time * 1'000'000'000'000ll / frequency);
    }
}
#endif
