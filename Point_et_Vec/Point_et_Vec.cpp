#include "Point_et_Vec.h"
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

Imp Imp::u_angle (real_t theta, real_t phi) {
	return {
	  .x = sin(theta)*cos(phi),
	  .y = sin(theta)*sin(phi),
	  .z = cos(theta)
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
std::pair<real_t,real_t> Imp::direction() const {
  return {acos(z/(!*this)), atan2(y,x)};
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


