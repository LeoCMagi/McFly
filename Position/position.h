#ifndef _POSITION_H_
#define _POSITION_H_
#include "../Point_et_Vec/Point_et_Vec.h"

class pos {
 public:
  pos (Imp X, Rot A);
  
  virtual void   operator+= (real_t v   );
  virtual void   operator+= (Imp   v   );
  virtual void   operator^  (Rot   a   );
  virtual real_t operator|  (pos    Y   );
  virtual bool   order      (int    axis,
              	             pos  Y   );
  virtual Imp   operator-  (pos Y   );
  virtual Rot   operator<< (pos Y   );
  virtual real_t x          (int    proj);
  virtual real_t y          (int    proj);
  virtual real_t z          (int    proj);
  virtual real_t t          (int    proj);
  virtual real_t p          (int    proj);
  
  void   move       (Imp   v){       this->operator+=( v);};
  void   move       (real_t v){       this->operator+=( v);};
  void   operator-= (Imp   v){       this->operator+=(-v);};
  void   operator-= (real_t v){       this->operator+=(-v);};
  void   turn       (Rot   a){       this->operator^ ( a);};
  real_t dist       (pos    Y){return this->operator| ( Y);};
  Imp   move_view  (pos    Y){return this->operator- ( Y);};
  Rot   angle_view (pos    Y){return this->operator<<( Y);};
  Rot   operator>> (pos    Y){return  Y<<(this[0]);};
  real_t x (){return this->x(0);};
  real_t y (){return this->y(0);};
  real_t z (){return this->z(0);};
  real_t t (){return this->t(0);};
  real_t p (){return this->p(0);};
  
};

/*   Position Documentation:
Every method's name can be used instead of the proper operator,
if the user desires more clarity...
let "p" refer to a given position.

--.move(v)
  if v is a Imp; moves the position of that vector.
  if v is real; moves that position of v in the position's own direction
  is written " p += v; "

--.turn(A)
  Rotates the position according to A.
  A NEEDS to be of type Rot (containing theta and phy)
  is written " p^A; "
  
--.dist(p')
  yields the distance to p'
  is written " real_t d = (p|p'); "

--.order(axis, p')
  is used to get a partial order over the set of all positions
  is written " p.oder(2,p'); "

--.move_view(p)  ~here p' and p where switched for clarity
  sends the vector needed to move to p' (from p)
  it can also be understood at the position at which p sees p'.
  note that in the case of a periodical space, it will be the
    closest position at which p sees p'...
  is written " Imp v = p'-p; "

--.angle_view(p')
  sends the rotation needed to have p point towards p'
  it can also be understood at the angle at which p sees p'.
  note that in the case of a periodical space, it will be the
    closest position at which p' sees p...
  is written " Rot v = p<<p'; "
  but can be rewritten "... p'>>p" for symetry's sake...
  
--.x(); .y(); .z(); .t(); .p()
  these are the methods to get coorddinates in a particular projection.
  it is written " real_t = p.y(proj); "
  where proj is the number of the projection.
  Note that this number is optionnal.
  Also note that the default projection will never yield values outside
    of [0, 1] for .x(), .y(), and .z()
    of [-π,π] for .t() and .p()
  each projection is specific to each space, so I recommend you
    check their respectiv documentations*/

#endif