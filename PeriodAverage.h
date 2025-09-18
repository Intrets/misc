// misc - A C++ library with many bad things
// Copyright (C) 2021 intrets

#pragma once

#include "CircularArray.h"

namespace misc
{
	template<class Value, class Time, class Duration>
	class PeriodAvarage
	{
	private:
		Value zero() {
			return static_cast<Value>(0);
		};

	public:
		CircularArray<Value> history;

		Time currentTime{};
		Value current{};
		int32_t measurements{};

		Duration timePeriod{};

		PeriodAvarage(int32_t historySize, Duration timePeriod_) :
			history(historySize),
			timePeriod(timePeriod_) {
		};

		PeriodAvarage() = default;
		~PeriodAvarage() = default;

		void insert(Value value, Time time) {
			if (time - this->currentTime >= this->timePeriod) {
				if (this->measurements != 0) {
					this->history.insert(this->current / this->measurements);
				}
				this->current = value;
				this->currentTime = time;
				this->measurements = 1;
			}
			else {
				this->current += value;
				this->measurements++;
			}

		};

		Value getAvarege(int32_t timePeriods) {
			return this->history.sumLast(timePeriods) / timePeriods;
		};
	};
}
