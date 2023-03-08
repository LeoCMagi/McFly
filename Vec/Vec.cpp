#include "Vec.h"
#include <cmath>
#include <stdexcept>
#include <cassert>
using namespace std;



// ⎡a  b⎤ ⎡x⎤   ⎡e⎤
// ⎣c  d⎦ ⎣y⎦ = ⎣f⎦
//
void mat22_sol (real_t a, real_t b, real_t c, real_t d, real_t e, real_t f, real_t& x, real_t& y) {
	real_t det = a * d - b * c;
	x = (e * d - b * f) / det;
	y = (a * f - e * c) / det;
}

void Rot::sync_interval() {
  /*p_phi=fmod(p_phi+M_PI,2*M_PI)-M_PI;
  real_t theta_ = fmod(p_theta+M_PI,2*M_PI)-M_PI;
  if (theta_ >= 0) 
    p_theta= theta_;
  else{
    p_theta=-theta_;
    p_phi = fmod(-p_phi, 2*M_PI)-M_PI;
    }*/
  p_phi=angle_mod2pi_11(p_phi);
  real_t theta_ = angle_mod2pi_11(p_theta);
  if (theta_ >= 0) 
    p_theta= theta_;
  else{
    p_theta=-theta_;
    p_phi = angle_mod2pi_11(M_PI+p_phi);
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


