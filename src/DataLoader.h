#ifndef DATALOADER_H
#define DATALOADER_H


typedef struct Signal{
	double t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
} Signal;

int readCSV( const char *filepath, Signal *signal_arr, int idx_start, int idx_end );
int splitCSVLine( char *line, char *line_arr[], int n_col_csv );

#endif