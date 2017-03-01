## Adding New Features
If you want to add new features, please follow these steps:
1. Fork the repo
2. Open an issue letting us know what you plan to do
3. Make your changes on the `dev` branch in the `py_object.hpp` file (C++) 
or `py_object.h` file (C)
4. Add tests of your changes to `unit_tests.cpp` (C++) or `unit_tests.c` (C) and an example showing 
how to use your feature in the appropriate `examples` folder
5. Create a Pull Request

## Fixing/Upgrading Features
To fix or upgrade a feature, please follow these steps:
1. Fork the repo
2. Open an issue explaining the bug or the suggested improvement 
    (in case someone else is already working on it, 
    and to document the reasons for making the change)
3. Make your changes on the `dev` branch in the `py_object.hpp` file (C++) 
or `py_object.h` file (C)
4. Add or modify the tests and examples of this feature
5. Create a Pull Request

## Documentation Clarification
To clarify documentation, please follow these steps:
1. Fork the repo
2. Open an issue with proposed changes
3. Make the changes on the `dev` branch
4. Create a Pull Request
Making documentation clearer is always good and always welcome! 
These kinds of PRs are super important, unclear documentation can't help anyone,
so making it clearer helps everyone. It's also a great way for people who want
to get more familiar with the Python C API to look around the project and make
sure it's clear to them (and by extension, others in the same situation).

## General
 - This library is header-only - I'd like to keep it that way!
 - Follow the naming conventions please, they reduce the possibility of collisions and 
    make the API homogeneous.