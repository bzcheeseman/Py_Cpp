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
  py_module *p = new_py_module("subclass", ".."); //Standard import of user-defined file, remember that it's running from
  //examples/build so we need to tell it to add one directory up to the Python path.
  //This shows the other way to select the python home - pass it as an
  //argument to the constructor.

  py_call(p, "add", pyc_make_tuple(2, PyFloat_FromDouble(1.1), PyFloat_FromDouble(2.2)), NULL); //Call the add function to check and be sure that works

  //segfaults here for some reason
  py_module *math = py_class(p, "math_ops", NULL, NULL); //Now we want the class we defined in the script subclass.py
  py_call(math, "multiply", pyc_make_tuple(2, PyFloat_FromDouble(1.1), PyFloat_FromDouble(2.)), NULL); //And we call multiply to make sure that works.

  return 0;
}
