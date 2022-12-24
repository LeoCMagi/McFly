#ifndef _FREE2D_H_
#define _FREE2DN_H_
#include "../Point_et_Vec/Point_et_Vec.h"
#include "position.h"

class free2d {
//class free2d : public pos {
 public:
  free2d (Vec3 X, Vec2 A);
  
  void   operator+= (real_t v   );
  void   operator+= (Vec3   v   );
  void   operator^  (Vec2   a   );
  real_t operator|  (free2d Y   );
  bool   order      (int    axis,
              	    free2d  Y   );
  Vec3   operator-  (free2d Y   );
  Vec2   operator<< (free2d Y   );
  real_t x          (int    proj);
  real_t y          (int    proj);
  real_t z          (int    proj);
  real_t t          (int    proj);
  real_t p          (int    proj);
  
  void   move       (Vec3   v){       this->operator+=( v);};
  void   move       (real_t v){       this->operator+=( v);};
  void   operator-= (Vec3   v){       this->operator+=(-v);};
  void   operator-= (real_t v){       this->operator+=(-v);};
  void   turn       (Vec2   a){       this->operator^ ( a);};
  real_t dist       (free2d Y){return this->operator| ( Y);};
  Vec3   move_view  (free2d Y){return this->operator- ( Y);};
  Vec2   angle_view (free2d Y){return this->operator<<( Y);};
  Vec2   operator>> (free2d Y){return  Y<<(this[0]);};
  real_t x (){return this->x(0);};
  real_t y (){return this->y(0);};
  real_t z (){return this->z(0);};
  real_t t (){return this->t(0);};
  real_t p (){return this->p(0);};

 private:
  real_t x_coord;
  real_t y_coord;
  real_t t_angle; // stands for θ, angle with axis 0.
};

#endif


/* FREE2D Documentation :

Projections:
  0) {default} cropped projection
    x,y ∈ ]0 , 1[²
    t   ∈ ]-π, π]

    When a boid leaves [-½,½]²,
      we only get its projection on the square's
      edges.
      (all of that is shifted by (½,½) to center 
      the picture on (0,0), for aesthetics)
    This allows to follow their orentation without
      leaving the center square...
  

  1) trivial projection
    x,y ∈ ℝ²
    t   ∈ ]-π, π]


  2) exponantial projection
      x,y ∈ ]0, 1[²
      t   ∈ ]-π, π]

    Gives a global view of the entire ℝ²
      (all of that is shifted by (½,½) to center 
      the picture on (0,0), for aesthetics)
*/
