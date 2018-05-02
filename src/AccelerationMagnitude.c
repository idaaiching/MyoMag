// AccelerationMagnitude.c 

#include "AccelerationMagnitude.h"  
#include "DataLoader.h"


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



double calculateMagnitude(const double x, const double y, const double z){
	return sqrt(x*x + y*y + z*z);
}

void calculateMagnitudeFromCSV(const char *filePath, double *magnitude_arr, int nlines, int nsplits){
	int steps;
	steps = (nlines-1)/nsplits; // warning: integer division!
	Signal signal_arr[steps+1];
	int lineStart = 0;
	int lineEnd = steps;
	int i;
	// read and process signal in packages of size <steps>
	for(lineStart = 0; lineEnd  < nlines; lineStart += steps, lineEnd += steps){
		readCSV(filePath, signal_arr, lineStart, lineEnd); 
		for (i = 0; i <= (lineEnd - lineStart); i++){
			magnitude_arr[lineStart+i] = calculateMagnitude(
				signal_arr[i].x, signal_arr[i].y, signal_arr[i].z);
		}
		if(lineStart == 0) lineStart++;
	}
	// remaining steps
	if(nlines  > lineStart){
		readCSV(filePath, signal_arr, lineStart, nlines-1); 
		for (i = 0; i + lineStart < nlines ; i++){
			magnitude_arr[lineStart + i] = calculateMagnitude(
				signal_arr[i].x, signal_arr[i].y, signal_arr[i].z);
		}		
	}
}

//**************************************************
// Extension module for Python
// make calculateMagnitudeFromCSV function compatible to be called in Python
/*
#include <Python.h>
static PyObject*
PyMyomag(PyObject* self, PyObject* args, PyObject* kwds)
{
  //static char* argnames[] = {"filePath","nlines","nsplits", NULL};
  const char *filePath;
  int nlines;
  int nsplits;
  
  if(!PyArg_ParseTuple(args,"sii", &filePath, &nlines, &nsplits ))
    return NULL;

  // calculation of magnitude
  double magnitude[nlines]; //= {0};
  calculateMagnitudeFromCSV(filePath, magnitude, nlines, nsplits);

  // conversion from C-object(magnitude) to a Python object (result)
  Py_ssize_t len = nlines;
  PyObject *result = PyTuple_New(len);
  for (Py_ssize_t i = 0; i < len; i++) {
    PyTuple_SET_ITEM(result, i, PyFloat_FromDouble(magnitude[i]));
  }
  
  return Py_BuildValue("O", result);
}

static char PyMyomag_docs[] =
  "Extension module PyMyomag to calculate the magnitude of an accelerometer signal.\n";


static PyMethodDef PyMyomag_funcs[] = {
  {"PyMyomag", (PyCFunction)PyMyomag, METH_VARARGS, PyMyomag_docs},
  {NULL}
};

void initPyMyomag(void)
{
  Py_InitModule3("PyMyomag", PyMyomag_funcs,
		 "Extension module PyMyomag to calculate the magnitude of an accelerometer signal.");
}
*/


