#ifndef FLOCK_H
#define FLOCK_H
#include "../Vec/Vec.h"
#include "../Position/position.h"
#include "SFML/Graphics.hpp"
#include<fstream>

class Flock {
    private :
/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX     The Parameters     XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/  int N_birds, n_drones;
    real_t I_rep, I_all, I_att, I_noi;  // Force Intensities
    real_t r_rep, r_all, r_att;         // Radius of interaction
    real_t v0;                          // Other parameters


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX     Data Management     XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/  std::vector<real_t>              l_speed;
    std::vector<real_t>              l_speed_prec;
    std::vector<pos>                 l_pos;
    std::vector<pos>                 l_pos_prec;
    std::vector<std::vector<real_t>> t_dist;


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX     Internal Operators     XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/  //   Update-related
    void update_dist    ();
    void update_graphics();

    //  Force-related
    int  boid_state (int i);
    Imp  get_F      (int i);
    Imp  F_rep      (int i);
    Imp  F_att      (int i);
    Imp  F_all      (int i);
    bool is_visible (int from,
                     int to)
         {return true;};//( (l_pos_prec[to]-l_pos_prec[from]).x > 0 );};


    public :
/*  XXXXXXXXXXXXXXXXXXXXXXXX
    XXX     Graphics     XXX
    XXXXXXXXXXXXXXXXXXXXXXXX
*/  sf ::Texture            texture;
    std::vector<sf::Sprite> l_sprites;

/*  XXXXXXXXXXXXXXXXXXXXXXX
    XXX     Getters     XXX
    XXXXXXXXXXXXXXXXXXXXXXX
*/  std::vector<std::vector<real_t>> tab_dist    () const {return t_dist;}
    std::vector<real_t>              speed_boids () const {return l_speed;}
    std::vector<pos>                 pos_boids   () const {return l_pos;}

/*  XXXXXXXXXXXXXXXXXXXXXXX
    XXX     Setters     XXX
    XXXXXXXXXXXXXXXXXXXXXXX
*/  void set_Intensities (real_t I_rep_, real_t I_all_, real_t I_att_, real_t I_noi_);
    void set_Radii       (real_t r_rep_, real_t r_all_, real_t r_att_);
    void set_Speed       (real_t v0_);

/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX     Constructors     XXX
    XXXXXXXXXXXXXXXXCCCCCXXXXXXX
*/  Flock (int N_birds_, real_t vi_birds, const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones); //vi_birds initial speed of birds
    Flock (const std::vector<real_t>& speed_birds, const std::vector<pos>& pos_birds,const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones);

/*  XXXXXXXXXXXXXXXXXXXXXXXX
    XXX     Updators     XXX
    XXXXXXXXXXXXXXXXXXXXXXXX
*/  void old_update_flock();

    void update_flock();
    void draw        (sf::RenderWindow& window);
    void store_data  (int  iteration,
                      int  N_dt,
                      int  proj,
                      bool tp,
                      bool is_drone,
                      std::ofstream& file);
};

#endif
