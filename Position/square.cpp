#include "position.h"
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
I'll just leave it like this, for now
But which to find a solution.
*/


square::square (float X[3], float A[2]){
  /* the parameters "X" and "A" are temporary...
     Once the modules "vec2" and "vec3" will be coded
     there will be an update...*/
  x_coord = X[0];
  y_coord = X[1];
  t_angle = fmod(A[0]+M_PI, 2*M_PI)-M_PI;
  if (y_coord - fmod(y_coord,2*r_y) > r_y) t_angle = -t_angle;
  if (x_coord - fmod(x_coord,2.) > 1)      t_angle = M_PI - t_angle;
  x_coord = fmod(x_coord, 1.);
  y_coord = fmod(y_coord,r_y);
}

void square::move (float v){
  x_coord+=v*cos(t_angle);
  y_coord+=v*sin(t_angle);
  // x_coord //2 ∈ {0,1}
  //        0 => nombre paire de mirroirs selon l'axe y
  //        1 => nécéssite un mirroir selon y
  // idem mais inversion x,y
  // a // 2b     <=> (a - fmod(a,2b))/2b
  // a//2b > 0.5 <=>  a - fmod(a,2b) > b
  // hence :
  if (y_coord - fmod(y_coord,2*r_y) > r_y) t_angle = -t_angle;
  if (x_coord - fmod(x_coord,2.) > 1)      t_angle = M_PI - t_angle;
  x_coord = fmod(x_coord, 1.);
  y_coord = fmod(y_coord,r_y);
}

void square::operator+= (float v[3]){
  x_coord+=v[0]*cos(t_angle) - v[1]*sin(t_angle);
  y_coord+=v[0]*sin(t_angle) + v[1]*cos(t_angle);
  if (y_coord - fmod(y_coord,2*r_y) > r_y) t_angle = -t_angle;
  if (x_coord - fmod(x_coord,2.) > 1)      t_angle = M_PI - t_angle;
}

void square::turn (float a[2]){
  t_angle= fmod(t_angle+a[0]+M_PI, 2*M_PI)-M_PI;
}

float square::dist (square Y){
  return sqrt( (x_coord-Y.x_coord)*(x_coord-Y.x_coord)
             + (y_coord-Y.y_coord)*(y_coord-Y.y_coord) );
}

bool square::order (int axis, square Y){
  if (axis==1) return x_coord<Y.x_coord;
  if (axis==2) return y_coord<Y.x_coord;
  // case of an unexisting axis
  cout << endl << endl
       << "You requested the 'order' method on axis "
       << axis << endl << "There is no such axis" << endl;
  throw std::invalid_argument( "Unexisting axis" );
}

float square::x (int proj){
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

float square::y (int proj){
  if (proj==0) return y_coord    ;
  if (proj==1 || proj==2) return y_coord/r_y;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'x' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

float square::z (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'z' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

float square::t (int proj){
  if (proj==0 || proj==1 || proj==2) return t_angle;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 't' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}

float square::p (int proj){
  if (proj==0 || proj==1 || proj==2) return 0.;

  // case of an unexisting projection
  cout << endl << endl
       << "You requested the 'p' method with projection "
       << proj << endl << "There is no such projection" 
       << endl << "Refer to square.h 's documentation"<< endl;
  throw std::invalid_argument( "Unexisting projection" );
}
