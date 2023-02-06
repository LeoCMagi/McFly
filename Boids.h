#ifndef BOIDS_H
#define BOIDS_H
#include "SFML/Graphics.hpp"
#include "../position/free2d.h"
//#include "../position/position.h"
#include "../Vec/Vec.h"


class boids
{
free2d position;
Imp impulsion;
sf::Texture texture;
sf::Sprite sprite;

public:
boids();
boids(free2d posi,Imp impulse);
void impulsion_noise(int distrib);
void update_position();

void draw(sf::RenderWindow &window)//draw sprite in window



};
#endif BOIDS_H


