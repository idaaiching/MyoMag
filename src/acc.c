// acc.c 

#include "acc.h"  
//#include "AccelerationMagnitude.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MAXLINE 100 // storage for one line

// returns number of lines read in.
int readCSV( const char *filepath, Signal *signal_arr, int idx_start, int idx_end )	
{
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if(fp == NULL){
    	printf("Error: Failed to open csv file!");
    	return 1;
    }
	char line[MAXLINE];
	Signal instance;
	int n_col_csv = 4; 
	char *line_arr[n_col_csv];
	int na;
	int idx = 0;
	while( fgets(line, sizeof(line), fp) != NULL && idx <= idx_end){
		if( idx < idx_start) 
		{
			idx++;
			continue;			
		}
		na = getLine(line, line_arr, n_col_csv);
		if (na > n_col_csv){
			printf("Error: Line %d\n has only %d\n entries for t, x, y, z.  Expected %d\n!", 
				idx, na, n_col_csv);
			break;			
		}		
		instance.t = atoi( line_arr[0] );
		instance.x = atof( line_arr[1] );
		instance.y = atof( line_arr[2] );
		instance.z = atof( line_arr[3] );
		signal_arr[idx - idx_start] = instance;
		idx++;
	};
	fclose(fp);
	return idx;
}

// loops through one line and saves each column entry in the line_arr
// for MyoMag: line_arr = [t, x, y, z] of one line
int getLine( char *line, char *line_arr[], int n_col_csv)
{
	char *p;
	int na = 0; /* idx of col in csv file */
	char prevc = ',';   /* force recognizing first field */
	char *dp = NULL;

	for ( p = line; *p != '\0'; prevc = *p, p++){
		if ( prevc == ',' ){
			/* start new field */
			if ( dp != NULL)
				*dp = '\0';  /*terminate prev*/
			if ( na >= n_col_csv)
				return na;
			line_arr[na++] = p;
			dp = p;
		}
		if ( *p != ',' )
			*dp++ = *p;
	}
	if ( dp != NULL )
		*dp = '\0';
	if ( na < n_col_csv)
		line_arr[na] = NULL;
	return na;
}

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
			magnitude_arr[idx_start+i] = calculateMagnitude(
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


