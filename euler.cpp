#include <cmath>
#include "euler.h"

using namespace std;

Euler eulercomp(double ax, double ay, double az,
				double mx, double my, double mz){
	Euler e;

  double norm_a = sqrt(ax*ax + ay*ay + az*az);
  double norm_m = sqrt(mx*mx + my*my + mz*mz);
  ax /= norm_a;
  ay /= norm_a;
  az /= -norm_a;

  mx /= norm_m;
  my /= norm_m;
  mz /= -norm_m;

  /*
	e.phi   = atan2(-ay, hypot(az,ax));
	e.theta = atan2(ax, az);
	e.psi   = atan2(-my * cos(e.phi) + mz * sin(e.phi),
					mx * cos(e.theta) + my * sin(e.theta) * sin(e.phi)
					+ mz * sin(e.theta) * cos(e.phi));
  */
	e.phi   = atan2(ay, az);
	e.theta = atan2(-ax, ay * sin(e.phi) + az * cos(e.phi));
	e.psi   = atan2(-my * cos(e.phi) + mz * sin(e.phi),
					mx * cos(e.theta) + my * sin(e.theta) * sin(e.phi)
					+ mz * sin(e.theta) * cos(e.phi));

  e.phi *= -1;
  e.theta *= -1;

	return e;
}
