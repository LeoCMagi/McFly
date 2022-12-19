#ifndef _POSITION_H_
#define _POSITION_H_

class pos {
 public:
  //virtual pos (float[5] X);
  /* apparently I connot define constructors virtually
     so I guess I'll just ignore the problem for now*/
  
  //virtual float coord (int   proj);
  /* I wanted to return a float[5] object, but forgot that it also didn't work...*/
  virtual void     move  (float v[3]) const = 0;
  virtual void     turn  (float a[2]) const = 0;
  virtual float    dist  (pos   Y   ) const = 0;
  virtual bool     order (int   axis,
	        	  pos   Y   ) const = 0;

  //float[5] coord (){return self.coord(0);};
  //void move (float v){return this->move({v,0,0});};
  // problem : compiler says he doesn't know how to convert {v,0,0} into float*, maybe I can fix that but perhaps, changing the structure of the function might be simplier...
};



#endif
/* Shouldn't we do mutable variables? To avoid making copies of everything when doing x.move(...) ? I assued that yes, but it can be changed once we've disscussed it.

also, is it necessary to code move for vectors?*/
