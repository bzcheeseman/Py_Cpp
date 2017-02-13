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


#ifndef PY_CPP_PYMODULE_HPP
#define PY_CPP_PYMODULE_HPP

#include <Python.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <type_traits>

/**
 * @todo: get windows build working?
 */

/**
 * @file include/py_module.hpp
 *
 * Holds the pycpp namespace. All the methods and functions related to importing Python modules and converting C++ values
 * to python are here.
 */

//! This allows us to use the python interpreter that CMake finds.
#ifndef PYCPP_WHICH_PYTHON
  #define PYCPP_WHICH_PYTHON "/usr/local/bin/ipython"
#endif

//! Gives us a smart value for the home directory - again from the CMake source directory.
#ifndef PYCPP_PY_HOME
  #define PYCPP_PY_HOME "../.."
#endif

namespace pycpp {

  /**
   * Selects the python executable - this is important to choose right because the wrong choice can have grave
   * consequences - a.k.a. things won't work.  If you're having trouble I recommend changing this first,
   * especially if you used homebrew to get another python distribution alongside your system python.
   */
  static std::string which_python = PYCPP_WHICH_PYTHON;

  /**
   * Sets the python home.  Generally scripts will be in the directory one up from build, so this is the default value.
   * However this is easily changed by calling pycpp::python_home = "path/to/script".
   */
  static std::string python_home = PYCPP_PY_HOME;

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
   * @brief Interface for passing functions back from Python.
   *
   * Will return C++ integral types, as well as vectors of integral types. C-style arrays can then be gotten by calling
   * <vector>.data() on the result.
   *
   * @tparam T Type of the object to be extracted from Python.
   */
  template<typename T>
  struct from_python {
    T result;
  };

  //! String specialization
  template<> struct from_python<std::string> {
    from_python(PyObject *pyObj): result(PyString_AsString(pyObj)) {}
    std::string result;
  };

  //! Int specialization
  template<> struct from_python<int> {
    from_python(PyObject *pyObj): result((int)PyInt_AsLong(pyObj)) {}
    int result;
  };

  //! Long specialization
  template<> struct from_python<long> {
    from_python(PyObject *pyObj): result(PyInt_AsLong(pyObj)) {}
    long result;
  };

  //! Float specialization
  template<> struct from_python<float> {
    from_python(PyObject *pyObj): result((float)PyFloat_AsDouble(pyObj)) {}
    float result;
  };

  //! Double specialization
  template<> struct from_python<double> {
    from_python(PyObject *pyObj): result(PyFloat_AsDouble(pyObj)) {}
    double result;
  };

  //! String vector specialization
  template<> struct from_python<std::vector<std::string>> {
    from_python(PyObject *pyObj){
      PyList_Check(pyObj);
      size_t len = PyList_Size(pyObj);
      PyObject *item;
      for (size_t i = 0; i < len; i++){
        PyList_GetItem(item, i);
        result.push_back(PyString_AsString(item));
      }
    }
    std::vector<std::string> result;
  };

  //! Int vector specialization
  template<> struct from_python<std::vector<int>> {
    from_python(PyObject *pyObj){
      PyList_Check(pyObj);
      size_t len = PyList_Size(pyObj);
      PyObject *item;
      for (size_t i = 0; i < len; i++){
        PyList_GetItem(item, i);
        result.push_back((int)PyInt_AsLong(item));
      }
    }
    std::vector<int> result;
  };

  //! Long vector specialization
  template<> struct from_python<std::vector<long>> {
    from_python(PyObject *pyObj){
      PyList_Check(pyObj);
      size_t len = PyList_Size(pyObj);
      PyObject *item;
      for (size_t i = 0; i < len; i++){
        PyList_GetItem(item, i);
        result.push_back(PyInt_AsLong(item));
      }
    }
    std::vector<long> result;
  };

  //! Float vector specialization
  template<> struct from_python<std::vector<float>> {
    from_python(PyObject *pyObj){
      PyList_Check(pyObj);
      size_t len = PyList_Size(pyObj);
      PyObject *item;
      for (size_t i = 0; i < len; i++){
        PyList_GetItem(item, i);
        result.push_back((float)PyFloat_AsDouble(item));
      }
    }
    std::vector<float> result;
  };

  //! Double vector specialization
  template<> struct from_python<std::vector<double>> {
    from_python(PyObject *pyObj){
      PyList_Check(pyObj);
      size_t len = PyList_Size(pyObj);
      PyObject *item;
      for (size_t i = 0; i < len; i++){
        PyList_GetItem(item, i);
        result.push_back(PyFloat_AsDouble(item));
      }
    }
    std::vector<double> result;
  };

  /**
   * @brief Makes a PyTuple.
   *
   * Makes a python tuple for the purpose of passing arguments to a python function. All arguments to this function MUST
   * be of type PyObject * as follows: make_tuple({pycpp::to_python(<value_1>), pycpp::to_python(<value_2>)})
   *
   * @param l The initializer list of arguments to be put into the tuple.
   * @return A PyTuple that can be passed directly to the py_module operator() call.
   */
  inline PyObject *make_tuple(std::initializer_list<PyObject *> l){

    int num = l.size();

    if (num == 0){
      return PyTuple_Pack(0);
    }

    PyObject *out = PyTuple_New(num);

    for (int i = 0; i < num; i++){
      PyTuple_SetItem(out, i, *(l.begin()+i));
    }

    return out;
  }

  /**
   * @brief Makes a PyDict
   *
   * Makes a python dictionary for the purpose of passing keyword arguments. Note that the order of
   * arguments is as follows: make_dict({pycpp::to_python("key_n"), pycpp::to_python(<value_n>)}) where
   * n is the total number of key-value PAIRS.
   *
   * @param l The initializer_list of key-value pairs.
   * @return A PyDict that can be passed directly to the py_module operator() call.
   */
  inline PyObject *make_dict(std::initializer_list<PyObject *> l){
    assert(l.size()%2 == 0);

    int num = l.size();

    if (num == 0){
      return nullptr;
    }

    PyObject *out = PyDict_New();

    for (int i = 0; i < num; i+=2){
      PyDict_SetItem(out, *(l.begin()+i), *(l.begin()+i+1));
    }

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
     * Default constructor - used internally only to make sure everything is working properly.
     */
    py_module(){};

  public:
    /**
     * Initializes a python module by starting the interpreter and importing the desired module.
     *
     * @param package The module to import.
     * @param py_home The home directory if it's different from pycpp::python_home (or the same, I don't judge)
     */
    py_module(std::string package, std::string py_home = ""){

      if (!py_home.empty()){
        setenv("PYTHONPATH", py_home.c_str(), 1);
      }
      else{
        setenv("PYTHONPATH", pycpp::python_home.c_str(), 1);
      }

      Py_SetProgramName((char *)pycpp::which_python.c_str());

      Py_Initialize();

      me = PyImport_Import(to_python(package));
      if (PyErr_Occurred()){
        PyErr_Print();
        throw std::runtime_error("Unable to import package");
      }
    }

    /**
     * Destructor - cleans up the python references and finalizes the interpreter.
     */
    ~py_module(){
      Py_CLEAR(me);
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

      check_callable(callable);

      PyObject *retval = PyObject_Call(callable, args, kwargs);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_CLEAR(args);
      Py_CLEAR(callable);
      PyDict_Clear(kwargs);
      Py_CLEAR(kwargs);

      return retval;
    }

    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given arguments
     * as the function's args tuple.  Creates a tuple of the arguments so that the function call can look like this:
     * <py_module>("<function>", {pycpp::to_python("string"), pycpp::to_python(<value>)})
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param l The initializer list of PyObject * types that make up the args of the function
     * @return The return value of the function as a PyObject *.  It is left to the user to convert that back to C++.
     */
    inline PyObject *operator()(const std::string attr, std::initializer_list<PyObject *> l) {

      PyObject *args = pycpp::make_tuple(l);

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      check_callable(callable);

      PyObject *retval = PyObject_Call(callable, args, NULL);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_CLEAR(args);
      Py_CLEAR(callable);

      return retval;
    }

    /**
     * Imports a class from a package so that members of that class can be called upon.  Name is under consideration for
     * changes.
     *
     * @param klass The class that is being imported - like pandas.DataFrame (for example)
     * @return A new py_module with the subpackage as its base.
     */
    py_module py_class(std::string klass, PyObject *args = NULL, PyObject *kwargs = NULL){

      assert(args == NULL || args == nullptr ||PyTuple_Check(args));
      assert(kwargs == NULL || kwargs == nullptr || PyDict_Check(kwargs));

      py_module out;

      out.me = PyInstance_New( //creates a new instance of a class
              PyObject_GetAttr(this->me, to_python(klass)), //choose the class
              args, //pass args/kwargs
              kwargs);

      Py_XDECREF(this->me); //keep reference counts in line

      if (PyErr_Occurred()){
        PyErr_Print();
      }

      if (out.me){ //if the class imported and it's not NULL
        return out;
      }
      else{ //else throw an error
        throw std::runtime_error("Class not imported!");
      }
    }

  };

} //pycpp


#endif //PY_CPP_PYMODULE_HPP
