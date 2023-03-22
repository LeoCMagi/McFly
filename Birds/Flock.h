#ifndef FLOCK_H
#define FLOCK_H
//#include "../Boids.h"
#include "../Vec/Vec.h"
#include "../Position/position.h"
#include "SFML/Graphics.hpp"

class Flock {
    private :
    int N_birds, n_drones;
    real_t J, v0, rc, g, l0, g0;
    std::vector<real_t> l_speed;
    std::vector<pos> l_pos;
    std::vector<real_t> l_speed_prec;
    std::vector<pos> l_pos_prec;
    std::vector<std::vector<real_t>> t_dist;
    void update_dist ();
    //void store_data ();
    //std::vector<sf::Texture> l_sprites;
    public :
    sf::Texture texture;
    std::vector<sf::Sprite> l_sprites;
    std::vector<std::vector<real_t>> tab_dist () const {return t_dist;}
    std::vector<real_t> speed_boids () const {return l_speed;}
    std::vector<pos> pos_boids() const {return l_pos;}
    void update_flock();
    void set_parameters (real_t J_, real_t v0_, real_t rc_,real_t g_, real_t l0_, real_t g0_);
    Flock (int N_birds_, real_t vi_birds, const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones); //vi_birds initial speed of birds
    Flock (const std::vector<real_t>& speed_birds, const std::vector<pos>& pos_birds,const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones);
    void draw(sf::RenderWindow& window);
};

#endif