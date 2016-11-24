## Welcome to Py_Cpp!

[![Build Status](https://travis-ci.org/bzcheeseman/py_cpp.svg?branch=master)](https://travis-ci.org/bzcheeseman/py_cpp)

I wrote this library because I found myself constantly needing to call python functions 
from my C++ applications, specifically for plotting but it can be used for other things.
I tried to write it in such a way that's it's clear and self-explanatory - anything that isn't
clear I'd be happy to change or document better (of course pull requests are always welcome too)!

This is an updated version of my other project, [multiplotter](https://github.com/bzcheeseman/multiplotter), that's more general and (I think) works better.

## Compiling the examples
```
cd examples; mkdir build; cd build; cmake ..; make
```
That will build all of the examples.

## Compiling the tests
```
cd tests/gtest; mkdir build; cd build; cmake ..; make; cd ../..; mkdir build; cd build; cmake ..; make
```
That will build all of the tests and the gtest libraries.

## Running the examples
```
./<example>
```
Currently the examples I have written are `hello_world`, `subclass`, and `plotting`.  They also test basic
functionality of the library, along with giving examples on how to use it.

## Running the tests
```
./unit_test
```
Currently the tests only test basic functionality of the library - the examples compiling and running are
excellent indicators of the library working the way it should.

I'm still working through some silly things with the tests - the examples show that we can include 
user-defined scripts but the gtest `TEST` doesn't pass for some reason...
Until I figure out what's wrong with it I'm going to simply not include that test, though I'll leave it in 
the file, just comment it out.

## Using the library
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

## Understanding the library
For anyone who isn't familiar with the Python-C interface, at the base every python object is of 
type PyObject*.  This can make some things painful, and makes other things nice and simple. In our case
it's not all sun and daisies but we make do with what we have.

The C API for Python requires that you call functions with a PyTuple as the argument and a PyDict as
the keyword arguments.  This is why I have the `make_tuple` and `make_dict` functions.  There is an
example in `examples/plotting.cpp` for how to use these functions. I tried to make converters for the
types I usually use in C++, but I've of course missed types that are good and useful. Pull requests with
these functions are great, or even just an issue that lets me know which ones need to be written - I'll
do it when I can.

This is of course not all-encompassing, and it will require more work to become more complete, but this
is helpful for me and I believe will also be helpful for others.

## Naming Convention
I try to name the header file by the name of the class it contains.  As I add more files (if I add more files)
their names will follow that convention.  Everything is in the namespace pycpp, named for the project Py_Cpp
(which is itself a play on the Python C API naming convention).  Otherwise I try to keep a function and class
convention that maches the C++ STL to make everything as homogeneous as possible.
