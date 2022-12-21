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
  0) {par défaut} projection rognée
    x,y ∈ ]0 , 1[²
    a   ∈ ]-π, π]

    Quand un boid sort du carré [-½,½]²,
      on ne voit plus que sa projection
      sur les bords du carré.
      (le tout, translaté d'un demi,
      utiliser (0,0) comme centre d'image, c'est
      plus simple à coder)
    Cela permet de suivre leur orientation
      sans sortir du carré...
  

  1) projection triviale
    x,y ∈ ℝ²
    a   ∈ ]-π, π]


  2) projection expoantielle
      x,y ∈ ]0, 1[²
      a   ∈ ]-π, π]

    Donne une vision d'ensemble de tout ℝ²
      (le tout, translaté d'un demi,
      utiliser (0,0) comme centre d'image, c'est
      plus simple à coder)
*/
