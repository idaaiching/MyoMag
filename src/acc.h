// acc.h 

#ifndef ACC_H_   
#define ACC_H_

typedef struct Signal // represents signal of accelerometer 
{
	double t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
} Signal;

int readCSV( const char *filepath, Signal *signal_arr, int idx_start, int idx_end );
int splitCSVLine( char *line, char *line_arr[], int n_col_csv );
void myomag( const char *filepath, double *magnitude_arr, int nlines, int nsplits );
double calculateMagnitude(const double x, const double y, const double z);
#endif // ACC_H_
