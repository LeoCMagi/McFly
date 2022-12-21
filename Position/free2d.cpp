#include "position.h"
#include "free2d.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

free2d::free2d (float X[3], float A[2]){
  /* the parameters "X" and "A" are temporary...
     Once the modules "vec2" and "vec3" will be coded
     there will be un update...*/
  x_coord = X[0];
  y_coord = X[1];
  t_angle = fmod(A[0]+M_PI, 2*M_PI)-M_PI;
}

void free2d::move (float v){
  x_coord+=v*cos(t_angle) - v*sin(t_angle);
  y_coord+=v*sin(t_angle) + v*cos(t_angle);
}

void free2d::operator+= (float v[3]){
  x_coord+=v[0]*cos(t_angle) - v[1]*sin(t_angle);
  y_coord+=v[0]*sin(t_angle) + v[1]*cos(t_angle);
}

void free2d::turn (float a[2]){
  t_angle= fmod(t_angle+a[0]+M_PI, 2*M_PI)-M_PI;
}

float free2d::dist (free2d Y){
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

float free2d::x (int proj){
  if (proj==0) {
    float d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    if (abs(x_coord)<0.5 && abs(y_coord)<0.5) return d*x_coord+0.5;
    if (y_coord==0.) {
      if (abs(x_coord)<.5) return 0.5 + d*x_coord;
      if (   x_coord>0   ) return 0.5 + d/2;
      if (   x_coord<0   ) return 0.5 - d/2;}
    float X = x_coord/(2*abs(y_coord));
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

float free2d::y (int proj){
  if (proj==0) {
    float d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    if (abs(x_coord)<0.5 && abs(y_coord)<0.5) return d*y_coord+0.5;
    if (x_coord==0.) {
      if (abs(y_coord)<.5) return 0.5 + d*y_coord;
      if (   y_coord>0   ) return 0.5 + d/2;
      if (   y_coord<0   ) return 0.5 - d/2;}
    float Y = y_coord/(2*abs(x_coord));
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

float free2d::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

float free2d::t (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

float free2d::p (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free2d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
