#include "disk.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

void disk::clean(){
  if (x_coord*x_coord + y_coord*y_coord > 1){
    real_t r = sqrt(x_coord*x_coord + y_coord*y_coord);
    real_t a;
    if (x_coord==0) {
      if (y_coord >0) a = M_PI/2;
      if (y_coord <0) a =-M_PI/2;}
    if (x_coord >0) a = atan(y_coord/x_coord);
    if (x_coord <0) a =M_PI+atan(y_coord/x_coord);
    r = 2-r;
    cout << "x:" << x_coord << " -> ";
    x_coord = r * cos(a);
    cout << x_coord << endl;
    y_coord = r * sin(a);
    t_angle = M_PI + 2*a - t_angle;
    t_angle = rest(t_angle+M_PI, 2*M_PI)-M_PI;
  }
}

disk::disk (Imp X, Rot A){
  /* the parameters "X" and "A" are temporary...
     Once the modules "Rot" and "Imp" will be coded
     there will be an update...*/
  x_coord = rest(X.x,1);
  y_coord = rest(X.y,1);
  t_angle = rest(A.phi()+M_PI, 2*M_PI)-M_PI;
  this->clean();
}

void disk::operator+= (real_t v){
  x_coord+=v*cos(t_angle);
  y_coord+=v*sin(t_angle);
  // x_coord //2 ∈ {0,1}
  //        0 => nombre paire de mirroirs selon l'axe y
  //        1 => nécéssite un mirroir selon y
  // idem mais inversion x,y
  // a // 2b     <=> (a - rest(a,2b))/2b
  // a//2b > 0.5 <=>  a - rest(a,2b) > b
  // hence :
  this->clean();
}

void disk::operator+= (Imp v){
  x_coord+=v.x*cos(t_angle) - v.x*sin(t_angle);
  y_coord+=v.x*sin(t_angle) + v.y*cos(t_angle);
  this->clean();
}

void disk::operator^ (Rot a){
  t_angle= rest(t_angle+a.phi()+M_PI, 2*M_PI)-M_PI;
}

real_t disk::operator| (disk Y){
  return (x_coord-Y.x_coord)*(x_coord-Y.x_coord)
       + (y_coord-Y.y_coord)*(y_coord-Y.y_coord);
}


Imp  disk::operator-  (disk Y   ){
  real_t x_glob = x_coord-Y.x_coord;
  real_t y_glob = y_coord-Y.y_coord;
  return {x_glob*cos(Y.t_angle)+y_glob*sin(Y.t_angle),
          -x_glob*sin(Y.t_angle)+y_glob*cos(Y.t_angle), 0.};
}

Rot disk::operator<< (disk Y){
  float x_d = Y.x_coord-x_coord;
  float y_d = Y.y_coord-y_coord;
  if (x_d==0.){
    if (y_d>0) return {M_PI/2, rest(-t_angle+3*M_PI/2, 2*M_PI)-M_PI};
    if (y_d<0) return {M_PI/2, rest(-t_angle+  M_PI/2, 2*M_PI)-M_PI};
  }
  real_t a = atan(y_d/x_d);
  if (x_d>0) return {M_PI/2, rest( a+M_PI-t_angle, 2*M_PI)-M_PI};
             return {M_PI/2, rest(-a     -t_angle, 2*M_PI)-M_PI};
}

real_t disk::x (int proj){
  if (proj==0) return x_coord/2+.5;
  if (proj==1){
    return sqrt(x_coord*x_coord + y_coord*y_coord);
  }

  if (proj==2) {
    real_t r = sqrt(x_coord*x_coord + y_coord*y_coord);
    real_t a;
    if (x_coord==0) a = M_PI;
    if (x_coord >0) a = atan(y_coord/x_coord);
    if (x_coord <0) a =M_PI-atan(y_coord/x_coord);
    return a;                    
  }

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to disk.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t disk::y (int proj){
  if (proj==0) return y_coord/2+.5;
  if (proj==1){
    real_t r = sqrt(x_coord*x_coord + y_coord*y_coord);
    real_t a;
    if (x_coord==0) a = M_PI;
    if (x_coord >0) a = atan(y_coord/x_coord);
    if (x_coord <0) a =M_PI-atan(y_coord/x_coord);
    return a;
  }
  if (proj==2){
    return sqrt(x_coord*x_coord + y_coord*y_coord);
  }
  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to disk.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t disk::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to disk.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t disk::p (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to disk.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t disk::t (int proj){
  if (proj==0 || proj==1 || proj==2) return M_PI/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to disk.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
