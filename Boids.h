#ifndef BOIDS_H
#define BOIDS_H
#include "Vec/Vec.h"
#include "Position/position.h"
#include "SFML/Graphics.hpp"


class boids
{
pos position;
Imp impulsion;
sf::Texture texture;
//sf::Sprite sprite;

public:
sf::Sprite sprite;
boids();
boids(pos posi,Imp impulse);
void impulsion_noise(int distrib);
void update_position();

void draw(sf::RenderWindow &window);//draw sprite in window



};
#endif


