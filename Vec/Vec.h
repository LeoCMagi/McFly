#ifndef _UTIL_H_
#define _UTIL_H_

using real_t = double;
/********************************************************************
 * Rot a class with the private arguments (p_theta, p_phi) in order to
 * make sure that they are include respectively in [0, pi] and [-pi, pi].
 * This class will permit to describe the direction of a boid.
 * You have to use the constructor of this class in order to make sure
 * to create and object with theta and phi in the right intervals.
 */
class Rot {
public :
  void theta(real_t valeur) {p_theta=valeur;sync_interval();}
  void phi(real_t valeur) {p_phi=valeur; sync_interval();}
  real_t theta() const {return p_theta;}
  real_t phi () const {return p_phi;}
  Rot(const Rot & autre) = default;
  Rot(real_t theta_, real_t phi_) {p_theta= theta_; p_phi=phi_; sync_interval();}
  Rot() {p_theta=0;p_phi=0;}
  void operator+=  (Rot o)         { theta(p_theta + o.theta()); phi(p_phi + o.phi()); }
  void operator-=  (Rot o)         { theta(p_theta - o.theta()); phi(p_phi - o.phi()); }
  Rot operator+   (Rot o)   const { return Rot(p_theta+o.p_theta, p_phi+o.p_phi); }
  Rot operator-   ()         const { return Rot( -p_theta, -p_phi ); }
  Rot operator-   (Rot o)   const { return Rot( p_theta-o.p_theta, p_phi-o.p_phi ); }
  void operator*=  (real_t k)       { theta(p_theta * k); phi(p_phi * k); }
  void operator/=  (real_t k)       { theta(p_theta/k); phi(p_phi/k); }
  Rot operator*   (real_t k) const { return Rot( k*p_theta, k*p_phi ); }
  Rot operator/   (real_t k) const { return Rot( p_theta/k, p_phi/k); }
private :
  real_t p_theta, p_phi;
  void sync_interval(); // a function which puts p_theta and p_phi in the right intervals.
};
inline Rot operator* (real_t k, const Rot& v) { return v*k; }


/********************************************************************
 * Imp. Simple structure (x,y,z). It represents a 3D vector in cartesian
 * coordinates.
 */
struct Imp {
  real_t x, y,z;
  void operator+=  (Imp o)         { x += o.x; y += o.y; z+=o.z; }
  void operator-=  (Imp o)         { x -= o.x; y -= o.y; z-=o.z; }
  Imp operator+   (Imp o)   const { return Imp{ x+o.x, y+o.y, z+o.z }; }
  Imp operator-   ()         const { return Imp{ -x, -y, -z }; }
  Imp operator-   (Imp o)   const { return Imp{ x-o.x, y-o.y, z-o.z }; }
  void operator*=  (real_t k)       { x *= k; y *= k; z*=k; }
  void operator/=  (real_t k)       { x /= k; y /= k; z/=k; }
  Imp operator*   (real_t k) const { return Imp{ k*x, k*y, k*z }; }
  Imp operator/   (real_t k) const { return Imp{ x/k, y/k, z/k }; }
	real_t operator| (Imp o)   const { return x*o.x + y*o.y+z*o.z ; }	// scalar product
	real_t norm2     ()         const { return x*x + y*y +z*z; }// norm² 
	real_t operator! ()         const;  // norm
  Rot direction() const; // gives the angles (theta, phi) between the vector and the axis x,y and z.
  Imp  rotate     (Rot angles2) const; //it returns the vector rotated by the angles theta2,phi2 which are encoded in angles2
  static Imp u_angle (Rot angles);  // function which creates the unitary with direction angles2
};
inline Imp operator* (double k, const Imp& v) { return v*k; }


// réduit un angle à [-π,+π]
real_t angle_mod2pi_11 (real_t);
// réduit un angle à [0,2π]
real_t angle_mod2pi_02 (real_t);
//réduit un angle à [0, pi]
real_t angle_modpi_01 (real_t);

real_t rest (real_t x, real_t d);
int    div (real_t x, real_t d);

#endif
