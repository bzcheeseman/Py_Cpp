//
// Created by Aman LaChapelle on 12/27/16.
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

#include "../Py_C/include/py_object.h"

int main(int argc, char *argv[]){

  pyc_which_python = "/usr/local/bin/python";

  //import testing
  py_object *psys = new_py_object("sys", NULL);
  py_object *pos = new_py_object("os", NULL);
  py_object *ptime = new_py_object("time", NULL);

  //if the imports worked
  if (psys && pos && ptime){
    PyObject *bad_call = pyc_py_call(psys, "foo", pyc_make_tuple(0), NULL);
    PyObject *good_call = pyc_py_call(ptime, "clock", pyc_make_tuple(0), NULL);

    if (good_call && bad_call == NULL){
      return 0;
    }
  }

  return 1;
}
