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

	// int n = 7024; // number of lines in the csv file
	DATA data_arr[7024];
	double magnitude_array[7024] = {0};
	char filepath[20];
	strcpy(filepath, "src/AccData.csv");
	int nlines = 0;
	int n_repetition = 100; // multiple execution of program to measure time 
	int idx_start = 0;
	int idx_end = 7024;
	int plotted_lines[3] = {7000, 7001, 7002};


	start_t = clock();
	for(int i = 0; i < n_repetition; i++)
	{

		idx_end = readCSV(filepath, data_arr, idx_start, idx_end); 
		calculateMagnitude(data_arr, magnitude_array, idx_start, idx_end);
	}
	end_t = clock();

	printf("The magnitude has been calculated an saved in magnetude_array.\n"
		"The lines %d, %d, %d are plotted here "
		"in the format (time, magnitude): \n"
		"%d: %g\n"
		"%d: %g\n"
		"%d: %g\n",
		plotted_lines[0], plotted_lines[1], plotted_lines[2],
		data_arr[7000].t, magnitude_array[7000],
		data_arr[7001].t, magnitude_array[7001],
		data_arr[7002].t, magnitude_array[7002]
		);
	

	printf("Total time taken by CPU for %d repetitions: %.2f seconds\n", 
		n_repetition,
		(double)(end_t - start_t) / CLOCKS_PER_SEC );

	printf("Done.\n");

    return 0;
}
