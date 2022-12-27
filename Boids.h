#ifndef BOIDS_H
#define BOIDS_H
#include "SFML/Graphics.hpp"


class boids
{
pos position;
vec3 impulsion;
sf::Texture texture;
sf::Sprite sprite;

public:
boids();
boids(pos posi,vec3 impulse);
void impulsion_noise(int distrib);
void update_position();

void draw(sf::RenderWindow &window)//draw sprite in window



};
#endif BOIDS_H


