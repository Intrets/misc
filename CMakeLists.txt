cmake_minimum_required(VERSION 2.18)

include("${CMAKE_SOURCE_DIR}/cmake/MakeModule.cmake")

set(MODULE_NAME misc)

project(${MODULE_NAME} LANGUAGES CXX)

make_module(
	MODULE_NAME ${MODULE_NAME}
	MODULE_FILES
		Logger
		Misc
		UpdatedCache
		StringHelpers
		FunctionHelpers
		PathManager
		Log
		Timer
		PeriodAverage
		CircularArray
		Num
		QueryPerformance
		AppData
		Periodic
		OpenUrl
		Break
		FilterUnique
		LimitChecks
	CXX_STANDARD 23
	REQUIRED_LIBS
		mem
)
