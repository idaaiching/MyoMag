// acc.h 

#ifndef ACC_H_   
#define ACC_H_

struct accelerometer // represents data of accelerometer 
{
	int t; // time 
	float x, y, z; // spatial coordiantes of accelerometer
};

int readcsv(const char *filepath, struct accelerometer acc_data[]);
void magnitude(struct accelerometer acc_data[], double magnitude_arr[]);

#endif // ACC_H_