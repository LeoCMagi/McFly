#ifndef BOIDS_H
#define BOIDS_H
#include "Vec/Vec.h"
#include "Position/position.h"
#include "SFML/Graphics.hpp"


class boids
{
pos position;
Imp impulsion;
sf::Texture& texture;
//sf::Sprite sprite;

public:
float x;
float y;
pos posi() const{return position;}
Imp impulsi() const{return impulsion;}
sf::Sprite sprite;
boids(sf::Texture& texture_ref);
boids(pos posi,Imp impulse,sf::Texture& texture_ref);
void impulsion_noise(int distrib);
//void update_position();

void draw(sf::RenderWindow &window);//draw sprite in window



};
#endif


