cmake_minimum_required(VERSION 2.5)
project(examples)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

find_package(Doxygen)

if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../docs/Doxyfile @ONLY)
    add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
            SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../docs/
            COMMENT "Generating API documentation with Doxygen" VERBATIM
            )
endif(DOXYGEN_FOUND)

find_package(PythonLibs 2 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIR})

MACRO(add_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} ${PYTHON_LIBRARY})
ENDMACRO()

add_example(plotting)
add_example(hello_world)