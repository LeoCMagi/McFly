#ifndef _disk_H_
#define _disk_H_
#include "../Vec/Vec.h"

class disk {
 public:
  disk (Imp X, Rot A);
  
  void   operator+= (real_t v   );
  void   operator+= (Imp    v   );
  void   operator^  (Rot    a   );
  real_t operator|  (disk   Y   );
  Imp    operator-  (disk   Y   );
  Rot    operator<< (disk   Y   );
  real_t x          (int    proj);
  real_t y          (int    proj);
  real_t z          (int    proj);
  real_t t          (int    proj);
  real_t p          (int    proj);
  
  void   move       (Imp    v){       this->operator+=( v);};
  void   move       (real_t v){       this->operator+=( v);};
  void   operator-= (Imp    v){       this->operator+=(-v);};
  void   operator-= (real_t v){       this->operator+=(-v);};
  void   turn       (Rot    a){       this->operator^ ( a);};
  real_t dist       (disk   Y){return this->operator| ( Y);};
  Imp    move_view  (disk   Y){return this->operator- ( Y);};
  Rot    angle_view (disk   Y){return this->operator<<( Y);};
  Rot    operator>> (disk   Y){return  Y<<(this[0]);};
  real_t x (){return this->x(0);};
  real_t y (){return this->y(0);};
  real_t z (){return this->z(0);};
  real_t t (){return this->t(0);};
  real_t p (){return this->p(0);};

 private:
  float x_coord;
  float y_coord;
  float t_angle; // stands for θ, angle with axis 0.

  void clean();
};

#endif


/* disk Documentation :

Projections:
  0) {default} trivial projection
    (x,y) | (x-0.5)²+(y-0.5)²<1
    t   ∈ ]-π, π]

  1) Cylindrical coordinates
    x = r
    y = θ
    t   ∈ ]-π, π]

  2) Cylindrical coordinates but switched
    x = θ
    y = r
    t   ∈ ]-π, π]
*/   