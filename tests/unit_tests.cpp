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
#include "../include/py_module.h"

TEST(PyImport, BadImport) {
  EXPECT_THROW(pycpp::py_module module ("foo"), std::runtime_error);
}

TEST(PyImport, matplotlib){
  EXPECT_NO_THROW(pycpp::py_module module ("matplotlib"));
}

TEST(PyImport, GoodImport){
  EXPECT_NO_THROW(pycpp::py_module module ("sys"));
  EXPECT_NO_THROW(pycpp::py_module module ("os"));
  EXPECT_NO_THROW(pycpp::py_module module ("time"));
  EXPECT_NO_THROW(pycpp::py_module module ("socket"));
}

TEST(PyImport, BadUserImport){
  EXPECT_ANY_THROW(pycpp::py_module module ("hello_world"));
}

//TEST(PyImport, GoodUserImport){ //this doesn't work for some reason...
//  pycpp::python_home += "/scripts";
//  EXPECT_NO_THROW(pycpp::py_module module ("hello_world"));
//}

TEST(PyCall, BadAttr){
  pycpp::py_module module ("sys");
  EXPECT_DEATH(module("foo", 0), "Assertion failed");
}

TEST(PyCall, NotCallable){
  pycpp::py_module module ("os");
  EXPECT_ANY_THROW(module("environ", 0));
}

////////// C Unit Tests ////////////

TEST(PyImport_C, BadImport) {
  EXPECT_THROW(pycpp::py_module module ("foo"), std::runtime_error);
}

TEST(PyImport_C, matplotlib){
  EXPECT_NO_THROW(pycpp::py_module module ("matplotlib"));
}

TEST(PyImport_C, GoodImport){
  EXPECT_NO_THROW(pycpp::py_module module ("sys"));
  EXPECT_NO_THROW(pycpp::py_module module ("os"));
  EXPECT_NO_THROW(pycpp::py_module module ("time"));
  EXPECT_NO_THROW(pycpp::py_module module ("socket"));
}

TEST(PyImport_C, BadUserImport){
  EXPECT_ANY_THROW(pycpp::py_module module ("hello_world"));
}

//TEST(PyImport, GoodUserImport){ //this doesn't work for some reason...
//  pycpp::python_home += "/scripts";
//  EXPECT_NO_THROW(pycpp::py_module module ("hello_world"));
//}

TEST(PyCall_C, BadAttr){
  pycpp::py_module module ("sys");
  EXPECT_DEATH(module("foo", 0), "Assertion failed");
}

TEST(PyCall_C, NotCallable){
  pycpp::py_module module ("os");
  EXPECT_ANY_THROW(module("environ", 0));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}