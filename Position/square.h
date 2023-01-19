#ifndef _SQUARE_H_
#define _SQUARE_H_
#include "position.h"
#include "../Point_et_Vec/Point_et_Vec.h"

class square {
//class square : public pos {
 public:
  square (Imp X, Rot A);
  
  void   operator+= (real_t v   );
  void   operator+= (Imp   v   );
  void   operator^  (Rot   a   );
  real_t operator|  (square Y   );
  bool   order      (int    axis,
              	    square  Y   );
  Imp   operator-  (square Y   );
  Rot   operator<< (square Y   );
  real_t x          (int    proj);
  real_t y          (int    proj);
  real_t z          (int    proj);
  real_t t          (int    proj);
  real_t p          (int    proj);
  
  void   move       (Imp   v){       this->operator+=( v);};
  void   move       (real_t v){       this->operator+=( v);};
  void   operator-= (Imp   v){       this->operator+=(-v);};
  void   operator-= (real_t v){       this->operator+=(-v);};
  void   turn       (Rot   a){       this->operator^ ( a);};
  real_t dist       (square Y){return this->operator| ( Y);};
  Imp   move_view  (square Y){return this->operator- ( Y);};
  Rot   angle_view (square Y){return this->operator<<( Y);};
  Rot   operator>> (square Y){return  Y<<(this[0]);};
  real_t x (){return this->x(0);};
  real_t y (){return this->y(0);};
  real_t z (){return this->z(0);};
  real_t t (){return this->t(0);};
  real_t p (){return this->p(0);};

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