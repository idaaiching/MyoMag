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
	int n_repetition = 10;
	int checkpoint = 6990;

	
	start_t = clock();
	for(int i = 0; i < n_repetition; i++)
	{
		nlines = readCSV(filepath, data_arr, checkpoint); 
		calculateMagnitude(data_arr, magnitude_array, 7024, checkpoint);
	}
	end_t = clock();
	
	printf("The magnitude has been calculated an saved in magnetude_array.\n"
		"The first three lines are plotted here "
		"in the format (time, magnitude): \n"
		"%d: %g\n"
		"%d: %g\n"
		"%d: %g\n",
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
