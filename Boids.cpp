#include<iostream>
#include "Boids.h"
#include<cmath>
//window.setFramerateLimit(FPS)
//implementing constructors
boids::boids(posu,Imp impulsu):pos(posu),impulse(impulsu){}

boids::boids():pos(/*null position ?*/),impulse([0.,0.,0.]){
texture.loadFromFile("oiseau.png");
sprite.setTexture(texture);
sprite.setColor(sf::Color(255, 255, 255, 128))//color,opacity
sprite.setOrigin(sf::Vector3f(25.f,0.f,0.f))
sprite.setPosition(sf::Vector3f(10.f, 50.f,75.f));}


void boids::impulsion_noise(int distrib){
/* test the integer to put gaussian, lorentzian or whatever noise you want : use Von Neumann transformation method to get the distibution */
}
//max speed, max acceleration in input of update pos ?
//more in flock.h
void boids::update_postion(){
(X,A)=boids.pos;

boids.sprite.rotate(15.f);//rotation of the sprite
boids.sprite.move(sf::Vector3f(5.f,10.f,15.f));//translation of the sprite

//RK4?Euler?
}

void boids::draw(sf::RenderWindow &window)
{
window.draw(sprite);
}
	
