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
struct Vec2 {
	real_t x, y;
	void operator+=  (Vec2 o)         { x += o.x; y += o.y; }
	void operator-=  (Vec2 o)         { x -= o.x; y -= o.y; }
	Vec2 operator+   (Vec2 o)   const { return Vec2{ x+o.x, y+o.y }; }
	Vec2 operator-   ()         const { return Vec2{ -x, -y }; }
	Vec2 operator-   (Vec2 o)   const { return Vec2{ x-o.x, y-o.y }; }
	void operator*=  (real_t k)       { x *= k; y *= k; }
	void operator/=  (real_t k)       { x /= k; y /= k; }
	Vec2 operator*   (real_t k) const { return Vec2{ k*x, k*y }; }
	Vec2 operator/   (real_t k) const { return Vec2{ x/k, y/k }; }
	real_t operator| (Vec2 o)   const { return x*o.x + y*o.y ; }	// produit scalaire
	real_t norm2     ()         const { return x*x + y*y; }			// norme au carré
	real_t operator! ()         const;								// norme
	Vec2  rotate     (real_t theta) const;							// rotation d'un angle `theta`
	static Vec2 u_angle (real_t theta);  // fonction statique de création d'un vecteur unité à partir d'un angle
  real_t direction() const; //renvoie la direction du vecteur (angle theta)
};
inline Vec2 operator* (double k, const Vec2& v) { return v*k; }


/********************************************************************
 * Point dans un espace 2D, en coordonnées carthésiennes.
 * Simple structure (x,y) avec opérateurs surchargés : la soustraction
 * de deux points est un vecteur, l'addition d'un vecteur à un point
 * donne un point. 
 */
struct Point2 {
	real_t x, y;
	Vec2 operator- (Point2 o) const { return Vec2{ x-o.x, y-o.y }; }  // vecteur entre deux points
	Point2 operator+ (Vec2 v) const { return Point2{ x+v.x, y+v.y }; }  // translation du point par un vecteur
};

/********************************************************************
 * Vecteur 2D. Simple structure (x,y) avec opérateurs surchargés
 * et quelques méthodes utiles. Ne pas utiliser pour représenter un
 * point dans un espace carthésien, il y a Point2 pour ça.
 */
struct Vec3 {
  real_t x, y,z;
  void operator+=  (Vec3 o)         { x += o.x; y += o.y; z+=o.z; }
  void operator-=  (Vec3 o)         { x -= o.x; y -= o.y; z-=o.z; }
  Vec3 operator+   (Vec3 o)   const { return Vec3{ x+o.x, y+o.y, z+o.z }; }
  Vec3 operator-   ()         const { return Vec3{ -x, -y, -z }; }
  Vec3 operator-   (Vec3 o)   const { return Vec3{ x-o.x, y-o.y, z-o.z }; }
  void operator*=  (real_t k)       { x *= k; y *= k; z*=k; }
  void operator/=  (real_t k)       { x /= k; y /= k; z/=k; }
  Vec3 operator*   (real_t k) const { return Vec3{ k*x, k*y, k*z }; }
  Vec3 operator/   (real_t k) const { return Vec3{ x/k, y/k, z/k }; }
	real_t operator| (Vec3 o)   const { return x*o.x + y*o.y+z*o.z ; }	// produit scalaire
	real_t norm2     ()         const { return x*x + y*y +z*z; }// norme au carré
	real_t operator! ()         const;  // norme
  //Vec3  rotate     (real_t theta, real_t phi) const; je ne sais pas adapter cette fonction dans le cas 3D
  static Vec3 u_angle (real_t theta, real_t phi);  // fonction statique de création d'un vecteur unité à partir d'un angle
  std::pair<real_t,real_t> direction() const; // donne la direction (angle theta et phi du vecteur
};
inline Vec3 operator* (double k, const Vec3& v) { return v*k; }

struct Point3 {
  real_t x, y, z;
  Vec3 operator- (Point3 o) const { return Vec3{ x-o.x, y-o.y, z-o.z }; }  // vecteur entre deux points
  Point3 operator+ (Vec3 v) const { return Point3{x+v.x, y+v.y, z+v.z }; }  // translation du point par un vecteur
};


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
