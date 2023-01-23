#include<iostream>
#include "Boids.h"
#include<cmath>
//window.setFramerateLimit(FPS)
//implementing constructors
//change scale and opacity with distance in 3D ?
boids::boids(posu,Imp impulsu):pos(posu),impulse(impulsu){}

boids::boids():pos( ),impulse([0.,0.,0.]){
texture.loadFromFile("oiseau.png");
sprite.setTexture(texture);
sprite.setColor(sf::Color(255, 255, 255, 128));//color,opacity
sprite.setOrigin(sf::Vector3f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite
sprite.setscale(0.05f,0.05f);//scale of the boid;
sprite.setPosition(sf::Vector3f(pos.x(), pos.y(),pos.z()));//initial position of the boid}
sprite.setRotation(Angle);//initial angle of the boid}


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
	
