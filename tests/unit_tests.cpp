//
// Created by Aman LaChapelle on 11/24/16.
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

#include <gtest/gtest.h>

#include "../include/py_module.hpp"
//#include "../include/py_module.h"

TEST(import, pycpp_import){
  EXPECT_NO_THROW(pycpp::py_module hello ("hello_world", "../../examples"));
}

TEST(helloworld, pycpp_examples){
  pycpp::py_module hello ("hello_world", "../../examples");

  EXPECT_NO_THROW(hello("hello"));
  std::cout << std::endl;
  EXPECT_EQ(hello.call<std::string>("retHello").compare("Hello, World!"), 0);
}

TEST(subclass, pycpp_examples){
  pycpp::py_module p ("subclass", "../../examples");

  float result1 = pycpp::from_python<float>(p("add", {pycpp::to_python(1.1), pycpp::to_python(2.2)})).result;
  EXPECT_EQ(result1, 3.3f);

  pycpp::py_module math = p.py_class("math_ops"); //Now we want the class we defined in the script subclass.py
  float result2 = pycpp::from_python<float>(math("multiply", {pycpp::to_python(1.1), pycpp::to_python(2.)})).result; //And we call multiply to make sure that works.
  EXPECT_EQ(result2, 2.2f);

  float result3 = math.call<float>("multiply", {pycpp::to_python(1.1), pycpp::to_python(4.)});
  EXPECT_EQ(result3, 4.4f);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}