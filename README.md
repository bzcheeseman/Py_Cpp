Welcome to Py_Cpp!

I wrote this library because I found myself constantly needing to call python functions 
from my C++ applications, specifically for plotting but it can be used for other things.
I tried to write it in such a way that's it's clear and self-explanatory - anything that isn't
clear I'd be happy to change or document better (of course pull requests are always welcome too)!

## Compiling the examples
```
cd examples
mkdir build; cd build; cmake ..; make;
```
That will build all of the examples.

## Using the library
Py_Cpp is header-only (and I don't want to change this in the future), so just 
include `py_module.hpp` and use it to your heart's content!

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
