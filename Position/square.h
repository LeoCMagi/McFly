#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "position.h"

class square {
//class square : public pos {
 public:
  square (float X[3], float A[2]);
  
  void  move       (float  v   );
  void  operator+= (float  v[3]);
  void  turn       (float  a[2]);
  float dist       (square Y   );
  bool  order      (int    axis,
              	    square Y   );
  float x          (int    proj);
  float y          (int    proj);
  float z          (int    proj);
  float t          (int    proj);
  float p          (int    proj);
  
  float x (){return this->x(0);};
  float y (){return this->y(0);};
  float z (){return this->z(0);};
  float t (){return this->t(0);};
  float p (){return this->p(0);};

 private:
  float x_coord;
  float y_coord;
  float t_angle; // stands for θ, angle with axis 0.
};

#endif


/* SQUARE Documentation :


Dimensions of the box:
  The square is characterized by two radii : r_x & r_y
    r_x fixed at the constant value 1.
    r_y that can be changed (to work on a rectangle
    rather than a proper square)
  WARNING: the condition r_x >= r_y will be imposed!



Projections:
  0) {default} whilde projection
    (x,y) ∈ [0,1] x [0, r_y]
    t   ∈ ]-π, π]

    all the coordinates are visible.
    Warning : if r_x >> r_y
              nothing will be visible
              use other projection.

  1) croped projection
    x,y ∈ [0 , 1]²
    t   ∈ ]-π, π]

    the space is scaled to enlarge the smaller
      axis. The bigger axis is thus cropped.
      When a boid leaves the visible part of 
      the square, we only see it's projection on the edge.
  
  2) dilated projection
    x,y ∈ [0 , 1]²
    t   ∈ ]-π, π]

    the entire space is now visible, without
      loss of space. However, the angles are
      no longer "true".
*/   