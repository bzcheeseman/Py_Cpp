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

#include <Python.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../internal/logging.h"

#ifndef PROJECT_PY_MODULE_H
#define PROJECT_PY_MODULE_H

//! This allows us to use the python interpreter that CMake finds.
#ifndef PYC_WHICH_PYTHON
  #define PYC_WHICH_PYTHON "/usr/local/bin/ipython"
#endif

//! Gives us a smart value for the home directory - again from the CMake source directory.
#ifndef PYC_PY_HOME
  #define PYC_PY_HOME "../.."
#endif

/*
 * TODO: Implement an error struct like in hA?
 */

/**
 * @file include/py_object.h
 *
 * Holds the C implementation of the pycpp tools. Not all the tools are here because of the lack of function and
 * operator overloading in C, and wanting to keep the interface clean. This version leaves the conversion to python up
 * to the user of the library, although that user is welcome to see the implementation for the conversion functions in
 * py_object.hpp for guidance.
 */

/**
 * Selects the python executable - this is important to choose right because the wrong choice can have grave
 * consequences - a.k.a. things won't work.  If you're having trouble I recommend changing this first,
 * especially if you used homebrew to get another python distribution alongside your system python.
 */
char *pyc_which_python = PYC_WHICH_PYTHON;

/**
 * Sets the python home.  Generally scripts will be in the directory one up from build, so this is the default value.
 * However this is easily changed by calling pycpp::python_home = "path/to/script".
 */
char *pyc_python_home = PYC_PY_HOME;

/**
 * @struct py_object
 * @brief Holds the PyObject that represents the module (or class) we've imported.
 *
 * Holds the module we imported (or class) as well as the logs for the module.  The logfiles are stored in
 * the build folder. That can be changed but will require changing the names of the logfiles in each of their calls
 * in this file.
 */
struct py_object{
  //! The PyObject that represents the object we're trying to import/call
  PyObject *me;

  //! Holds the logfiles for a module.
  logs_t *log;

  //! Whether or not this py_object is a subclass - so we don't finalize the interpreter too early!
  bool is_subclass;
};

typedef struct py_object py_object;

/**
 * Checks if a PyObject * is callable - throws an error if it's not.
 *
 * @param obj PyObject * to check.
 */
bool check_callable(PyObject *obj, logs_t *logs) {
  if (PyCallable_Check(obj)) {
    char *callable = strncat(PyString_AsString(PyObject_Repr(obj)), " is callable!", 13);
    to_log("callables.log", callable, logs);
    return true;
  }
  else {
    char *callable = strncat(PyString_AsString(PyObject_Repr(obj)), " not callable!", 14);
    to_log("callables.log", callable, logs);
    return false;
  }
}

/**
 * Create a new py_object struct that holds all the various items needed to call python objects.
 *
 * @param package Which package to import
 * @param py_home Where to set the python home. If set to NULL, defaults to the cmake path
 * @return New py_object that contains a python object and (if needed) its subclasses.
 */
py_object *new_py_object(const char *package, const char *py_home){

  py_object *newmodule = malloc(sizeof(py_object));
  newmodule->log = new_logs();

  if (py_home){
    setenv("PYTHONPATH", py_home, 1);
  }
  else{
    setenv("PYTHONPATH", pyc_python_home, 1);
  }

  Py_SetProgramName(pyc_which_python);

  if (!Py_IsInitialized()){
    Py_Initialize();
  }

  newmodule->me = PyImport_Import(PyString_FromString(package));
  if (PyErr_Occurred()){
    PyErr_Print();
    to_log("imports.log", "Unsuccessful import of: ", newmodule->log);
    to_log("imports.log", package, newmodule->log);
    return NULL;
  }
  to_log("imports.log", "Successful import of: ", newmodule->log);
  to_log("imports.log", package, newmodule->log);

  return newmodule;
}

/**
 * Frees memory associated with the py_object.
 *
 * @param module The module to free
 */
void delete_py_object(py_object *module){
  if (!module->is_subclass){
    Py_Finalize();
  }
  free(module);
}

/**
 * @brief Makes a PyTuple.
 *
 * Makes a python tuple for the purpose of passing arguments to a python function. All arguments to this function MUST
 * be of type PyObject *
 *
 * @param num Number of arguments to the function
 * @param ... Variable number of arguments of the type PyObject *
 * @return A PyTuple that can be passed directly to py_call.
 */
PyObject *pyc_make_tuple(int num, ...){

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
 * arguments is as follows: make_dict(2*n, PyObject *key, PyObject *value, ...) where
 * n is the total number of key-value PAIRS.
 *
 * @param num Number of arguments to the function
 * @param ... Variable number of arguments of type PyObject *
 * @return A PyDict that can be passed directly to py_call.
 */
PyObject *pyc_make_dict(int num, ...){
  if (num == 0){
    return NULL;
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
 * An example function that takes an array of doubles and makes a python list from that array.
 *
 * @param list C style array of doubles
 * @param len Length of the input (and output array)
 * @return PyObject that represents a python list of length len
 */
PyObject *pyc_make_list(double *list, size_t len){
  PyObject *out = PyList_New(len);

  for (size_t i = 0; i < len; i++){
    PyList_SetItem(out, i, PyFloat_FromDouble(list[i]));
  }

  return out;
}

/**
 * Calls a python function directly from python. Use the pyc_make_dict and pyc_make_tuple functions to pass arguments
 * to this function.
 *
 * @param module The struct that holds the items we need to make a python call
 * @param attr The function (attribute) we want to call from a module
 * @param args The args to pass to the function as a PyTuple
 * @param kwargs The keyword args to pass to the function as a PyDict
 * @return The return value of the function call - conversion is up to the user
 */
PyObject *pyc_py_call(py_object *module, const char *attr, PyObject *args, PyObject *kwargs){

  assert(PyTuple_Check(args));
  assert(kwargs == NULL || PyDict_Check(kwargs));

  if (module) {
    PyObject *callable = PyObject_GetAttrString(module->me, attr);

    if (PyErr_Occurred()){
      PyErr_Print();
      return NULL;
    }

    if (check_callable(callable, module->log)) {
      PyObject *retval;

      if (kwargs == NULL) {
        retval = PyObject_Call(callable, args, NULL);
      } else if (PyDict_Check(kwargs)) {
        retval = PyObject_Call(callable, args, kwargs);
      } else {
        to_log("object_call.log", "Error, kwargs not NULL or a PyDict", module->log);
      }
      if (PyErr_Occurred()) {
        PyErr_Print();
        to_log("object_call.log", "Error during object call, attr: ", module->log);
        to_log("object_call.log", attr, module->log);
      }

      Py_CLEAR(args);
      Py_CLEAR(callable);
      if (kwargs) {
        PyDict_Clear(kwargs);
        Py_CLEAR(kwargs);
      }

      return retval;
    }
  }
  else{
    return NULL;
  }
}

/**
 * Imports a class from a module.
 *
 * @param module The overall module (or file) already imported
 * @param klass The submodule (or class) to import
 * @param args Arguments to pass to class constructor
 * @param kwargs Keyword arguments to pass to the class constructor
 * @return A new py_object with the imported class contained within it.
 */
py_object *pyc_py_class(py_object *module, const char *klass, PyObject *args, PyObject *kwargs){

  assert(args == NULL || PyTuple_Check(args));
  assert(kwargs == NULL || PyDict_Check(kwargs));

  //setup the new output module
  py_object *out = malloc(sizeof(py_object));
  out->log = new_logs();

  out->me = PyInstance_New( //creates a new instance of a class
          PyObject_GetAttr(module->me, PyString_FromString(klass)), //choose the class
          args, //pass args
          kwargs); //pass kwargs

  out->is_subclass = true;

  if (PyErr_Occurred()){
    PyErr_Print();
    to_log("subclass.log", "Problem creating instance of class: ", module->log);
    to_log("subclass.log", klass, module->log);
  }

  Py_XDECREF(module->me); //keep reference counts in line

  if (out->me){ //if the class imported and it's not NULL
    return out;
  }
  else{ //else throw an error
    return NULL;
  }
}




#endif //PROJECT_PY_MODULE_H
