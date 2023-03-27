#include "Vec.h"
#include <cmath>
#include <stdexcept>
#include <cassert>
using namespace std;


void Rot::sync_interval() { 
  p_phi=angle_mod2pi_11(p_phi); 
  real_t theta_ = angle_mod2pi_11(p_theta); // in order to put theta and phi between -pi and pi
  if (theta_ >= 0) 
    p_theta= theta_;
  else{
    p_theta=-theta_;
    p_phi = angle_mod2pi_11(M_PI+p_phi);/* theta has to be >0 thus whe have to apply the transformation
theta ->-theta and phi -> phi+pi since it's a transformation that doesn't change our object */
    }
}
  

Imp Imp::u_angle (Rot angles) {
	return {
	  .x = sin(angles.theta())*cos(angles.phi()),
	  .y = sin(angles.theta())*sin(angles.phi()),
	  .z = cos(angles.theta())
	};
}


real_t Imp::operator! () const {
  return sqrt(x*x+y*y+z*z);
}


Rot Imp::direction() const {
  if (!*this ==0) {
    return Rot(0,0);
  }
  else {
    return Rot(acos(z/(!*this)),atan2(y,x));
  }
}

Imp Imp::rotate (Rot angles2) const {
  Rot angles1 = (*this).direction();
  Rot anglesf = angles1+ angles2;
  real_t r = !*this;
  return r*u_angle(anglesf);
}

real_t rest (real_t x, real_t d){
  real_t q = x/d;
  int k;
  if (q>=0) k = int(q);
  if (q<0) k = int(q) - 1;
  return x - k*d;
}

int div (real_t x, real_t d){
  real_t q = x/d;
  int k;
  if (q>=0) k = int(q);
  if (q<0) k = int(q) + 1;
  return k;
}

real_t angle_mod2pi_11 (real_t theta) {
	while (theta > M_PI)
		theta -= 2*M_PI;
	while (theta < -M_PI)
		theta += 2*M_PI;
	return theta;
}

real_t angle_mod2pi_02 (real_t theta) {
	return theta - 2*M_PI* floor( theta/(2*M_PI) );
}


