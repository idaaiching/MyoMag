// main.c 
// The MyoMag program reads in a signal data and 
// process it to return its magnitude 
// at each time step.
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AccelerationMagnitude.h"  


int myomag(const char* filePath, int nLines, int nSplits){
	clock_t startTimestamp;
	clock_t endTimestamp;
	double magnitude_arr[nLines];
	int nRepetition = 1; // multiple executions of program to measure time 
	int i1 = 1, i2 = 300, i3 = 7023; // line index for printf

	printf("********** Start Myomag *********\n\n");
	startTimestamp = clock();
	for(int i = 0; i < nRepetition; i++){
		calculateMagnitudeFromCSV(filePath, magnitude_arr, nLines, nSplits);
	}
	endTimestamp = clock();

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
		nRepetition,
		(double)(endTimestamp - startTimestamp) / CLOCKS_PER_SEC );
	return 0;
}
	
int main(int argc, char* argv[])
{
	char filePath[30];
	strcpy(filePath, "data/AccData.csv");
	int nLines = 7024;
	int nSplits = 2;

	myomag(filePath, nLines, nSplits);

	printf("Done.\n");
	
    return 0;
}
