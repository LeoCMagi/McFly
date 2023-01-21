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

Imp Imp::u_angle (Rot angles) {
	return {
	  .x = sin(angles.theta)*cos(angles.phi),
	  .y = sin(angles.theta)*sin(angles.phi),
	  .z = cos(angles.theta)
	};
}


real_t Imp::operator! () const {
  return sqrt(x*x+y*y+z*z);
}

/*Imp Imp::rotate (real_t theta, real_t phi) const {
	real_t c = cos(theta), s = sin(theta);
	return { .x = c * x - s * y,
	         .y = s * x + c * y };
}*/

Rot Imp::direction() const {
  return {.theta =acos(z/(!*this)),.phi= atan2(y,x)};
}

Imp Imp::rotate (Rot angles2) const {
  Rot angles1 = (*this).direction();
  Rot anglesf = angles1+ angles2;
  real_t r = !*this;
  return r*u_angle(anglesf);
    /*return Imp {
    .x = r*sin(anglesf.theta)*cos(anglesf.phi),
    .y = r*sin(anglesf.theta)*sin(anglesf.phi),
    .z = r*cos(anglesf.theta)};*/
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


