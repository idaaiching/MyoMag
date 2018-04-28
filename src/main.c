// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acc.h"  /* Include the header here, to obtain the function declaration */



int main(int argc, char* argv[])
{

	struct accelerometer acc_data[7024];
	char filepath[20];
	strcpy(filepath, "src/AccData.csv");
	int error = 0;
	error = readCSV(filepath, acc_data); 
	if (error == 1)
		printf("error: %d\n", error);
	printf("here is the first time: ");
	printf("%g\n", acc_data[1].x);
	printf("here is the last time: ");
	printf("%d\n", acc_data[2].t);

	struct accelerometer instance[1] = {
		{.t = 10, .x=6., .y=3., .z=2.}
	};
	printf("here is the last time: ");
	printf("%d\n", instance[0].t);
	
	double magnitude_array[7024];
	calculateMagnitude(acc_data, magnitude_array, 7024);
	printf("length is %lu\n", sizeof(acc_data)/sizeof(acc_data[0]));
	printf("magnitude is %g\n", magnitude_array[2]);
	printf("%g\n", magnitude_array[0]);
	printf("%g\n", magnitude_array[1]);

    return 0;
}
