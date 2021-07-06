cmake_minimum_required(VERSION 3.20)

include("./cmake/MakeModule.cmake")

set(MODULE_NAME misc)

project(${MODULE_NAME} LANGUAGES CXX)

make_module(
	MODULE_NAME ${MODULE_NAME}
	MODULE_FILES
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
	CXX_STANDARD 20
	OPTIONAL_LIBS
		mem
		WGLM
)
