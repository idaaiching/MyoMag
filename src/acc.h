// acc.h 

#ifndef ACC_H_   
#define ACC_H_

typedef struct DATA // represents data of accelerometer 
{
	int t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
} DATA;

int readCSV(const char *filepath, DATA *acc_data);
void calculateMagnitude(const DATA *acc_data, double *magnitude_arr, int number_of_entries);
int getLine(char *line, char *entry_arr[], int nentries);
//double calculateMagnitude(double x, double y, double z);

#endif // ACC_H_
