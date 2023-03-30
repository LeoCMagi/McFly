#include "annulus.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;
real_t d_y=1.;
real_t L=1/d_y;

annulus::annulus (Imp X, Rot A){
  /* the parameters "X" and "A" are temporary...
     Once the modules "Rot" and "Imp" will be coded
     there will be an update...*/
  x_coord = rest(X.x, 1.);
  y_coord = rest(X.y, L );
  t_angle = rest(A.phi()+M_PI, 2*M_PI)-M_PI;
}

void annulus::operator+= (real_t v){
  x_coord+=v*cos(t_angle);
  y_coord+=v*sin(t_angle);
  x_coord = rest(x_coord, 1.);
  y_coord = rest(y_coord, L );
}

void annulus::operator+= (Imp v){
  x_coord+=v.x*cos(t_angle) - v.y*sin(t_angle);
  y_coord+=v.x*sin(t_angle) + v.y*cos(t_angle);
  x_coord = rest(x_coord, 1.);
  y_coord = rest(y_coord, L );
}

void annulus::operator^ (Rot a){
  t_angle= rest(t_angle+a.phi()+M_PI, 2*M_PI)-M_PI;
}

real_t annulus::operator| (annulus Y){
  float X_f,Y_f;
  X_f = rest(x_coord-Y.x_coord+.5,1.)-.5;
  Y_f = rest(y_coord-Y.y_coord+L/2., L)-L/2.;
  return X_f*X_f + Y_f*Y_f;
}

Imp  annulus::operator-  (annulus Y   ){
  real_t x_glob = rest(x_coord-Y.x_coord+.5,1.)-.5;
  real_t y_glob = rest(y_coord-Y.y_coord+L/2., L)-L/2.;
  return {x_glob*cos(Y.t_angle)+y_glob*sin(Y.t_angle),
          -x_glob*sin(Y.t_angle)+y_glob*cos(Y.t_angle), 0.};
}

Rot annulus::operator<< (annulus Y){
  float x_d = rest(x_coord-Y.x_coord+.5,1.)-.5;
  float y_d = rest(y_coord-Y.y_coord+L/2., L)-L/2.;
  if (x_d==0.){
    if (y_d>0) return {M_PI/2, rest(-t_angle+3*M_PI/2, 2*M_PI)-M_PI};
    if (y_d<0) return {M_PI/2, rest(-t_angle+  M_PI/2, 2*M_PI)-M_PI};
  }
  real_t a = atan(y_d/x_d);
  if (x_d>0) return {M_PI/2, rest( a+M_PI-t_angle, 2*M_PI)-M_PI};
             return {M_PI/2, rest(-a     -t_angle, 2*M_PI)-M_PI};
}



real_t annulus::x (int proj){
  if (proj==0 || proj==2) return x_coord;

  if (proj==1) {
    // X = 1/d_y;
    // eps = (X-1)/2
    // x' = x/d_y
    // if x' < eps return 0
    // if > 1+eps  return 0
    //             return x'
    // x'>1+eps <=> x_coord/d_y > 1 + (X-1)/2
    //          <=> x_coord/d_y > 1 + (1/d_y-1)/2
    //          <=>2*x_coord/d_y> 2 + 1/d_y -1
    //          <=> 2 * x_coord > d_y + 1 (-1 sinon)
    // ATTENTION JE CROIS QUE C FAUX, tester!!!!
    float eps = (1/d_y - 1) / 2;
    if (x_coord/d_y < eps)     return 0.;
    if (x_coord/d_y > 1 + eps) return 1.;
    /*                     */  return (x_coord- (1-d_y)/2)/d_y;
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
  if (proj==1 || proj==2) return y_coord/d_y;

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
