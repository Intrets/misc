// misc - A C++ library with many bad things
// Copyright (C) 2021  Intrets
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
