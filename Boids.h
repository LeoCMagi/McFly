#ifndef BOIDS_H
#define BOIDS_H
#include "Vec/Vec.h"
#include "Position/position.h"
#include "SFML/Graphics.hpp"


class boids
{
pos position;
real_t v;
//Imp impulsion;
sf::Texture& texture;
//sf::Sprite sprite;

public:
/*float x;
float y;*/
pos posi() const{return position;}
real_t speed() const{return v;}
sf::Sprite sprite;
boids(sf::Texture& texture_ref);
//boids(pos posi,Imp impulse,sf::Texture& texture_ref);
boids(pos posi, real_t vit, sf::Texture& texture_ref); 
void impulsion_noise(int distrib);
//void update_position();

void draw(sf::RenderWindow &window);//draw sprite in window



};
#endif


