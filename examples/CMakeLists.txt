cmake_minimum_required(VERSION 2.7)
project(examples)

set(BREWED 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_definitions(-DPYCPP_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")

if (!BREWED)
    find_package(PythonInterp 2.5 REQUIRED)
    add_definitions(-DPYCPP_WHICH_PYTHON="${PYTHON_EXECUTABLE}")
endif()

find_package(PythonLibs 2.5 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})

MACRO(add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${PYTHON_LIBRARY})
ENDMACRO()

add_example(hello_world)
add_example(subclass)
add_example(plotting)