#ifndef _POSITION_H_
#define _POSITION_H_


/*#include "free2d.h"
using pos = free2d;
*/


/*#include "free3d.h"
using pos = free3d;
*/


#include "square.h"
using pos = square;




/*#include "annulus.h"
using pos = annulus;
*/


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
