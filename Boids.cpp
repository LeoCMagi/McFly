#include<iostream>
#include "Boids.h"
#include<cmath>

//implementing constructors
boids::boids(posu,vec3 impulsu):pos(posu),impulse(impulsu){}

boids::boids():pos(/*null position ?*/),impulse([0.,0.,0.]){
texture.loadFromFile("oiseau.png");
sprite.setTexture(texture);
sprite.setOrigin(jesaispasfrr)}


void boids::impulsion_noise(int distrib){
/* test the integer to put gaussian, lorentzian or whatever noise you want : use Von Neumann transformation method to get the distibution */
}

void boids::update_postion(){
(X,A)=boids.pos;
//RK4?Euler?
}
	
