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
#include <map>
#include <type_traits>

/**
 * @todo: update docs
 */

/**
 * @file include/py_object.hpp
 *
 * Holds the pycpp namespace. All the methods and functions related to importing Python modules and converting C++ values
 * to python are here.
 */

//! This allows us to use the python interpreter that CMake finds or overload it
#ifndef PYCPP_WHICH_PYTHON
  #define PYCPP_WHICH_PYTHON "/usr/local/bin/ipython"
#endif

//! Gives us a smart value for the home directory - again from the CMake source directory.
#ifndef PYCPP_PY_HOME
  #define PYCPP_PY_HOME "../.."
#endif

namespace pycpp {

  class py_object;

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
  inline PyObject *to_python(const std::vector<int> &vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyInt_FromLong((long) vec[i]));
    }
    return pyvec;
  }

  /**
   * @brief Takes a vector to a python list.
   *
   * @param vec Vector of ints to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<int> &&vec) {
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
  inline PyObject *to_python(const std::vector<long> &vec) {
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
  inline PyObject *to_python(std::vector<long> &&vec) {
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
  inline PyObject *to_python(const std::vector<double> &vec) {
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
   * @param vec Vector of doubles to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<double> &&vec) {
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
  inline PyObject *to_python(const std::vector<float> &vec) {
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
  inline PyObject *to_python(std::vector<float> &&vec) {
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
   * @param vec Vector of strings to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const std::vector<std::string> &vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyString_FromString(vec[i].c_str()));
    }
    return pyvec;
  }

  /**
   * @copybrief PyObject*to_python(std::vector<int>)
   *
   * @param vec Vector of strings to take to a Python list.
   * @return A python list ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::vector<std::string> &&vec) {
    long n = vec.size();
    PyObject *pyvec = PyList_New(n);
    for (int i = 0; i < n; i++) {
      PyList_SetItem(pyvec, i, PyString_FromString(vec[i].c_str()));
    }
    return pyvec;
  }

  /**
   * @brief Takes an int to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const int &num){
    return PyInt_FromLong((long)num);
  }

  /**
   * @brief Takes an int to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(int &&num){
    return PyInt_FromLong((long)num);
  }

  /**
   * @brief Takes a long to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const long &num){
    return PyInt_FromLong(num);
  }

  /**
   * @brief Takes a long to a python int.  Thin wrapper around PyInt_FromLong.
   *
   * @param num Numeric value to be converted
   * @return A python int ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(long &&num){
    return PyInt_FromLong(num);
  }

  /**
   * @brief Takes a float to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const float &num){
    return PyFloat_FromDouble((double)num);
  }

  /**
   * @brief Takes a float to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(float &&num){
    return PyFloat_FromDouble((double)num);
  }

  /**
   * @brief Takes a double to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const double &num){
    return PyFloat_FromDouble(num);
  }

  /**
   * @brief Takes a double to a python float.  Thin wrapper around PyFloat_FromDouble.
   *
   * @param num Numeric value to be converted
   * @return A python float ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(double &&num){
    return PyFloat_FromDouble(num);
  }

  /**
   * @brief Takes an std::string to a Python string.  Thin wrapper around PyString_FromString.
   *
   * @param str The std::string to be converted
   * @return A python string ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const std::string &str){
    return PyString_FromString(str.c_str());
  }

  /**
   * @brief Takes an std::string to a Python string.  Thin wrapper around PyString_FromString.
   *
   * @param str The std::string to be converted
   * @return A python string ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(std::string &&str){
    return PyString_FromString(str.c_str());
  }

  /**
   * @brief Takes a char * to a Python string. Thin wrapper around PyString_FromString.
   *
   * @param str The char * to be converted
   * @return A python string ready to be put into an appropriate pycpp function.
   */
  inline PyObject *to_python(const char *str){
    return PyString_FromString(str);
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

  //! String specialization
  void from_python(PyObject *pyobj, std::string &cppobj) {
    cppobj = std::string(PyString_AsString(pyobj));
  };

  //! Int specialization
  void from_python(PyObject *pyobj, int &cppobj) {
    cppobj = (int) PyInt_AsLong(pyobj);
  };

  //! Long specialization
  void from_python(PyObject *pyobj, long &cppobj) {
    cppobj = PyInt_AsLong(pyobj);
  };

  //! Float specialization
  void from_python(PyObject *pyobj, float &cppobj) {
    cppobj = (float) PyFloat_AsDouble(pyobj);
  };

  //! Double specialization
  void from_python(PyObject *pyobj, double &cppobj) {
    cppobj = PyFloat_AsDouble(pyobj);
  };

  //! String vector specialization
  void from_python(PyObject *pyobj, std::vector<std::string> &cppobj) {
    PyList_Check(pyobj);
    size_t len = PyList_Size(pyobj);
    PyObject *item;
    for (size_t i = 0; i < len; i++){
      PyList_GetItem(item, i);
      cppobj.push_back(PyString_AsString(item));
    }
  };

  //! Int vector specialization
  void from_python(PyObject *pyobj, std::vector<int> &cppobj) {
    PyList_Check(pyobj);
    size_t len = PyList_Size(pyobj);
    PyObject *item;
    for (size_t i = 0; i < len; i++){
      PyList_GetItem(item, i);
      cppobj.push_back((int)PyInt_AsLong(item));
    }
  };

  //! Long vector specialization
  void from_python(PyObject *pyobj, std::vector<long> &cppobj) {
    PyList_Check(pyobj);
    size_t len = PyList_Size(pyobj);
    PyObject *item;
    for (size_t i = 0; i < len; i++){
      PyList_GetItem(item, i);
      cppobj.push_back(PyInt_AsLong(item));
    }
  };

  //! Float vector specialization
  void from_python(PyObject *pyobj, std::vector<float> &cppobj) {
    PyList_Check(pyobj);
    size_t len = PyList_Size(pyobj);
    PyObject *item;
    for (size_t i = 0; i < len; i++){
      PyList_GetItem(item, i);
      cppobj.push_back((float)PyFloat_AsDouble(item));
    }
  };

  //! Double vector specialization
  void from_python(PyObject *pyobj, std::vector<double> &cppobj) {
    PyList_Check(pyobj);
    size_t len = PyList_Size(pyobj);
    PyObject *item;
    for (size_t i = 0; i < len; i++){
      PyList_GetItem(item, i);
      cppobj.push_back(PyFloat_AsDouble(item));
    }
  };

  /**
   * @brief Makes a PyTuple.
   *
   * Makes a python tuple for the purpose of passing arguments to a python function. All arguments to this function MUST
   * be of type PyObject * as follows: make_tuple({pycpp::to_python(<value_1>), pycpp::to_python(<value_2>)})
   *
   * @param l The initializer list of arguments to be put into the tuple.
   * @return A PyTuple that can be passed directly to the py_object operator() call.
   */
  inline PyObject *make_tuple(std::initializer_list<PyObject *> &l){

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
   * @return A PyDict that can be passed directly to the py_object operator() call.
   */
  inline PyObject *make_dict(std::initializer_list<PyObject *> &l){
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
   * @class py_object include/py_object.hpp
   *
   * Imports a python module and offers call operators to simplify calling member functions of that module from C++.
   */
  class py_object {
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

  public:

    /**
     * Default constructor - used internally only to make sure everything is working properly.
     */
    py_object(){};

    /**
     * Allows for setting a py_object as a regular python object - as an object instead of a module or class. Also adds
     * the object to the global namespace.
     *
     * @param obj The python object we're tring to set to Python
     */
    py_object(PyObject *obj){
      me = std::move(obj);
      Py_XDECREF(obj);
    }

    /**
     * Initializes a python module by starting the interpreter and importing the desired module.
     *
     * @param package The module to import.
     * @param py_home The home directory if it's different from pycpp::python_home (or the same, I don't judge)
     */
    py_object(const std::string &package,
              const std::string &py_home = ""){

      if (!py_home.empty()){
        setenv("PYTHONPATH", py_home.c_str(), 1);
      }
      else{
        setenv("PYTHONPATH", pycpp::python_home.c_str(), 1);
      }

      Py_SetProgramName((char *)pycpp::which_python.c_str());

      if (!Py_IsInitialized()){
        Py_Initialize();
      }

      me = PyImport_Import(to_python(package));
      if (PyErr_Occurred()){
        PyErr_Print();
        throw std::runtime_error("Unable to import package");
      }

    }

    /**
     * Destructor - cleans up the python references and finalizes the interpreter.
     */
    ~py_object(){
      Py_CLEAR(me);
      Py_Finalize();
    }

    /**
     * Allows us to cleanly call functions that take no arguments.
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @return The return value of the function if there is one.
     */
    inline PyObject *operator()(const std::string &attr){
      return this->operator()(attr, {});
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
    inline PyObject *operator()(const std::string &attr,
                                PyObject *args,
                                PyObject *kwargs = NULL){
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
     * <py_object>("<function>", {pycpp::to_python("string"), pycpp::to_python(<value>)})
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args The initializer list of PyObject * types that make up the args of the function
     * @return The return value of the function as a PyObject *.  It is left to the user to convert that back to C++.
     */
    inline PyObject *operator()(const std::string &attr,
                                std::initializer_list<PyObject *> arg) {

      PyObject *args = pycpp::make_tuple(arg);

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
     * Given a string that is exactly a member function of a python module, calls that function with the given arguments
     * as the function's args tuple.  Creates a tuple of the arguments so that the function call can look like this:
     * <py_object>("<function>", {pycpp::to_python("string"), pycpp::to_python(<value>)})
     *
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args The initializer list of PyObject * types that make up the args of the function
     * @param args The initializer list of PyObject * types that make up the keyword args of the function
     * @return The return value of the function as a PyObject *.  It is left to the user to convert that back to C++.
     */
    inline PyObject *operator()(const std::string &attr,
                                std::initializer_list<PyObject *> arg,
                                std::initializer_list<PyObject *> kwarg) {

      PyObject *args = pycpp::make_tuple(arg);
      PyObject *kwargs = pycpp::make_dict(kwarg);

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      check_callable(callable);

      PyObject *retval = PyObject_Call(callable, args, kwargs);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_CLEAR(args);
      Py_CLEAR(kwargs);
      Py_CLEAR(callable);

      return retval;
    }

    /**
     * Allows us to cleanly call functions that take no arguments.
     *
     * @tparam T The C++ type of the return value of the function
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @return The return value of the function as its C++ type.
     */
    template<typename T>
    inline void operator()(const std::string &attr,
                           T &cpp_retval){
      (*this)(attr, cpp_retval, {});

      return;
    }

    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given args
     * and kwargs.  args is a PyTuple and kwargs is a PyDict - the user can either create their own or use the pycpp
     * functions make_tuple and make_dict provided here.
     * 
     * @tparam T C++ type of return value of specified function
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args PyTuple that holds the arguments to pass to the function.
     * @param kwargs PyDict that holds the keyword arguments to pass to the function.
     * @return The return value of the function as its C++ type. Throws errors if the object is not the correct type.
     */
    template<typename T>
    inline void operator()(const std::string &attr,
                           T &cpp_retval,
                           PyObject *args,
                           PyObject *kwargs = NULL){
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

      from_python(retval, cpp_retval);

      return;
    }
    
    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given arguments
     * as the function's args tuple.  Creates a tuple of the arguments so that the function call can look like this:
     * <py_object>("<function>", {pycpp::to_python("string"), pycpp::to_python(<value>)})
     * 
     * @tparam T C++ type of return value of specified function
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args The initializer list of PyObject * types that make up the args of the function
     * @return The return value of the function as its C++ type. Throws errors if the object is not the correct type.
     */
    template<typename T>
    inline void operator()(const std::string &attr,
                           T &cpp_retval,
                           std::initializer_list<PyObject *> arg){
      
      PyObject *args = pycpp::make_tuple(arg);

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      check_callable(callable);

      PyObject *retval = PyObject_Call(callable, args, NULL);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_CLEAR(args);
      Py_CLEAR(callable);

      from_python(retval, cpp_retval);

      return;
      
    }

    /**
     * Given a string that is exactly a member function of a python module, calls that function with the given arguments
     * as the function's args tuple.  Creates a tuple of the arguments so that the function call can look like this:
     * <py_object>("<function>", {pycpp::to_python("string"), pycpp::to_python(<value>)}, {pybpp::to_python("kwarg_key"), pycpp::to_python("kwarg_arg")})
     *
     * @tparam T C++ type of return value of specified function
     * @param attr String that is exactly the name of a member function of the python module initialized.
     * @param args The initializer list of PyObject * types that make up the args of the function
     * @param kwargs The initializer list of PyObject *types that make up the keyword arguments of the function
     * @return The return value of the function as its C++ type. Throws errors if the object is not the correct type.
     */
    template<typename T>
    inline void operator()(const std::string &attr,
                           T &cpp_retval,
                           std::initializer_list<PyObject *> arg,
                           std::initializer_list<PyObject *> kwarg){

      PyObject *args = pycpp::make_tuple(arg);
      PyObject *kwargs = pycpp::make_dict(kwarg);

      PyObject *callable = PyObject_GetAttrString(me, attr.c_str());

      check_callable(callable);

      PyObject *retval = PyObject_Call(callable, args, kwargs);
      if (PyErr_Occurred()){
        PyErr_Print();
      }

      Py_CLEAR(args);
      Py_CLEAR(kwargs);
      Py_CLEAR(callable);

      from_python(retval, cpp_retval);

      return;

    }

    /**
     * Imports a class from a package so that members of that class can be called upon.  Name is under consideration for
     * changes.
     *
     * @param klass The class that is being imported - like pandas.DataFrame (for example)
     * @return A new py_object with the subpackage as its base.
     */
    py_object py_class(const std::string &klass, PyObject *args = NULL, PyObject *kwargs = NULL){

      assert(args == NULL || args == nullptr ||PyTuple_Check(args));
      assert(kwargs == NULL || kwargs == nullptr || PyDict_Check(kwargs));

      py_object out;

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
