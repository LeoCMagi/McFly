#ifndef _FREE3D_H_
#define _FREE3D_H_
#include "../Vec/Vec.h"

class free3d {
 public:
  free3d (Imp X, Rot A);
  
  void   operator+= (real_t v   );
  void   operator+= (Imp    v   );
  void   operator^  (Rot    a   );
  real_t operator|  (free3d Y   );
  Imp   operator-  (free3d  Y   );
  Rot   operator<< (free3d  Y   );
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
  real_t dist       (free3d Y){return this->operator| ( Y);};
  Imp    move_view  (free3d Y){return this->operator- ( Y);};
  Rot    angle_view (free3d Y){return this->operator<<( Y);};
  Rot    operator>> (free3d Y){return  Y<<(this[0]);};
  real_t x (){return this->x(0);};
  real_t y (){return this->y(0);};
  real_t z (){return this->z(0);};
  real_t t (){return this->t(0);};
  real_t p (){return this->p(0);};

 private:
  real_t x_coord;
  real_t y_coord;
  real_t z_coord;
  Rot angle; // stands for (θ, \phi)
};

#endif


/* free3d Documentation :

Projections:
  0) {default} cropped projection
    x,y,z ∈ ]0 , 1[³
    t   ∈ ]-π, π]
    p   ∈ ] 0, π]

    When a boid leaves [-½,½]³,
      we only get its projection on the square's
      edges.
      (all of that is shifted by (½,½,½) to center 
      the picture on (0,0,0), for aesthetics)
    This allows to follow their orentation without
      leaving the center square...
  

  1) trivial projection
    x,y,z ∈ ℝ³
    t     ∈ ]-π, π]
    p     ∈ ]0,  π]


  2) exponantial projection
      x,y,z ∈ ]0, 1[²
      t     ∈ ]-π, π]
      p     ∈ ]2, π]

    Gives a global view of the entire ℝ³
      (all of that is shifted by (½,½,½) to center 
      the picture on (0,0), for aesthetics)
*/
