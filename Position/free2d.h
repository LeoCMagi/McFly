#ifndef _FREE2D_H_
#define _FREE2DN_H_
#include "position.h"

class free2d {
//class free2d : public pos {
 public:
  free2d (float X[3], float A[2]);
  
  void  move       (float  v   );
  void  operator+= (float  v[3]);
  void  turn       (float  a[2]);
  float dist       (free2d Y   );
  bool  order      (int    axis,
              	    free2d Y   );
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
