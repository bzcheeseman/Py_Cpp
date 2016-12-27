## Welcome to Py_Cpp!

[![Build Status](https://travis-ci.org/bzcheeseman/Py_Cpp.svg?branch=master)](https://travis-ci.org/bzcheeseman/Py_Cpp)

I wrote this library because I found myself constantly needing to call python functions 
from my C++ applications, specifically for plotting but it can be used for other things.
I tried to write it in such a way that's it's clear and self-explanatory - anything that isn't
clear I'd be happy to change or document better (of course pull requests are always welcome too)!

This is an updated version of my other project, [multiplotter](https://github.com/bzcheeseman/multiplotter), that's more general and (I think) works better.

## Compiling Tests and Examples
```
mkdir build; cd build; cmake ..
```
And then to compile examples
```
cd examples; make
```

Or to compile tests (assuming your current directory is `Py_Cpp/build`)
```
cd ../tests/gtest; mkdir build; cd build; cmake ..; make
cd ../../../build/tests; make
./unit_tests
./unit_tests_c
```
The first command builds the gtest libraries, the second makes the tests, and the third and fourth
run tests in C++ and C respectively. The C++ tests use the google test framework, but I've copied the code
into the repo so that this library has no dependencies other than `Python.h` and the python libraries.

## Using the library - C++
Py_Cpp is header-only (and I don't want to change this in the future), so just 
include `py_module.hpp` and use it to your heart's content! It's important to note that you can change
which python interpreter you're using, and you can set that with the `pycpp::which_python` variable. This
is especially important if you have a version of python installed via homebrew (or something) that is different
from your system python because using the wrong interpreter can cause major and confusing problems.
In debugging applications, unless you know what's wrong this is a good place to look.

If you wrote a python script that you want to import there are two ways to import it.  The first way is to
set `pycpp::python_home`, and the second way is to pass the directory as an argument to the constructor of
the module.  The idea was that you might have a whole folder of scripts to import and the global variable is
so that you don't have to set it more than once, but I kept the other functionality in case it's wanted.
If you don't want to specify a new directory for the import just don't add in that argument to the function.

## Using the library - C
Again, this library is header-only so simply include `py_module.h` and have at it. Since C has no namespaces
all functions are prefaced with `pyc_`, so be sure to take a look at the examples to get the call interface.
Since C lacks function overloading, I left the type conversion to Python up to the user. 
In general, the C++ interface has more to it and it's a little cleaner (plus it's nice to use an OO language
as an interface to another OO language), but as we can see from the examples most things work just fine
and sometimes you need to use C.

## Using the library - Compile your own C++ code
I would follow this general format, using `cmake`:
```
set(CMAKE_CXX_STANDARD 11)

if (APPLE)
    set(BREWED 1) # This tells cmake if we want to use a homebrew verison of python - you NEED to get
                  # this right if you're using matplotlib, for example. I would check this FIRST if you have
                  # problems.
endif()

add_definitions(-DPYCPP_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(PythonInterp 2.7 REQUIRED)

add_definitions(-DPYCPP_WHICH_PYTHON="${PYTHON_EXECUTABLE}")

find_package(PythonLibs 2.7 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})

if (BREWED)
    set(PYTHON_LIBRARY "/usr/local/Frameworks/Python.framework/Versions/Current/lib/libpython2.7.dylib")
endif ()

# Use these messages to make sure the include dir and library are right
message("${PYTHON_INCLUDE_DIR}")
message("${PYTHON_LIBRARY}")

add_executable(<your project name> <your project files> include/py_module.hpp)
target_link_libraries(<your project name> ${PYTHON_LIBRARY})
```

## Using the library - Compile your own C code
I would follow this general format, again using `cmake`:
```
set(CMAKE_C_STANDARD 11)

if (APPLE)
    set(BREWED 1) # This tells cmake if we want to use a homebrew verison of python - you NEED to get
                  # this right if you're using matplotlib, for example. I would check this FIRST if you have
                  # problems.
endif()

add_definitions(-DPYC_PY_HOME="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(PythonInterp 2.7 REQUIRED)

add_definitions(-DPYC_WHICH_PYTHON="${PYTHON_EXECUTABLE}")

find_package(PythonLibs 2.7 REQUIRED)

include_directories(${PYTHON_INCLUDE_DIR})

if (BREWED)
    set(PYTHON_LIBRARY "/usr/local/Frameworks/Python.framework/Versions/Current/lib/libpython2.7.dylib")
endif ()

# Use these messages to make sure the include dir and library are right
message("${PYTHON_INCLUDE_DIR}")
message("${PYTHON_LIBRARY}")

add_executable(<your project name> <your project files> include/py_module.h)
target_link_libraries(<your project name> ${PYTHON_LIBRARY})
```

## Understanding the library
For anyone who isn't familiar with the Python <-> C interface, at the base every python object is of 
type PyObject*.  This can make some things painful, and makes other things nice and simple. In our case
it's not all sun and daisies but we make do with what we have.

The C API for Python requires that you call functions with a PyTuple as the argument and a PyDict as
the keyword arguments.  This is why I have the `make_tuple` and `make_dict` functions.  There is an
example in `examples/plotting.cpp` for how to use these functions. I tried to make converters for the
types I usually use in C++, but I've of course missed types that are good and useful. Pull requests with
these functions are great, or even just an issue that lets me know which ones need to be written - I'll
do it when I can.

The same holds for the C interface, I have the `make_tuple` and `make_dict` functions, except again, 
the type conversions aren't there for lack of overloading. The C interface requires a little more understainding
of the C API for Python, but it does take care of a number of things that make using Python from C easier
still.

This is of course not all-encompassing, and it will require more work to become more complete, but this
is helpful for me and I believe will also be helpful for others.

## Naming Convention
### C++
I try to name the header file by the name of the class it contains.  As I add more files (if I add more files)
their names will follow that convention.  Everything is in the namespace pycpp, named for the project Py_Cpp
(which is itself a play on the Python C API naming convention).  Otherwise I try to keep a function and class
convention that matches the C++ STL to make everything as homogeneous as possible.

### C
I still follow the same file naming conventions in C, but since there are no namespaces I use the convention
of `pyc_<function name>` to eliminate the possibility of collisions. Again, I try to follow a naming convention
that follows the C++ STL for homogeneity.
