// main.c 
// The MyoMag program reads in a signal data and 
// process it to return its magnitude 
// at each time step.
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acc.h"  


int main(int argc, char* argv[])
{
	clock_t start_timestamp;
	clock_t end_timestamp;
	int nlines = 7024;
	double magnitude_arr[7024] = {0};
	char filepath[20];
	strcpy(filepath, "src/AccData.csv");
	int n_repetition = 1; // multiple executions of program to measure time 
	int i1 = 1, i2 = 300, i3 = 7023; // line index for plotting

	printf("********** Start Myomag *********\n\n");
	start_timestamp = clock();
	for(int i = 0; i < n_repetition; i++){
		myomag(filepath, magnitude_arr, nlines, 2);
	}
	end_timestamp = clock();

	// ********* Printing results
	printf("The magnitude has been calculated an saved in magnetude_array.\n"
		"The magnitude of lines %d, %d, %d are plotted here \n"
		" %g, %g, %g\n",
		i1, i2, i3,
		magnitude_arr[i1],
		magnitude_arr[i2],
		magnitude_arr[i3]
		);
	printf("Total time taken by CPU for %d repetitions: %.2f seconds\n", 
		n_repetition,
		(double)(end_timestamp - start_timestamp) / CLOCKS_PER_SEC );

	printf("Done.\n");
	
    return 0;
}
