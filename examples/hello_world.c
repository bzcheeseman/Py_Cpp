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
  //This line creates a new py_module, and in the process imports the hello_world script from the examples folder.
  //Keep in mind that we are running from Py_Cpp/build/examples, so we need to go up two levels and then into the
  //examples folder.
  py_module *module = new_py_module("hello_world", "../../examples");

  //Now we make the call to the function in the file hello_world.py.  Notice that we need to pass an empty tuple
  //even if there are no arguments - this is a Python requirement that I've decided to keep because it forces the user
  //to be a little more careful.
  PyObject *retval = pyc_py_call(module, "hello", pyc_make_tuple(0), NULL);

  //If nothing went wrong, a.k.a. we have some return value, free the module.
  if(retval){
    delete_py_module(module);
  }

  return 0;
}