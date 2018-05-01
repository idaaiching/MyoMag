// AccelerationMagnitude.h
#ifndef ACCMAG_H_
#define ACCMAG_H_

#include <math.h>

double computeMagnitude(const double x, const double y, const double z)
{
	return sqrt(x*x + y*y + z*z);
}


#endif
