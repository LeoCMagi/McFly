#include "annulus.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;
real_t r_y=1.;
real_t L=1/r_y;

annulus::annulus (Imp X, Rot A){
  /* the parameters "X" and "A" are temporary...
     Once the modules "Rot" and "Imp" will be coded
     there will be an update...*/
  x_coord = fmod(X.x, 1.);
  y_coord = fmod(X.y, L );
  t_angle = fmod(A.phi()+M_PI, 2*M_PI)-M_PI;
}

void annulus::operator+= (real_t v){
  x_coord+=v*cos(t_angle);
  y_coord+=v*sin(t_angle);
  x_coord = fmod(x_coord, 1.);
  y_coord = fmod(y_coord, L );
}

void annulus::operator+= (Imp v){
  x_coord+=v.x*cos(t_angle) - v.y*sin(t_angle);
  y_coord+=v.x*sin(t_angle) + v.y*cos(t_angle);
  x_coord = fmod(x_coord, 1.);
  y_coord = fmod(y_coord, L );
}

void annulus::operator^ (Rot a){
  t_angle= fmod(t_angle+a.theta()+M_PI, 2*M_PI)-M_PI;
}

real_t annulus::operator| (annulus Y){
  float X,Y;
  X = fmod(x_coord-Y.x_coord+.5,1.)+.5;
  Y = fmod(y_coord-Y.y_coord+L/2., L)+L/2.;
  return X*X + Y*Y;
}

Imp  annulus::operator-  (annulus Y   ){
  float X,Y;
  X = fmod(x_coord-Y.x_coord+.5,1.)+.5;
  Y = fmod(y_coord-Y.y_coord+L/2., L)+L/2.;
  return {X, Y, 0.};
}

Rot annulus::operator<< (annulus Y){
  float x_d = fmod(x_coord-Y.x_coord+.5,1.)+.5;
  float y_d = fmod(y_coord-Y.y_coord+L/2., L)+L/2.;
  if (x_d==0.){
    if (y_d>0) return {M_PI/2, fmod(-t_angle+3*M_PI/2, 2*M_PI)-M_PI};
    if (y_d<0) return {M_PI/2, fmod(-t_angle+  M_PI/2, 2*M_PI)-M_PI};
  }
  real_t a = atan(y_d/x_d);
  if (x_d>0) return {M_PI/2, fmod( a+M_PI-t_angle, 2*M_PI)-M_PI};
             return {M_PI/2, fmod(-a     -t_angle, 2*M_PI)-M_PI};
}



real_t annulus::x (int proj){
  if (proj==0 || proj==2) return x_coord;

  if (proj==1) {
    // X = 1/r_y;
    // eps = (X-1)/2
    // x' = x/r_y
    // if x' < eps return 0
    // if > 1+eps  return 0
    //             return x'
    // x'>1+eps <=> x_coord/r_y > 1 + (X-1)/2
    //          <=> x_coord/r_y > 1 + (1/r_y-1)/2
    //          <=>2*x_coord/r_y> 2 + 1/r_y -1
    //          <=> 2 * x_coord > r_y + 1 (-1 sinon)
    // ATTENTION JE CROIS QUE C FAUX, tester!!!!
    float eps = (1/r_y - 1) / 2;
    if (x_coord/r_y < eps)     return 0.;
    if (x_coord/r_y > 1 + eps) return 1.;
    /*                     */  return (x_coord- (1-r_y)/2)/r_y;
  }

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to annulus.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t annulus::y (int proj){
  if (proj==0) return y_coord    ;
  if (proj==1 || proj==2) return y_coord/r_y;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to annulus.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t annulus::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to annulus.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t annulus::p (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to annulus.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t annulus::t (int proj){
  if (proj==0 || proj==1 || proj==2) return M_PI/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to annulus.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
