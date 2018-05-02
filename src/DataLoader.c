#include "DataLoader.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXLINE 100 // storage for one line
#define NCOLUMNS 4

// returns number of last line read 
int readCSV( const char *filepath, Signal *signal_arr, int fromLine, int toLine )	{
    FILE *filePointer = NULL;
    filePointer = fopen(filepath, "r");
    if(filePointer == NULL){
    	printf("Error: Failed to open csv file!");
    	return 0;
    }
	char line[MAXLINE];
	char *line_arr[NCOLUMNS];
	int nElementsInLine;
	int lineIndex = 0;
	while( fgets(line, sizeof(line), filePointer) != NULL && lineIndex <= toLine){
		if( lineIndex < fromLine) {
			lineIndex++;
			continue;			
		}
		nElementsInLine = splitCSVLine(line, line_arr, NCOLUMNS);
		if (nElementsInLine > NCOLUMNS){
			printf("Error: Line %d\n has only %d\n entries for t, x, y, z.  Expected %d\n!", 
				lineIndex, nElementsInLine, NCOLUMNS);
			break;			
		}		
		signal_arr[lineIndex - fromLine].t = strtod( line_arr[0], NULL );
		signal_arr[lineIndex - fromLine].x = strtod( line_arr[1], NULL );
		signal_arr[lineIndex - fromLine].y = strtod( line_arr[2], NULL );
		signal_arr[lineIndex - fromLine].z = strtod( line_arr[3], NULL );
		lineIndex++;
	};
	fclose(filePointer);
	return lineIndex;
}

// loops through one line and saves each column entry in the line_arr
int splitCSVLine( char *line, char *line_arr[], int nColumns){
	char *p;
	int nElementsInLine = 0;
	char prevc = ',';   /* force recognizing first field */
	char *dp = NULL;

	for ( p = line; *p != '\0'; prevc = *p, p++){
		if ( prevc == ',' ){
			/* start new field */
			if ( dp != NULL){
				*dp = '\0';  /*terminate prev*/
			}
			if ( nElementsInLine >= nColumns){
				return nElementsInLine;
			}
			line_arr[nElementsInLine++] = p;
			dp = p;
		}
		if ( *p != ',' )
			*dp++ = *p;
	}
	if ( dp != NULL ){
		*dp = '\0';
	}
	if ( nElementsInLine < nColumns){
		line_arr[nElementsInLine] = NULL;
	}
	return nElementsInLine;
}
