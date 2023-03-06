#include "Boids.h"
#include<random>
#include<chrono>
#include<iostream>
using namespace std;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed); 


std::uniform_real_distribution<real_t> distribution(2.,360.);
auto dice = std::bind (distribution,generator);


std::normal_distribution<real_t> normal(0.,sqrt(2*3*0.5));
auto gauss = std::bind (normal,generator);

//implementing constructors
//change scale and opacity with distance in 3D ?
//boids::boids(pos posu,Imp impulsu, sf::Texture& texture_ref):position(posu),impulsion(impulsu),texture(texture_ref){}

boids::boids(pos posu, real_t vit, sf::Texture& texture_ref):position(posu),v(vit),texture(texture_ref){}

boids::boids(sf::Texture& texture_ref):position(Imp {dice(),dice(),dice()}, Rot {dice(),dice()}),v(0),texture(texture_ref){
sprite.setTexture(texture);
sprite.setColor(sf::Color(255, 255, 255, 128));//color,opacity
sprite.setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite
sprite.setScale(0.02f,0.02f);//scale of the boid;
sprite.setPosition(sf::Vector2f(position.x()*1500, position.y()*1200));//initial position of the boid}
sprite.setRotation(position.t()*180/M_PI);//initial angle of the boid
}


Imp boids::impulsion_noise(){	
	Imp F = Imp{gauss(),gauss(),gauss()};
	return F;
}



void boids::draw(sf::RenderWindow &window){
	window.draw(sprite);
	}

