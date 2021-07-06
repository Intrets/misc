cmake_minimum_required(VERSION 3.20)

include("./cmake/MakeModule.cmake")

set(MODULE_NAME misc)

project(${MODULE_NAME})

make_module(
  MODULE_NAME ${MODULE_NAME}
  MODULE_FILES
    Rectangle
    NumHelpers
    Misc
    UpdatedCache
    StringHelpers
    Option
    FunctionHelpers
    IOWrapped
    PathManager
    Enums
    Log
    Timer
    PeriodAverage
    CircularArray
    Num
  CXX_STANDARD 20
  REQUIRED_LIBS
    GLFW3
    WGLM
    GLEW
    mem
    render
)

