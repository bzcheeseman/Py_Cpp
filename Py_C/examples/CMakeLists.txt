cmake_minimum_required(VERSION 3.0)
project(examples)

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

MACRO(add_c_example name)
    add_executable(${name}_c ${name}.c ../include/py_object.h)
    target_link_libraries(${name}_c ${PYTHON_LIBRARY})
ENDMACRO()

add_c_example(hello_world)
add_c_example(plotting)
add_c_example(subclass)