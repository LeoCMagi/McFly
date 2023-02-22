#ifndef BOIDS_H
#define BOIDS_H
#include "Vec/Vec.h"
#include "Position/position.h"
#include "SFML/Graphics.hpp"


class boids
{
pos          position;
real_t       v;
sf::Texture& texture;
//sf::Sprite sprite;

public:
boids(sf::Texture& texture_ref);
boids(pos          posi,
      real_t       vit,
      sf::Texture& texture_ref);
//boids(pos posi,Imp impulse,sf::Texture& texture_ref);

pos    posi           () const{return position;}
real_t speed          () const{return v;}
void   impulsion_noise(int distrib);
void   draw           (sf::RenderWindow &window);//draw sprite in window
void   move           (real_t v) {position += v;}
void   turn           (Rot    r) {position  ^ r;}
//void update_position();

sf::Sprite sprite;

};
#endif


