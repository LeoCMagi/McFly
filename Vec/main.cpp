#include "Vec.h"
#include <cmath>
#include <iostream>
using namespace std;

int main() {
  Imp u {1,1,1};
  cout <<"norme de u " << !u << endl;
  Rot angle {M_PI/4,0};
  Imp v = Imp::u_angle (angle);
  cout <<"coordonnées de v " << v.x << " " <<v.y << " " << v.z<<endl;
  Rot dir_u = u.direction(), dir_v = v.direction();
  cout << "theta_u " << dir_u.theta << " phi_u " << dir_u.phi <<endl;
  cout << "theta_v "<< dir_v.theta << " phi_v " << dir_v.phi<<endl;
  Imp w = v.rotate(Rot {M_PI/4,M_PI/4});
  Rot dir_w = w.direction();
  cout << "theta_w " << dir_w.theta << " phi_w " << dir_w.phi <<endl;
 return 0;
}
