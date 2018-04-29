// acc.c 

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "acc.h"  

#define MAXLINE 100 // storage for one line
#define MAXLENGTH 100 // numer of csv-lines stored in one dump 

// returns number of lines read in.
int readCSV( const char *filepath, DATA *data_arr, int idx_checkpoint )	
{
    FILE *fp = NULL;
    fp = fopen(filepath, "r");
    if(fp == NULL){
    	printf("Error: Failed to open csv file!");
    	return 1;
    }
	char line[MAXLINE];
	DATA instance;
	int n_col_csv = 4; 
	char *line_arr[n_col_csv];
	int na;
	int idx = 0;
	while( fgets(line, sizeof(line), fp) != NULL ){
		if( idx < idx_checkpoint) 
		{
			idx++;
			continue;			
		}

		na = getLine(line, line_arr, n_col_csv);
		if (na > n_col_csv){
			printf("Error: Line %d\n has only %d\n entries for t, x, y, z.  Expected %d\n!", 
				idx, na, n_col_csv);
			break;			
		}
		
		instance.t = atoi( line_arr[0] );
		instance.x = atof( line_arr[1] );
		instance.y = atof( line_arr[2] );
		instance.z = atof( line_arr[3] );
		data_arr[idx] = instance;
		//printf("Line %d has been read in! %d %g %g %g \n", idx, instance.t, instance.x, instance.y, instance.z);
		idx++;
	};
	fclose(fp);

	return idx;
}

// loops through one line and saves each column entry in the line_arr
// for MyoMag: line_arr = [t, x, y, z] of one line
int getLine( char *line, char *line_arr[], int n_col_csv)
{
	char *p;
	size_t na = 0; /* idx of col in csv file */
	char prevc = ',';   /* force recognizing first field */
	char *dp = NULL;

	for ( p = line; *p != '\0'; prevc = *p, p++){
		if ( prevc == ',' ){
			/* start new field */
			if ( dp != NULL)
				*dp = '\0';  /*terminate prev*/
			if ( na >= n_col_csv)
				return na;
			line_arr[na++] = p;
			dp = p;
		}
		if ( *p != ',' )
			*dp++ = *p;
	}
	if ( dp != NULL )
		*dp = '\0';
	if ( na < n_col_csv)
		line_arr[na] = NULL;
	return na;
}

void calculateMagnitude(const DATA *data_arr, double *magnitude_arr, int n_lines_csv, int idx_checkpoint )
{
	for ( int i=idx_checkpoint; i < n_lines_csv; i++ ){
		magnitude_arr[i] = sqrt(
		pow(data_arr[i].x, 2) + 
		pow(data_arr[i].y, 2) + 
		pow(data_arr[i].z, 2));
	}	
}
