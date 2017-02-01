//
// Created by Aman LaChapelle on 11/22/16.
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

  pycpp::py_module p ("subclass", "../../examples"); //Standard import of user-defined file, remember that it's running from
  //Py_Cpp/build/examples so we need to tell it to add two directories up to the Python path.
  //This shows the other way to select the python home - pass it as an argument to the constructor.

  //Call the add function to check and be sure that works - both return and print
  float result = pycpp::from_python<float>(p("add", 2, pycpp::to_python(1.1), pycpp::to_python(2.2))).result;
  std::cout << result << std::endl;


  pycpp::py_module math = p.py_class("math_ops"); //Now we want the class we defined in the script subclass.py
  result = pycpp::from_python<float>(math("multiply", 2, pycpp::to_python(1.1), pycpp::to_python(2.))).result; //And we call multiply to make sure that works.
  std::cout << result << std::endl;

  return 0;

}