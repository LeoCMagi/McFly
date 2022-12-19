#ifndef _FREE2D_H_
#define _FREE2DN_H_
//#include "position.h"

class free2d {
//class free2d : public pos {
 public:
  free2d (float X[5]);
  
  // float[5] coord (int    proj);
  void     move  (float  v[3]);
  void     turn  (float  a[2]);
  float    dist  (free2d Y   );
  bool     order (int    axis,
		  free2d Y   );
 private:
  float x;
  float y;
  float t; // stands for θ, angle with axis 0.
};

#endif
