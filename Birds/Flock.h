#ifndef FLOCK_H
#define FLOCK_H
#include "../Vec/Vec.h"
#include "../Position/position.h"
#include "SFML/Graphics.hpp"
#include<fstream>

class Flock {
    private :
    int N_birds, n_drones;
    real_t I_rep, I_all, I_att; // Force Intensities
    real_t r_rep, r_all;        // Radius of interaction
    real_t v0;                  // Other parameters
    std::vector<real_t> l_speed;
    std::vector<pos> l_pos;
    std::vector<real_t> l_speed_prec;
    std::vector<pos> l_pos_prec;
    std::vector<std::vector<real_t>> t_dist;
    void update_dist ();
    int boid_state(int i);
    void update_graphics();
    Imp get_F(int i);
    Imp F_rep(int i);
    Imp F_att(int i);
    Imp F_all(int i);
    
    public :
    sf::Texture texture;
    std::vector<sf::Sprite> l_sprites;
    std::vector<std::vector<real_t>> tab_dist () const {return t_dist;}
    std::vector<real_t> speed_boids () const {return l_speed;}
    std::vector<pos> pos_boids() const {return l_pos;}
    void update_flock();
    void set_parameters (real_t I_all_, real_t v0_, real_t r_rep_,real_t I_att_, real_t r_all_, real_t I_rep_);
    Flock (int N_birds_, real_t vi_birds, const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones); //vi_birds initial speed of birds
    Flock (const std::vector<real_t>& speed_birds, const std::vector<pos>& pos_birds,const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones);
    void draw(sf::RenderWindow& window);
    void store_data(int  iteration,
                    int  N_dt,
                    int  proj,
                    bool tp,
                    bool is_drone,
                    std::ofstream& file);
};

#endif
