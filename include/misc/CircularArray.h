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

#include <vector>

namespace misc
{
	template <class T>
	class CircularArray
	{
	private:
		T zero();

	public:
		int32_t index;
		int32_t size;
		std::vector<T> arr;
		T total;

		CircularArray(T, int32_t);
		CircularArray(int32_t size);

		void insert(T);
		T sum(T);
		T sum();
		T average(T initial);
		T average();
		T sumLast(int32_t steps);

		CircularArray() = delete;
	};

	template<class T>
	inline T CircularArray<T>::zero() {
		return static_cast<T>(0);
	}

	template<class T>
	CircularArray<T>::CircularArray(T value, int32_t s) {
		size = s;
		index = 0;
		total = s * value;
		arr.assign(s, value);
	}

	template<class T>
	inline CircularArray<T>::CircularArray(int32_t size) : CircularArray(this->zero(), size) {
	}

	template<class T>
	void CircularArray<T>::insert(T value) {
		index = (index + 1) % size;
		total -= arr[index];
		arr[index] = value;
		total += arr[index];
	}

	template<class T>
	inline T CircularArray<T>::sum(T) {
		return total;
	}

	template<class T>
	inline T CircularArray<T>::sum() {
		return total;
	}

	template<class T>
	inline T CircularArray<T>::average(T initial) {
		return sum() / static_cast<T>(this->size);
	}

	template<class T>
	inline T CircularArray<T>::average() {
		return sum() / static_cast<T>(this->size);
	}

	template<class T>
	inline T CircularArray<T>::sumLast(int32_t steps) {
		T sum = this->zero();
		for (int32_t i = 0; i < steps; i++) {
			int32_t j = (i + this->index) % this->size;
			sum += arr[j];
		}
		return sum;
	}
}
