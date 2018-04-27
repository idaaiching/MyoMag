// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "acc.h"  /* Include the header here, to obtain the function declaration */



int main(int argc, char* argv[])
{
	struct accelerometer acc_data[7024];
	char filepath[20];
	strcpy(filepath, "AccData.csv");
	int error = 0;
	error = readcsv(filepath, acc_data); 
	if (error == 1)
		printf("error: %d\n", error);
	printf("here is the first time: ");
	printf("%g\n", acc_data[1].x);
	printf("here is the last time: ");
	printf("%d\n", acc_data[2].t);


	double magnitude_array[7024];
	magnitude(acc_data, magnitude_array);
	printf("length is %lu\n", sizeof(acc_data)/sizeof(acc_data[0]));
	printf("magnitude is %g\n", magnitude_array[2]);
	printf("%g\n", magnitude_array[5]);
	printf("%g\n", magnitude_array[2000]);
    return 0;
}