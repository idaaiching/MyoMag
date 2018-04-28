// acc.h 

#ifndef ACC_H_   
#define ACC_H_

struct accelerometer // represents data of accelerometer 
{
	int t; // time 
	double x, y, z; // spatial coordiantes of accelerometer
};

int readCSV(const char *filepath, struct accelerometer *acc_data);
void calculateMagnitude(const struct accelerometer *acc_data, double *magnitude_arr, int number_of_entries);
//double calculateMagnitude(double x, double y, double z);

#endif // ACC_H_
