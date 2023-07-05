#pragma once

#ifdef OS_WIN
#include <intrin.h>
#define breakpoint() \
	do { \
		__debugbreak(); \
	} while (0)
#else
#include <cassert>
#define breakpoint() \
	do { \
		assert(0); \
	}
#endif
