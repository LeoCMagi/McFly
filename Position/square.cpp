#include "square.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

/*|||||||||| defining r_y ||||||||||||||*/
float r_y = 1.;
/*||||||||||||||||||||||||||||||||||||||*/

/* BUG I DON'T KNOW HOW TO FIX
I would like to implement the folowing foolproof precedure:
r_y = abs(r_y);
if (r_y==0) r_y = 1.   ;
if (r_y>1)  r_y = 1/r_y;
But sadly, I cannot do so outside a "main" function
And I cannot define a main function without conflicting 
with the actual program...
I'll just lcdeave it like this, for now
But which to find a solution.
*/

void square::clean(){
  real_t x_0 = rest(x_coord,1);
  real_t y_0 = rest(y_coord,1*r_y);
  int k_x = div (x_coord, 1.);
  int k_y = div (y_coord, r_y);
  if (k_x%2==1){
    x_coord = 1 - x_0;
    t_angle = M_PI -t_angle;
  }else{
    x_coord = x_0;
  }
  if (k_y%2==1){
    y_coord = r_y - y_0;
    t_angle = - t_angle; 
  }else{
    y_coord = y_0;
  }
}

square::square (Imp X, Rot A){
  /* the parameters "X" and "A" are temporary...
     Once the modules "Rot" and "Imp" will be coded
     there will be an update...*/
  x_coord = X.x;
  y_coord = X.y;
  t_angle = rest(A.phi()+M_PI, 2*M_PI)-M_PI;
  this->clean();
}

void square::operator+= (real_t v){
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

void square::operator+= (Imp v){
  x_coord+=v.x*cos(t_angle) - v.x*sin(t_angle);
  y_coord+=v.x*sin(t_angle) + v.y*cos(t_angle);
  this->clean();
}

void square::operator^ (Rot a){
  t_angle= rest(t_angle+a.phi()+M_PI, 2*M_PI)-M_PI;
}

real_t square::operator| (square Y){
  return (x_coord-Y.x_coord)*(x_coord-Y.x_coord)
       + (y_coord-Y.y_coord)*(y_coord-Y.y_coord);
}


Imp  square::operator-  (square Y   ){
  real_t x_glob = x_coord-Y.x_coord;
  real_t y_glob = y_coord-Y.y_coord;
  return {x_glob*cos(Y.t_angle)+y_glob*sin(Y.t_angle),
          -x_glob*sin(Y.t_angle)+y_glob*cos(Y.t_angle), 0.};
}

Rot square::operator<< (square Y){
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

real_t square::x (int proj){
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
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t square::y (int proj){
  if (proj==0) return y_coord    ;
  if (proj==1 || proj==2) return y_coord/r_y;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t square::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t square::p (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

real_t square::t (int proj){
  if (proj==0 || proj==1 || proj==2) return M_PI/2;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
