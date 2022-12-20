#include "position.h"
#include "free2d.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

using namespace std;

free2d::free2d (float X[5]){
  /* There's the question of how to store our data...
     I go for [angle1, x, y, z, angle2]
     that way, 1,2,3 refer to position (like in GR)
     and [0:3] refers to the 2D case (and we can just ignore the reste)
     of course, it can be changed once we disscussed it
     (if we alredy have, it means I forgot to delete this comment,
      so please, dear reader, do it youself... Thks) */
  x = X[1];
  y = X[2];
  t = X[0];
}

/*float[5] free2d::coord(int proj){
  float X[5];
  X[0]=t;
  X[1]=x;
  X[2]=y;*/
  /* Do we need to ensure that the unused data is 0 ?
     if so:
  X[3]=0;
  X[4]=0;
     */ /*
  return X;
  }*/

void free2d::move (float v[5]){
  x+=v[0]*cos(t) - v[1]*sin(t);
  y+=v[0]*sin(t) + v[1]*cos(t);
}

void free2d::turn (float a[2]){
  t+= a[0];
}

float free2d::dist (free2d Y){
  return sqrt( (x-Y.x)*(x-Y.x) + (y-Y.y)*(y-Y.y) );
}

bool free2d::order (int axis, free2d Y){
  if (axis==1) return x<Y.x;
  if (axis==2) return y<Y.x;
  // case of an unexisting axis
  cout << endl << endl
       << "You requested the 'order' method on axis "
       << axis << endl << "There is no such axis" << endl;
  throw std::invalid_argument( "Unexisting axis" );
}
  
