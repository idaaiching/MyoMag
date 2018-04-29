// acc.h 

#ifndef ACC_H_   
#define ACC_H_

typedef struct DATA // represents data of accelerometer 
{
	int t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
} DATA;

int readCSV( const char *filepath, DATA *data_arr, int idx_start, int idx_end );
int getLine(char *line, char *line_arr[], int n_col_csv);

void calculateMagnitude(const DATA *data_arr, double *magnitude_arr, int idx_start, int idx_end );
//double calculateMagnitude(double x, double y, double z);

#endif // ACC_H_
