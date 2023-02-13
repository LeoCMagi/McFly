#include "Boids.h"
#include<random>
#include<chrono>
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed); 
std::uniform_real_distribution<real_t> distribution(2.,360.);
auto dice = std::bind (distribution,generator);
//window.setFramerateLimit(FPS)
//implementing constructors
//change scale and opacity with distance in 3D ?
boids::boids(pos posu,Imp impulsu):position(posu),impulsion(impulsu){}

boids::boids():position(Imp {x=dice(),y=dice(),dice()}, Rot (dice(),dice() )),impulsion(Imp {0.,0.,0.}){
texture.loadFromFile("oiseau.png");
sprite.setTexture(texture);
sprite.setColor(sf::Color(255, 255, 255, 128));//color,opacity
sprite.setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite
sprite.setScale(0.02f,0.02f);//scale of the boid;
sprite.setPosition(sf::Vector2f(position.x()*1500, position.y()*1200));//initial position of the boid}
sprite.setRotation(0.f);//initial angle of the boid
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
void boids::update_position(){

sprite.rotate(position.t());//rotation of the sprite
sprite.move(sf::Vector2f(position.x(),position.y()));//translation of the sprite

//RK4?Euler?
}

void boids::draw(sf::RenderWindow &window){
	window.draw(sprite);
	}

