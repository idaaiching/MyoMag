// main.c 
// The MyoMag program reads in a signal data and 
// process it to return its magnitude 
// at each time step.
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "acc.h"  /* Include the header here, to obtain the function declaration */



int main(int argc, char* argv[])
{
	clock_t start_t, end_t;

	int steps = 500;
	int length = 7024;

	DATA data_1[length];
	DATA data_2_short[steps];

	double magnitude_1[7024] = {0};
	double magnitude_2[7024] = {0};

	char filepath[20];
	strcpy(filepath, "src/AccData.csv");
	int n_repetition = 100; // multiple execution of program to measure time 
	int idx_start = 0;
	int idx_end = 7024;
	int i1 = 0, i2 = 700, i3 = 7023;

	start_t = clock();
	for(int i = 0; i < n_repetition; i++){
		idx_end = readCSV(filepath, data_1, idx_start, idx_end); 
		calculateMagnitude(data_1, magnitude_1, idx_start, idx_end);
	}
	end_t = clock();

	printf("The magnitude has been calculated an saved in magnetude_array.\n"
		"The magnitude of lines %d, %d, %d are plotted here \n"
		" %g\n"
		" %g\n"
		" %g\n",
		i1, i2, i3,
		magnitude_1[i1],
		magnitude_1[i2],
		magnitude_1[i3]
		);
	

	printf("Total time taken by CPU for %d repetitions (all in one): %.2f seconds\n", 
		n_repetition,
		(double)(end_t - start_t) / CLOCKS_PER_SEC );


	start_t = clock();
	for(int i = 0; i < n_repetition; i++){
		for(idx_start = 0; (idx_start+500)  < length; idx_start+=500){
			idx_end = readCSV(filepath, data_2_short, idx_start, idx_start + 500); 
			calculateMagnitude(data_2_short, magnitude_2, idx_start, idx_start + 500);
		}
		if((length - idx_end ) > 0){
			readCSV(filepath, data_2_short, idx_end, length); 
			calculateMagnitude(data_2_short, magnitude_2, idx_end, length);	
		}
	}
	end_t = clock();

	printf("The magnitude has been calculated an saved in magnetude_array.\n"
		"The magnitude of lines %d, %d, %d are plotted here \n"
		" %g\n"
		" %g\n"
		" %g\n",
		i1, i2, i3,
		magnitude_2[i1],
		magnitude_2[i2],
		magnitude_2[i3]
		);
	

	printf("Total time taken by CPU for %d repetitions (memory optimisation): %.2f seconds\n", 
		n_repetition,
		(double)(end_t - start_t) / CLOCKS_PER_SEC );

	printf("Done.\n");

    return 0;
}
