#ifndef _POSITION_H_
#define _POSITION_H_
#include "../Point_et_Vec/Point_et_Vec.h"

class pos {
 public:
  pos (Vec3 X, Vec2 A);
  
  virtual void     move       (float v   );
  virtual void     operator+= (Vec3  v   );
  virtual void     turn       (Vec2  a   );
  virtual float    dist       (pos   Y   );
  virtual bool     order      (int   axis,
                       	       pos   Y   );

  //virtual x,y,z,t,p...      
};


#endif