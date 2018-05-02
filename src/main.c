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
	
int main(int argc, char* argv[]){
	if(argc != 4){
		fprintf(stderr,
			"Incorrect number of parameters. Usage: ./myomag <filename> <number of lines of the file> <number of splits for memory optimization>\n");
		exit(-1);
	}
	char filePath[30];
	strcpy(filePath, argv[1]);
	int nLines = strtol(argv[2], NULL, 10);
	int nSplits = strtol(argv[3], NULL, 10);
	if(nLines < 1){
		fprintf(stderr,
			"Incorrect nLines: The file can't have less than one line.\n");
		exit(-1);		
	}
	if(nSplits < 1){
		fprintf(stderr,
			"Incorrect nSplits: The number of splits can't be less than one.\n");
		exit(-1);		
	}

	myomag(filePath, nLines, nSplits);

	printf("Done.\n");
	
    return 0;
}
