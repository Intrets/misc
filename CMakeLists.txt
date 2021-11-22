# misc - A C++ library with many bad things
# Copyright (C) 2021  Intrets
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.20)

include("${CMAKE_SOURCE_DIR}/cmake/MakeModule.cmake")

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
