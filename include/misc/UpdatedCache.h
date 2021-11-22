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

#include <misc/Misc.h>

template <class T>
class UpdatedCache
{
private:
	T val;
	bool updated = false;

public:
	T const& getVal() const;
	T& getVal();

	bool isValid();
	void validate();
	void invalidate();

	UpdatedCache& operator=(const T&);
	UpdatedCache& operator=(T&&);

	UpdatedCache(T const& v);
	UpdatedCache(T&& v);

	NO_COPY_MOVE(UpdatedCache);

private:
	UpdatedCache() = default;
};

template<class T>
inline T const& UpdatedCache<T>::getVal() const {
	return this->val;
}

template<class T>
inline T& UpdatedCache<T>::getVal() {
	return this->val;
}

template<class T>
inline bool UpdatedCache<T>::isValid() {
	return !this->updated;
}

template<class T>
inline void UpdatedCache<T>::validate() {
	this->updated = false;
}

template<class T>
inline void UpdatedCache<T>::invalidate() {
	this->updated = true;
}

template<class T>
inline UpdatedCache<T>& UpdatedCache<T>::operator=(const T& v) {
	this->val = v;
	this->updated = true;
	return *this;
}

template<class T>
inline UpdatedCache<T>& UpdatedCache<T>::operator=(T&& v) {
	this->val = std::move(v);
	this->updated = true;
	return *this;
}

template<class T>
inline UpdatedCache<T>::UpdatedCache(T const& v) {
	this->val = v;
}

template<class T>
inline UpdatedCache<T>::UpdatedCache(T&& v) {
	this->val = std::move(v);
}
