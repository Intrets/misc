#pragma once

#include <limits>
#include <utility>
#include <cstdlib>

#include <tepp/assert.h>

namespace misc
{
	template<class From, class To>
	To abortConvert(From from) {
		if (!std::in_range<To>(from)) {
			tassert(0);
			std::abort();
		}

		return static_cast<To>(from);
	}

	template<class From, class To>
	bool checkConvert(From from, To& to) {
		if (!std::in_range<To>(from)) {
			return false;
		}
		else {
			to = static_cast<To>(from);
			return true;
		}
	}

#define TRY_ASSIGN(to, from, ...) \
	if (!misc::checkConvert(from, to)) { \
		return __VA_ARGS__; \
	}

	template<class From, class To>
	void abortAssign(To& to, From from) {
		to = abortConvert<From, To>(from);
	}
}