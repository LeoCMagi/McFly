#ifndef BOIDS_H
#define BOIDS_H
#include "SFML/Graphics.hpp"
#include "../position/position.h"
#include "../Vec/Vec.h"


class boids
{
pos position;
Imp impulsion;
sf::Texture texture;
sf::Sprite sprite;

public:
boids();
boids(pos posi,Imp impulse);
void impulsion_noise(int distrib);
void update_position();

void draw(sf::RenderWindow &window)//draw sprite in window



};
#endif BOIDS_H


