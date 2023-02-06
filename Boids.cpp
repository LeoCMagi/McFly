#include<iostream>
#include "Boids.h"
#include<cmath>
#include<random>
auto dice = std::uniform_int_distribution<int> distribution(2,360);
//window.setFramerateLimit(FPS)
//implementing constructors
//change scale and opacity with distance in 3D ?
boids::boids(free2d posu,Imp impulsu):free2d(posu),Imp(impulsu){}

boids::boids():free2d(Imp {dice(),dice(),dice()}, Rot (dice(),dice() ),impulse(Imp {0.,0.,0.}){
texture.loadFromFile("oiseau.png");
sprite.setTexture(texture);
sprite.setColor(sf::Color(255, 255, 255, 128));//color,opacity
sprite.setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite
sprite.setScale(0.02f,0.02f);//scale of the boid;
sprite.setPosition(sf::Vector2f(free2d.x(), free2d.y()));//initial position of the boid}
sprite.setRotation(Angle);//initial angle of the boid
}


void boids::impulsion_noise(int distrib){
/* test the integer to put gaussian, lorentzian or whatever noise you want : use Von Neumann transformation method to get the distibution */
//von neumann 1styear:
/*int Von_Neumann(double x,double y,double z){//pour réaliser la distribution on utilise la methode de Von Neumann
  int b=0;
  double r=sqrt(x*x+y*y+z*z);
  double phi=atan(y/x);
  double theta=atan(y/(z*sin(phi)));
  double dp=pow(fabs(R(r,n,l)*Y(theta,phi,l,m,v)),2.);//on calcule dp
  double w=drand48();//on prends valeur aleatoire entre 0 et 1
  if (w/(1000)<dp){
    b=1;
  }
  return b;
}*/
//if b(==1){ do something}

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
	
