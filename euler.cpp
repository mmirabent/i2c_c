#include <cmath>
#include "euler.h"

using namespace std;

Euler eulercomp(double ax, double ay, double az,
				double mx, double my, double mz){
	Euler e;
	e.phi   = -atan2(-ay, hypot(az,ax));
	//e.phi   = atan2(-ay, hypot(az,ax));
	e.theta = -atan2(-ax, -az);
	//e.theta = atan2(-ax, az);
	e.psi   = atan2(-my * cos(e.phi) + mz * sin(e.phi),
					mx * cos(e.theta) + my * pow(sin(e.theta),2)
					+ mz * sin(e.theta) * cos(e.phi));
	return e;
}
