// AccelerationMagnitude.h 

#ifndef ACC_H_   
#define ACC_H_

void calculateMagnitudeFromCSV( const char *filePath, double *magnitude_arr, int nlines, int nsplits );
double calculateMagnitude(const double x, const double y, const double z);
#endif // ACC_H_
