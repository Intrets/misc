# misc - A C++ library with many bad things
# Copyright (C) 2021 intrets

cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/cmake/MakeModule.cmake")

set(MODULE_NAME misc)

project(${MODULE_NAME} LANGUAGES CXX)

make_module(
	MODULE_NAME ${MODULE_NAME}
	MODULE_FILES
		Matrix3Transform
		Logger
		Rectangle
		Misc
		UpdatedCache
		StringHelpers
		Option
		IOWrapped
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
	CXX_STANDARD 20
	REQUIRED_LIBS
		mem
		WGLM
)
