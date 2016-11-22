//
// Created by Aman LaChapelle on 11/14/16.
//
// Py_Cpp
// Copyright (c) 2016 Aman LaChapelle
// Full license at Py_Cpp/LICENSE.txt
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


#ifndef PY_CPP_PYOBJECT_HPP
#define PY_CPP_PYOBJECT_HPP

#include <Python.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

/*
 * TODO: Make sure all my decref's are correct!
 */

/**
 * @file include/py_module.hpp
 *
 * Holds the pycpp namespace. All the methods and functions related to importing Python modules and converting C++ values
 * to python are here.
 */

namespace pycpp {

  /**
   * @brief Takes a vector to a python list.
   *
   * @param vec Vector of ints to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<int> vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyInt_FromLong((long) vec[i]));
    }
    return pyvec;
  }

  /**
   * @copybrief PyObject*to_python(std::vector<int>)
   *
   * @param vec Vector of longs to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<long> vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyInt_FromLong((long) vec[i]));
    }
    return pyvec;
  }

  /**
   * @copybrief PyObject*to_python(std::vector<int>)
   *
   * @param vec Vector of doubles to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<double> vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyFloat_FromDouble((double) vec[i]));
    }
    return pyvec;
  }

  /**
   * @copybrief PyObject*to_python(std::vector<int>)
   *
   * @param vec Vector of floats to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<float> vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyFloat_FromDouble((double) vec[i]));
    }
    return pyvec;
  }

  /**
   * @brief Takes an int to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(int num){
    return PyInt_FromLong((long)num);
  }

  /**
   * @brief Takes a long to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(long num){
    return PyInt_FromLong(num);
  }

  /**
   * @brief Takes a float to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(float num){
    return PyFloat_FromDouble((double)num);
  }

  /**
   * @brief Takes a double to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(double num){
    return PyFloat_FromDouble(num);
  }

  /**
   * @brief Takes an std::string to a Python string.  Thin wrapper around PyString_FromString.
   *
   * @param str The std::string to be converted
   * @return A python string ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::string str){
    return PyString_FromString(str.c_str());
  }

  /**
   * @brief Takes a char * to a Python string. Thin wrapper around PyString_FromString.
   *
   * @param str The char * to be converted
   * @return A python string ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(char *str){
    return PyString_FromString(str);
  }

  /**
   * @brief Makes a PyTuple.
   *
   * Makes a python tuple for the purpose of passing arguments to a python function. All arguments to this function MUST
   * be of type PyObject * as follows: make_tuple(2, pycpp::to_python(<value_1>), pycpp::to_python(<value_2>))
   *
   * @param num Number of arguments to the function
   * @param ... Variable number of arguments of the type PyObject *
   * @return A PyTuple that can be passed directly to the py_module operator() call.
   */
  inline PyObject *make_tuple(int num, ...){

    if (num == 0){
      return PyTuple_Pack(0);
    }

    va_list args;
    va_start(args, num);

    PyObject *out = PyTuple_New(num);

    for (int i = 0; i < num; i++){
      PyTuple_SetItem(out, i, va_arg(args, PyObject *));
    }

    va_end(args);

    return out;
  }

  /**
   * @brief Makes a PyDict
   *
   * Makes a python dictionary for the purpose of passing keyword arguments. Note that the order of
   * arguments is as follows: make_dict(2*n, pycpp::to_python("key_n"), pycpp::to_python(<value_n>)) where
   * n is the total number of key-value PAIRS.
   *
   * @param num Number of arguments to the function
   * @param ... Variable number of arguments of type PyObject *
   * @return A PyDict that can be passed directly to the py_module operator() call.
   */
  inline PyObject *make_dict(int num, ...){
    if (num == 0){
      return nullptr;
    }

    va_list args;
    va_start(args, num);

    PyObject *out = PyDict_New();

    for (int i = 0; i < num; i+=2){
      PyDict_SetItem(out, va_arg(args, PyObject *), va_arg(args, PyObject *));
    }

    va_end(args);

    return out;
  }

  /**
   * @class py_module include/py_module.hpp
   *
   * Imports a python module and offers call operators to simplify calling member functions of that module from C++.
   */
  class py_module {
    //! The core Python module.
    PyObject *me;

  private:

    /**
     * Checks if a PyObject * is callable - throws an error if it's not.
     *
     * @param obj PyObject * to check.
     */
    inline void check_callable(PyObject *obj) {
      if (PyCallable_Check(obj)) {
        return;
      } else {
        std::string object(PyString_AsString(PyObject_Repr(obj)));
        throw std::runtime_error("Object " + object + " not callable");
      }
    }

    /**
     * Makes a tuple like the pycpp::make_tuple function but it's meant for internal use as it takes a va_list of
     * arguments.  Makes the operator() function nicer.
     *
     * @param num Number of arguments
     * @param args va_list of arguments - already called va_start on the va_list being passed to this function.
     * @return A PyTuple that will be passed as the argument list to the python function being called.
     */
    inline PyObject *make_tuple(int num, va_list args){

      if (num == 0){
        return PyTuple_Pack(0);
      }

      PyObject *out = PyTuple_New(num);

      for (int i = 0; i < num; i++){
        PyTuple_SetItem(out, i, va_arg(args, PyObject *));
      }

      va_end(args);

      return out;
    }

  public:
    /**
     * Initializes a python module by starting the interpreter and importing the desired module.
     *
     * @param package The module to import.
     */
    py_module(std::string package, std::string which_python="/usr/local/bin/ipython"){
      Py_SetProgramName((char *)which_python.c_str());

      Py_Initialize();

      me = PyImport_ImportModule(package.c_str());
      if (PyErr_Occurred()){
        PyErr_Print();
      }
    }

    /**
     * Destructor - cleans up the python references and finalizes the interpreter.
     */
    ~py_module(){
      Py_XDECREF(me);
      Py_Finalize();
    }

    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given args
     * and kwargs.  args is a PyTuple and kwargs is a PyDict - the user can either create their own or use the pycpp
     * functions make_tuple and make_dict provided here.
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args PyTuple that holds the arguments to pass to the function.
     * @param kwargs PyDict that holds the keyword arguments to pass to the function.
     * @return The return value of the function as a PyObject *.  It is left to the user to convert that back to C++.
     */
    inline PyObject *operator()(const std::string attr, PyObject *args, PyObject *kwargs = NULL){
      assert(PyTuple_Check(args));
      assert(kwargs == NULL || kwargs == nullptr || PyDict_Check(kwargs));

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      try{
        check_callable(callable);
      }
      catch (std::runtime_error &e){
        std::cout << e.what() << std::endl;
        return me;
      }

      PyObject *retval = PyObject_Call(callable, args, kwargs);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_XDECREF(args);
      PyDict_Clear(kwargs);
      Py_XDECREF(kwargs);
      Py_XDECREF(callable);

      return retval;
    }

    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given arguments
     * as the function's args tuple.  Creates a tuple of the arguments so that the function call can look like this:
     * <py_module>("<function>", 2, pycpp::to_python("string"), pycpp::to_python(<value>))
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param num Number of PyObject * arguments being passed to the function.
     * @return The return value of the function as a PyObject *.  It is left to the user to convert that back to C++.
     */
    inline PyObject *operator()(const std::string attr, int num, ...){

      va_list cpp_args;
      va_start(cpp_args, num);

      PyObject *args = this->make_tuple(num, cpp_args);

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      try{
        check_callable(callable);
      }
      catch (std::runtime_error &e){
        std::cout << e.what() << std::endl;
        return me;
      }

      PyObject *retval = PyObject_Call(callable, args, NULL);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_XDECREF(args);
      Py_XDECREF(callable);

      return retval;
    }

  };

} //pycpp


#endif //PY_CPP_PYOBJECT_HPP
