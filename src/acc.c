// acc.c 

#include "acc.h"  
#include "DataLoader.h"


#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



double calculateMagnitude(const double x, const double y, const double z)
{
	return sqrt(x*x + y*y + z*z);
}

void myomag(const char *filepath, double *magnitude_arr, int nlines, int nsplits)
{
	int steps;
	steps = (nlines-1)/nsplits; // warning: integer division!
	Signal signal_arr[steps+1];
	int idx_start = 0;
	int idx_end = steps;
	int i;
	// read and process signal in packages of size <steps>
	for(idx_start = 0; idx_end  < nlines; idx_start += steps, idx_end += steps){
		readCSV(filepath, signal_arr, idx_start, idx_end); 
		for (i = 0; i <= (idx_end - idx_start); i++){
			magnitude_arr[idx_start+i] = calculateMagnitude(
				signal_arr[i].x, signal_arr[i].y, signal_arr[i].z);
		}
		if(idx_start == 0) idx_start++;
	}
	// remaining steps
	if((nlines - idx_start ) > 0){
		readCSV(filepath, signal_arr, idx_start, nlines-1); 

		for (i = 0; i <= (nlines-1 - idx_start); i++){
			magnitude_arr[idx_start + i] = calculateMagnitude(
				signal_arr[i].x, signal_arr[i].y, signal_arr[i].z);
		}		
	}
}

//**************************************************
// Extension module for Python
// make myomag function compatible to be called in Python
/*
#include <Python.h>
static PyObject*
PyMyomag(PyObject* self, PyObject* args, PyObject* kwds)
{
  //static char* argnames[] = {"filepath","nlines","nsplits", NULL};
  const char *filepath;
  int nlines;
  int nsplits;
  
  if(!PyArg_ParseTuple(args,"sii", &filepath, &nlines, &nsplits ))
    return NULL;

  // calculation of magnitude
  double magnitude[nlines]; //= {0};
  myomag(filepath, magnitude, nlines, nsplits);

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


