// acc.c 

#include "acc.h"  
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLENGTH 7024

int readcsv(const char *filepath, struct accelerometer acc_data[])	
{
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if(fp == NULL){
    	printf("Error: Failed to open csv file!");
    	return 1;
    }
	char line[MAXLENGTH];
	struct accelerometer acc_one_line;
	size_t narr = 4;
	char *arr[narr];

	size_t idx = 0;
	while(fgets(line, sizeof(line), fp) != NULL)
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
				arr[na++] = p;
				dp = p;
				}
			if(*p != ',')
				*dp++ = *p;
			}
		if(dp != NULL)
			*dp = '\0';

		//if(na >= 5) break;
		acc_one_line.t = atoi(arr[0]);
		acc_one_line.x = atof(arr[1]);
		acc_one_line.y = atof(arr[2]);
		acc_one_line.z = atof(arr[3]);
		acc_data[idx] = acc_one_line;
		idx++;
	};
	fclose(fp);

	return 0;
}

void magnitude(struct accelerometer acc_data[], double magnitude_arr[])
{
	size_t length_acc_data = 7024; //sizeof(acc_data)/sizeof(acc_data[0]);
	for ( size_t i=0; i < length_acc_data; i++ ){
		magnitude_arr[i] = sqrt(
		pow(acc_data[i].x, 2) + pow(acc_data[i].y, 2) + pow(acc_data[i].z, 2)
		);
	}
}
