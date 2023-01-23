#include "free2d.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

free2d::free2d (Imp X, Rot A){
  /* the parameters "X" and "A" are temporary...
     Once the modules "Rot" and "Imp" will be coded
     there will be an update...*/
  x_coord = X.x;
  y_coord = X.y;
  t_angle = fmod(A.theta+M_PI, 2*M_PI)-M_PI;
}

void free2d::operator+= (real_t v){
  x_coord+=v*cos(t_angle);
  y_coord+=v*sin(t_angle);
}

void free2d::operator+= (Imp v){
  x_coord+=v.x*cos(t_angle) - v.y*sin(t_angle);
  y_coord+=v.x*sin(t_angle) + v.y*cos(t_angle);
}

void free2d::operator^ (Rot a){
  t_angle= fmod(t_angle+a.theta+M_PI, 2*M_PI)-M_PI;
}

real_t free2d::operator| (free2d Y){
  return sqrt( (x_coord-Y.x_coord)*(x_coord-Y.x_coord)
             + (y_coord-Y.y_coord)*(y_coord-Y.y_coord) );
}

bool free2d::order (int axis, free2d Y){
  if (axis==1) return x_coord<Y.x_coord;
  if (axis==2) return y_coord<Y.x_coord;
  // case of an unexisting axis
  cout << endl << endl
       << "You requested the 'order' method on axis "
       << axis << endl << "There is no such axis" << endl;
  throw std::invalid_argument( "Unexisting axis" );
}

Imp  free2d::operator-  (free2d Y   ){
  return {x_coord-Y.x_coord, y_coord-Y.y_coord, 0.};
}

Rot free2d::operator<< (free2d Y){
  float x_d = Y.x_coord-x_coord;
  float y_d = Y.y_coord-y_coord;
  if (x_d==0.){
    if (y_d>0) return {fmod(-t_angle+3*M_PI/2, 2*M_PI)-M_PI,0.};
    if (y_d<0) return {fmod(-t_angle+  M_PI/2, 2*M_PI)-M_PI,0.};
  }
  real_t a = atan(y_d/x_d);
  if (x_d>0) return {fmod( a+M_PI-t_angle, 2*M_PI)-M_PI,0};
             return {fmod(-a     -t_angle, 2*M_PI)-M_PI,0};
}




real_t free2d::x (int proj){
  if (proj==0) {
    real_t d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    if (abs(x_coord)<0.5 && abs(y_coord)<0.5) return d*x_coord+0.5;
    if (y_coord==0.) {
      if (abs(x_coord)<.5) return 0.5 + d*x_coord;
      if (   x_coord>0   ) return 0.5 + d/2;
      if (   x_coord<0   ) return 0.5 - d/2;}
    real_t X = x_coord/(2*abs(y_coord));
    if (abs(X)<0.5) return d*X + 0.5;
    return d* X/abs(X)/2 + 0.5;
  }

  if (proj==1) return x_coord;

  if (proj==2 && x_coord>=0) return 0.5 + (1-exp(-x_coord))/2;
  if (proj==2)         return 0.5 + (exp(x_coord) -1)/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free2d::y (int proj){
  if (proj==0) {
    real_t d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    if (abs(x_coord)<0.5 && abs(y_coord)<0.5) return d*y_coord+0.5;
    if (x_coord==0.) {
      if (abs(y_coord)<.5) return 0.5 + d*y_coord;
      if (   y_coord>0   ) return 0.5 + d/2;
      if (   y_coord<0   ) return 0.5 - d/2;}
    real_t Y = y_coord/(2*abs(x_coord));
    if (abs(Y)<0.5) return d*Y + 0.5;
    return d* Y/abs(Y)/2 + 0.5;
  }

  if (proj==1) return y_coord;

  if (proj==2 && y_coord>=0) return 0.5 + (1-exp(-y_coord))/2;
  if (proj==2)         return 0.5 + (exp(y_coord) -1)/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'y' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free2d::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free2d::t (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free2d::p (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
