#ifndef _UTIL_H_
#define _UTIL_H_

#include <utility>
#include <limits>

using real_t = double; // peut être utile de de définir un type real_t pour faire des tests entre simple et double précision

/********************************************************************
 * Vecteur 2D. Simple structure (x,y) avec opérateurs surchargés
 * et quelques méthodes utiles. Ne pas utiliser pour représenter un
 * point dans un espace cartésien, il y a Point2 pour ça.
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
  void sync_interval();
};
inline Rot operator* (real_t k, const Rot& v) { return v*k; }


/********************************************************************
 * Vecteur 2D. Simple structure (x,y) avec opérateurs surchargés
 * et quelques méthodes utiles. Ne pas utiliser pour représenter un
 * point dans un espace carthésien, il y a Point2 pour ça.
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
	real_t operator| (Imp o)   const { return x*o.x + y*o.y+z*o.z ; }	// produit scalaire
	real_t norm2     ()         const { return x*x + y*y +z*z; }// norme au carré
	real_t operator! ()         const;  // norme
  Rot direction() const; // donne la direction (angle theta et phi du vecteur
  Imp  rotate     (Rot angles2) const; //it returns the vector rotated by the angles theta2,phi2 which are encoded in angles2
  static Imp u_angle (Rot angles);  // fonction statique de création d'un vecteur unité à partir d'un angle
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

/// Divers

/********************************************************************
 * Réslution du système linéaire
 * ⎡a  b⎤ ⎡x⎤   ⎡e⎤
 * ⎣c  d⎦ ⎣y⎦ = ⎣f⎦
 */
void mat22_sol (real_t a, real_t b, real_t c, real_t d, real_t e, real_t f, real_t& x, real_t& y);


#endif
