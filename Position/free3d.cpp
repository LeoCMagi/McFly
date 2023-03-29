#include "free3d.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

free3d::free3d (Imp X, Rot A){
  x_coord = X.x;
  y_coord = X.y;
  z_coord = X.z;
  angle = A;
}

void free3d::operator+= (real_t v){
  x_coord+=v*sin(angle.theta())*cos(angle.phi());
  y_coord+=v*sin(angle.theta())*sin(angle.phi());
  z_coord+=v*cos(angle.phi());
}

void free3d::operator+= (Imp v){
  Imp imp;
  imp = v.rotate(angle);
  x_coord+=imp.x;
  y_coord+=imp.y;
  z_coord+=imp.z;
}

void free3d::operator^ (Rot a){
  angle+= a;
}

real_t free3d::operator| (free3d Y){
  return (x_coord-Y.x_coord)*(x_coord-Y.x_coord)
       + (y_coord-Y.y_coord)*(y_coord-Y.y_coord)
       + (z_coord-Y.z_coord)*(z_coord-Y.z_coord);
}

Imp  free3d::operator-  (free3d Y   ){
  Imp out = {x_coord-Y.x_coord, y_coord-Y.y_coord, z_coord-Y.z_coord};
  out.rotate(Y.angle);
  // attention, pas gigasûr de ce résultat
  // faire des tests avant de valider...
  // je rotate peut-être à l'envers...
  return out;
}


Rot free3d::operator<< (free3d Y){
  return (Y-this[0]).direction()+angle;
}

// fonction to know how to scale in the square projection
real_t free3d::dil_sqr(){
  if (abs(x_coord)<0.5 && abs(y_coord)<0.5 && abs(z_coord)<0.5){return 1.;}
  real_t m;               m = abs(x_coord);
  if (m< abs(y_coord)){   m = abs(y_coord);}
  if (m< abs(z_coord)){return abs(z_coord);}
  if (m==abs(x_coord)){return abs(x_coord);}
                       return abs(y_coord);
}

// !!!! Think !!!!!!
real_t free3d::x (int proj){
  if (proj==0) {
    real_t d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    return x_coord/(this->dil_sqr())*d/2 + 0.5;
  }

  if (proj==1) return x_coord;

  if (proj==2 && x_coord>=0) return 0.5 + (1-exp(-x_coord))/2;
  if (proj==2)         return 0.5 + (exp(x_coord) -1)/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free3d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free3d::y (int proj){
  if (proj==0) {
    real_t d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    return y_coord/(this->dil_sqr())*d/2 + 0.5;
  }

  if (proj==1) return y_coord;

  if (proj==2 && y_coord>=0) return 0.5 + (1-exp(-y_coord))/2;
  if (proj==2)         return 0.5 + (exp(y_coord) -1)/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'y' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free3d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free3d::z (int proj){
  if (proj==0) {
    real_t d = 1. - 1./16 ;
    //≈0.9375 ie closse to 0.99 but with exact binary representation
    // made to ensure that a boid doesn't get too close to the edge 
    // because we don't want edge cases when going into pixels
    return z_coord/(this->dil_sqr())*d/2 + 0.5;
  }

  if (proj==1) return z_coord;

  if (proj==2 && z_coord>=0) return 0.5 + (1-exp(-z_coord))/2;
  if (proj==2)         return 0.5 + (exp(z_coord) -1)/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'y' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free3d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free3d::t (int proj){
  if (proj==0 || proj==1 || proj==2) return angle.theta();

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free3d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t free3d::p (int proj){
  if (proj==0 || proj==1 || proj==2) return angle.phi();

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to free3d.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
