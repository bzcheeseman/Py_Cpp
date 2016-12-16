cmake_minimum_required(VERSION 3.0)
project(examples)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

#set(BREWED 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
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


MACRO(add_example name)
    add_executable(${name} ${name}.cpp ../include/py_module.hpp)
    target_link_libraries(${name} ${PYTHON_LIBRARY})
ENDMACRO()

MACRO(add_c_example name)
    add_executable(${name}_c ${name}.c ../include/py_module.h)
    target_link_libraries(${name}_c ${PYTHON_LIBRARY})
ENDMACRO()

add_example(hello_world)
add_example(subclass)
add_example(plotting)
add_c_example(hello_world)
add_c_example(plotting)
add_c_example(subclass)