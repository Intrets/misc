#pragma once

#include <limits>
#include <utility>

namespace misc
{
	template<class From, class To>
	To abortConvert(From from) {
		if (std::cmp_less(from, std::numeric_limits<To>::min())) {
			assert(0);
			std::abort();
		}
		if (std::cmp_greater(from, std::numeric_limits<To>::max())) {
			assert(0);
			std::abort();
		}

		return To(from);
	}

	template<class From, class To>
	void abortAssign(To& to, From from) {
		to = abortConvert<From, To>(from);
	}
}