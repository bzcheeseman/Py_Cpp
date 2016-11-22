#include <iostream>

#include "../include/py_module.hpp"

int main() {


  //Choose a module to import
  pycpp::py_module p ("matplotlib.pyplot");

  //C++ data of some form
  std::vector <double> data = {1.,2.,3.,4.};

  //Call the python module you want to call - make sure you take all the data to python via calls to to_python. The
  // arguments to a function are a python tuple (make_tuple) while the keyword arguments are a python dictionary (make_dict).
  p("plot",
    pycpp::make_tuple(2, pycpp::to_python(data), pycpp::to_python(data)), //arguments
    pycpp::make_dict(2, pycpp::to_python("label"), pycpp::to_python("$f(x) = x$")) //keyword arguments
  );

  //Do the same as above with only arguments - keyword arguments don't work with this interface.
  p("plot", 3, pycpp::to_python(data), pycpp::to_python(data), pycpp::to_python("o"));

  //Corresponds to python calls matplotlib.pyplot.legend() and matplotlib.pyplot.show() respectively.
  p("legend", 0);
  p("show", 0);

  return 0;
}
