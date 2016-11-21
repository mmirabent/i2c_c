#ifndef MMSW_EULER_H
#define MMSW_EULER_H
/* Euler.h */

struct Euler
{
	double phi;
	double theta;
	double psi;
};

Euler eulercomp(double ax, double ay, double az,
				double mx, double my, double mz);

#endif
