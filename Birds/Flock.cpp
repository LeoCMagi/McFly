#include<iostream>
#include "Flock.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include<random>
#include<chrono>
using namespace std;
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed); 
std::uniform_real_distribution<real_t> distribution(2.,360.);
auto dice = std::bind (distribution,generator);
void Flock::update_dist() {
    int i, j;
    for (i=0;i<n;i++) {
        t_dist[i][i]=0;
        for (j=0;j<i;j++) {
            t_dist[i][j] = (l_pos[i] | l_pos[j]);
        }
    }
}
void Flock::set_parameters (real_t J_, real_t v0_, real_t rc_,real_t g_) {
    J=J_; v0=v0_; rc=rc_; g=g_;
}
Flock::Flock (int n_, real_t J_, real_t v0_, real_t rc_, real_t g_) {
    n = n_;
    J=J_;
    v0=v0_;
    rc=rc_;
    g=g_;
    texture.loadFromFile("oiseau.png");
    //l_birds_prec = std::vector<boids> (n);
    //l_birds = std::vector<boids>(n_,boids(texture));
    l_speed = std::vector<real_t> (n_,0);
    l_pos = std::vector<pos> (n_,pos(Imp{0,0,0}, Rot(0,0)));
    t_dist = std::vector<std::vector<real_t>> (n_,std::vector<real_t> (n_));
    l_sprites = std::vector<sf::Sprite> (n_);
    int i;
    for (i=0;i<n_;i++) {
        l_pos[i] = pos(Imp {dice(),dice(),dice()}, Rot (dice()*M_PI/180,dice()*M_PI/180));
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(255, 255, 255, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
    }
    l_speed_prec = l_speed;
    l_pos_prec = l_pos;
    update_dist();
}
//Flock::Flock (const std::vector<boids>& list_birds, real_t J_, real_t v0_, real_t rc_,real_t g_):n(list_birds.size()), J(J_), v0(v0_), rc(rc_), g(g_), l_birds(list_birds),l_birds_prec(std:vector<real_t>), t_dist(std::vector<std::vector<real_t>> (list_birds.size(),std::vector<real_t> (list_birds.size()))){update_dist();}
void Flock::draw(sf::RenderWindow& window) {
    int i;
    for (i=0;i<n;i++) {
        window.draw(l_sprites[i]);
    }
}

void Flock::update_flock() {
    l_speed_prec = l_speed;
    l_pos_prec = l_pos;
    int i, j;
    for (i=0;i<n;i++) {
        l_pos[i]+= l_speed_prec[i]; //dt=1 
        Imp Fsc {.x= 2*g*(v0-l_speed_prec[i]),.y=0,.z=0};
        Imp Fint {0,0,0};
        for (j=0;j<n;j++) {
            if (t_dist[i][j]<rc) {
                Rot angles = l_pos_prec[i] <<l_pos_prec[j];
                Fint += J*Imp{l_speed_prec[i]-l_speed_prec[j]*sin(angles.phi())*cos(angles.theta()),
                -l_speed_prec[j]*sin(angles.theta())*sin(angles.phi()),
                -l_speed_prec[j]*cos(angles.theta())};
            }
            Imp F = Fsc+Fint; //dt =1
            l_speed[i] = !(F+Imp{l_speed[i],0,0});
            l_pos[i] ^ F.direction();
        }
    }
    update_dist();
}
/*void store_data(int& iteration,
                int  N_dt,
                int  proj,
                bool tp,
                bool is_drone,
                ofstream file)
    if (iteration==0){
                      file << "time,";
                      file << "boid,";
                      file << "speed,";
                      file << "x,";
                      file << "y,";
                      file << "z,";
        if (tp){      file << "theta,";
                      file << "phi,";  }
        if (is_drone){file << "drone,";}
                      file << endl;
    }
    if (iteration% N_dt==0){
        int i;
        for (i=0, i<n, i++){
                          file << iteration << ",";
                          file << i << ",";
                          file << l_birds[i].v << ",";
                          file << l_birds[i].position.x(proj) << ",";
                          file << l_birds[i].position.y(proj) << ",";
                          file << l_birds[i].position.z(proj) << ",";
            if (tp){      file << l_birds[i].position.t(proj) << ",";
                          file << l_birds[i].position.p(proj) << ",";}
            if (is_drone){file << l_birds[i].drone << ",";}
                          file << endl;
    }
    iteration++;
    }*/