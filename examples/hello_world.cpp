//
// Created by Aman LaChapelle on 11/21/16.
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

#include <iostream>

#include "../include/py_module.hpp"

int main(int argc, char *argv[]){

  pycpp::which_python = "/usr/local/bin/python"; //Select the python executable, found by typing (bash)$ which python
  pycpp::python_home = "../../examples"; //Select the python home - this is needed if you're importing scripts you wrote!

  pycpp::py_module p ("hello_world"); //This is a python script that I wrote in hello_world.py

  p("hello"); //And this just calls the function 'hello' from that script.

  //Demonstrating the from_python functionality - all the from_python functions work just like this.
  std::string r = pycpp::from_python<std::string>(p("retHello")).result;
  std::cout << r << std::endl;


  return 0;
}


