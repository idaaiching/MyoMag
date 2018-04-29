// acc.c 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "acc.h"  

#define MAXLINE 100 // storage for one line
#define MAXLENGTH 100 // numer of csv-lines stored in one dump 

int readCSV(const char *filepath, DATA *acc_data)	
{
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if(fp == NULL){
    	printf("Error: Failed to open csv file!");
    	return 1;
    }
	char line[MAXLINE];
	DATA instance;
	int narr = 4;
	char *arr[narr];
	int na;
	int line_idx = 0;
	int idx = 0;
	while(fgets(line, sizeof(line), fp) != NULL)
	{
		na = getLine(line, arr, narr);
		if (na > narr)
		{
			printf("Error: Line %d\n has only %d\n entries for t, x, y, z.  Expected %d\n!", 
				line_idx, na, narr);
			break;			
		}

		instance.t = atoi(arr[0]);
		instance.x = atof(arr[1]);
		instance.y = atof(arr[2]);
		instance.z = atof(arr[3]);
		acc_data[idx] = instance;
		idx++;
		line_idx++;
	};
	fclose(fp);

	return 0;
}

// loops through one line and saves each column entry in the entry_array
// for MyoMag: entry_arr = [t, x, y, z] of one line
int getLine(char *line, char *entry_arr[], int nentries)
{
	char *p;
	size_t na = 0; /* idx of col in csv file */
	char prevc = ',';   /* force recognizing first field */
	char *dp = NULL;

	for(p = line; *p != '\0'; prevc = *p, p++)
	{
		if(prevc == ',')
		{
			/* start new field */
			if(dp != NULL)
				*dp = '\0';  /*terminate prev*/
			if(na >= nentries)
				return na;
			entry_arr[na++] = p;
			dp = p;
		}
		if(*p != ',')
			*dp++ = *p;
	}
	if(dp != NULL)
		*dp = '\0';
	if(na < nentries)
		entry_arr[na] = NULL;
	return na;
}

void calculateMagnitude(const DATA *acc_data, double *magnitude_arr, int number_of_entries)
{
	for ( int i=0; i < number_of_entries; i++ ){
		magnitude_arr[i] = sqrt(
		pow(acc_data[i].x, 2) + pow(acc_data[i].y, 2) + pow(acc_data[i].z, 2)
		);
	}	
}



