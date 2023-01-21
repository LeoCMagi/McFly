#ifndef _UTIL_H_
#define _UTIL_H_

#include <utility>
#include <limits>

using real_t = double; // peut être utile de de définir un type real_t pour faire des tests entre simple et double précision

// Nombre flottant infini
#define Inf std::numeric_limits<real_t>::infinity()
// Nombre flottant invalide (Not a Number)
#define NaN std::numeric_limits<real_t>::signaling_NaN()

/********************************************************************
 * Vecteur 2D. Simple structure (x,y) avec opérateurs surchargés
 * et quelques méthodes utiles. Ne pas utiliser pour représenter un
 * point dans un espace carthésien, il y a Point2 pour ça.
 */
struct Rot {
	real_t theta, phi;
	void operator+=  (Rot o)         { theta += o.theta; phi += o.phi; }
	void operator-=  (Rot o)         { theta -= o.theta; phi -= o.phi; }
	Rot operator+   (Rot o)   const { return Rot{ theta+o.theta, phi+o.phi }; }
	Rot operator-   ()         const { return Rot{ -theta, -phi }; }
	Rot operator-   (Rot o)   const { return Rot{ theta-o.theta, phi-o.phi }; }
	void operator*=  (real_t k)       { theta *= k; phi *= k; }
	void operator/=  (real_t k)       { theta /= k; phi /= k; }
	Rot operator*   (real_t k) const { return Rot{ k*theta, k*phi }; }
	Rot operator/   (real_t k) const { return Rot{ theta/k, phi/k }; }
};
inline Rot operator* (double k, const Rot& v) { return v*k; }


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
  Imp  rotate     (Rot angles2) const; //je ne sais pas adapter cette fonction dans le cas 3D
  static Imp u_angle (Rot angles);  // fonction statique de création d'un vecteur unité à partir d'un angle
};
inline Imp operator* (double k, const Imp& v) { return v*k; }


// réduit un angle à [-π,+π]
real_t angle_mod2pi_11 (real_t);
// réduit un angle à [0,2π]
real_t angle_mod2pi_02 (real_t);


/// Divers

/********************************************************************
 * Réslution du système linéaire
 * ⎡a  b⎤ ⎡x⎤   ⎡e⎤
 * ⎣c  d⎦ ⎣y⎦ = ⎣f⎦
 */
void mat22_sol (real_t a, real_t b, real_t c, real_t d, real_t e, real_t f, real_t& x, real_t& y);


#endif
