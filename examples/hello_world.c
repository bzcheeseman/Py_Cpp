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
  py_module *module = new_py_module("hello_world", "..");
  PyObject *retval = py_call(module, "hello", pyc_make_tuple(0), NULL);
  if(retval){
    free_py_module(module);
  }
  else{
    return 0;
  }
}