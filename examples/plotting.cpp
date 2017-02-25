#include <iostream>

#include "../include/py_module.hpp"

int main() {

  pycpp::which_python = "/usr/local/bin/ipython"; //Note that matplotlib prefers ipython if you have a brewed python
                                                  //on your system.

  //matplotlib is picky - gotta make sure the backend is right, make sure to change the backend to something appropriate.
  setenv("MPLBACKEND", "TkAgg", 1);
  //Choose a module to import
  pycpp::py_module p ("matplotlib.pyplot");

  //C++ data of some form
  std::vector <double> data = {1.,2.,3.,4.};

  //Call the python module you want to call - make sure you take all the data to python via calls to to_python. The
  //arguments to a function are a python tuple (make_tuple) while the keyword arguments are a python dictionary (make_dict).
  p("plot",
    {pycpp::to_python(data), pycpp::to_python(data)}, //arguments
    {pycpp::to_python("label"), pycpp::to_python("$f(x) = x$")} //keyword arguments
  );

  //Do the same as above with another format
  p("plot", {pycpp::to_python(data), pycpp::to_python(data), pycpp::to_python("o")});

  //Corresponds to python calls matplotlib.pyplot.legend() and matplotlib.pyplot.show() respectively.
  p("legend");
  p("show");

  return 0;
}
