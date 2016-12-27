//
// Created by Aman LaChapelle on 12/10/16.
//
// Project
// Copyright (c) 2016 Aman LaChapelle
// Full license at Project/LICENSE.txt
//

/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/py_module.h"

int main(int argc, char *argv[]){
  pyc_which_python = "/usr/local/bin/ipython"; //Note that matplotlib prefers brewed python if you have it
  //on your system.

  //matplotlib is picky in C - gotta make sure the backend is right
  setenv("MPLBACKEND", "TkAgg", 1);
  //Choose a module to import
  py_module *p = new_py_module("matplotlib.pyplot", pyc_python_home);

  //C++ data of some form
  double data[4] = {1.,2.,3.,4.};

  PyObject *xdata = pyc_make_list(data, 4);
  PyObject *ydata = pyc_make_list(data, 4);

  //Call the python module you want to call - make sure you take all the data to python via calls to to_python. The
  //arguments to a function are a python tuple (make_tuple) while the keyword arguments are a python dictionary (make_dict).
  pyc_py_call(p, "plot",
              pyc_make_tuple(2, xdata, ydata),
              pyc_make_dict(2, PyString_FromString("label"), PyString_FromString("$f(x) = x")));

  //Corresponds to python calls matplotlib.pyplot.legend() and matplotlib.pyplot.show() respectively.
  pyc_py_call(p, "legend", pyc_make_tuple(0), NULL);
  pyc_py_call(p, "show", pyc_make_tuple(0), NULL);
  
  //Clean up
  delete_py_module(p);
}

