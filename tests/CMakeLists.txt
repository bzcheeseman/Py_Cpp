cmake_minimum_required(VERSION 3.0)
project(tests)

set(BREWED 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

add_definitions(-DPYCPP_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")

if (!BREWED)
    find_package(PythonInterp 2.5 REQUIRED)
    add_definitions(-DPYCPP_WHICH_PYTHON="${PYTHON_EXECUTABLE}")
endif()

enable_testing()

include_directories(gtest/include)

find_package(PythonLibs 2.5 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})

link_directories(gtest/build)

MACRO(add_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${PYTHON_LIBRARY})
    target_link_libraries(${name} gtest gtest_main)
ENDMACRO()

add_test(unit_tests)