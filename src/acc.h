// acc.h 

#ifndef ACC_H_   
#define ACC_H_

typedef struct DATA // represents data of accelerometer 
{
	int t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
} DATA;

int readCSV(const char *filepath, DATA *data_arr, int idx_checkpoint );
void calculateMagnitude(const DATA *data_arr, double *magnitude_arr, int n_lines_csv, int idx_checkpoint );
int getLine(char *line, char *line_arr[], int n_col_csv);
//double calculateMagnitude(double x, double y, double z);

#endif // ACC_H_
