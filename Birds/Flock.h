#ifndef FLOCK_H
#define FLOCK_H
//#include "../Boids.h"
#include "../Vec/Vec.h"
#include "../Position/position.h"
#include "SFML/Graphics.hpp"

class Flock {
    private :
    int n;
    real_t J, v0, rc, g;
    std::vector<real_t> l_speed;
    std::vector<pos> l_pos;
    std::vector<real_t> l_speed_prec;
    std::vector<pos> l_pos_prec;
    std::vector<std::vector<real_t>> t_dist;
    void update_dist ();
    //std::vector<sf::Texture> l_sprites;
    public :
    sf::Texture texture;
    std::vector<sf::Sprite> l_sprites;
    std::vector<std::vector<real_t>> tab_dist () const {return t_dist;}
    std::vector<real_t> speed_boids () const {return l_speed;}
    std::vector<pos> pos_boids() const {return l_pos;}
    void update_flock();
    void set_parameters (real_t J_, real_t v0_, real_t rc_,real_t g_);
    Flock (int n_,real_t J_, real_t v0_, real_t rc_, real_t g_);
    //Flock (const std::vector<boids>& list_birds, real_t J_, real_t v0_, real_t rc_,real_t g_);
    void draw(sf::RenderWindow& window);
};

#endif