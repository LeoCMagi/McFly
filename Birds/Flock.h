#ifndef FLOCK_H
#define FLOCK_H
#include "../Boids.h"

class Flock {
    private :
    int n;
    std::vector<boids> l_birds;
    std::vector<std::vector<real_t>> t_dist;
    void update_dist ();
    //std::vector<sf::Texture> l_sprites;
    public :
    sf::Texture texture;
    std::vector<std::vector<real_t>> tab_dist () const {return t_dist;}
    std::vector<boids> l_boids () const {return l_birds;}
    //void update_flock();
    Flock (int n_);
    Flock (const std::vector<boids>& list_birds):n(list_birds.size()),l_birds(list_birds),
    t_dist(std::vector<std::vector<real_t>> (list_birds.size(),std::vector<real_t> (list_birds.size()))){update_dist();}
    void draw(sf::RenderWindow& window);
};

#endif