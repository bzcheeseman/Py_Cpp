cmake_minimum_required(VERSION 3.0)
project(tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

if (APPLE)
    set(BREWED 1)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")

add_definitions(-DPYCPP_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPYC_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(PythonInterp 2.7 REQUIRED)

add_definitions(-DPYCPP_WHICH_PYTHON="${PYTHON_EXECUTABLE}")
add_definitions(-DPYC_WHICH_PYTHON="${PYTHON_EXECUTABLE}")

find_package(PythonLibs 2.7 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})

if (BREWED)
    set(PYTHON_LIBRARY "/usr/local/Frameworks/Python.framework/Versions/Current/lib/libpython2.7.dylib")
endif ()

message("${PYTHON_INCLUDE_DIR}")
message("${PYTHON_LIBRARY}")

include_directories(gtest/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest/build)

MACRO(add_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${PYTHON_LIBRARY})
    target_link_libraries(${name} libgtest.a libgtest_main.a pthread)
ENDMACRO()

MACRO(add_c_test name)
    add_executable(${name}_c ${name}.c)
    target_link_libraries(${name}_c ${PYTHON_LIBRARY})
    target_link_libraries(${name}_c libgtest.a libgtest_main.a pthread)
ENDMACRO()

add_test(unit_tests)
add_c_test(unit_tests)