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
std::normal_distribution<real_t> normal(0.,sqrt(2*3*0.5*0.00000001));
auto gauss = std::bind (normal,generator);

void Flock::update_dist() {
    int i, j;
    int n = N_birds+n_drones;
    for (i=0;i<n;i++) {
        for (j=0;j<n;j++) {
            t_dist[i][j] = (l_pos[i] | l_pos[j]);
        }
        t_dist[i][i]=0;
    }
}
void Flock::set_parameters (real_t J_, real_t v0_, real_t rc_,real_t g_, real_t l0_, real_t g0_) {
    J=J_; v0=v0_; rc=rc_; g=g_; l0=l0_; g0=g0_;
}
Flock::Flock (int N_birds_,real_t vi_birds,const std::vector<real_t>& speed_drones,const std::vector<pos>& pos_drones){
    N_birds=N_birds_;
    n_drones= speed_drones.size();
    J=0;
    v0=0;
    rc=0;
    g=0;
    l0=0;
    g0=0;
    int n = N_birds_ +n_drones; 
    texture.loadFromFile("oiseau.png");
    l_speed = std::vector<real_t> (n,vi_birds);
    l_pos = std::vector<pos> (n,pos(Imp{0,0,0}, Rot(0,0)));
    t_dist = std::vector<std::vector<real_t>> (n,std::vector<real_t> (n));
    l_sprites = std::vector<sf::Sprite> (n);
    int i;
    for (i=0;i<N_birds_;i++) {
    	   l_speed[i]= vi_birds;
        l_pos[i] = pos(Imp {dice(),dice(),dice()}, Rot (dice()*M_PI/180,dice()*M_PI/180));//dice()*M_PI/180));
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(0, 0, 0, 108));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.07f,0.07f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
    }
    for (i=N_birds; i<n;i++) {
        l_speed[i] =speed_drones[i-N_birds_];
        l_pos[i] = pos_drones[i-N_birds_];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color::Blue);//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.09f,0.09f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
    }
     for (i=N_birds; i<n;i++) {
        l_speed[i] =speed_drones[i-N_birds_];
        l_pos[i] = pos_drones[i-N_birds_];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(120, 0, 0, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.07f,0.07f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
    }
    l_speed_prec = l_speed;
    l_pos_prec = l_pos;
    update_dist();
}

Flock::Flock (const std::vector<real_t>& speed_birds, const std::vector<pos>& pos_birds,const std::vector<real_t>& speed_drones, const std::vector<pos>& pos_drones) {
    N_birds = pos_birds.size();
    n_drones = speed_drones.size();
    int n = N_birds + n_drones;
    l_speed = std::vector<real_t> (n,0.0);
    l_pos = std::vector<pos> (n,pos(Imp{0,0,0}, Rot(0,0)));
    t_dist = std::vector<std::vector<real_t>> (n,std::vector<real_t> (n));
    l_sprites = std::vector<sf::Sprite> (n);
    t_dist = std::vector<std::vector<real_t>> (n,std::vector<real_t> (n));
    J=0;
    v0=0;
    rc=0;
    g=0;
    l0=0;
    g0=0;
    texture.loadFromFile("oiseau.png");
    int i;
    for (i=0;i<N_birds;i++) {
    	   l_pos[i] = pos_birds[i];
        l_speed[i] = speed_birds[i];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(255, 255, 255, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
    }
        for (i=N_birds;i<n;i++) {
        l_pos[i] = pos_drones[i-N_birds];
        l_speed[i] = speed_drones[i-N_birds];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(118, 56, 159, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));//initial position of the boid
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
        } 
        l_pos_prec = l_pos;
        l_speed_prec = l_speed;
    update_dist();
}
void Flock::draw(sf::RenderWindow& window) {
    int i;
    int n = N_birds+n_drones;
    for (i=0;i<n;i++) {
        window.draw(l_sprites[i]);
    }
}



void Flock::update_flock() {
    l_speed_prec = l_speed;
    l_pos_prec = l_pos;
    int i, j;
    int n= N_birds+n_drones;
    for (i=0;i<N_birds;i++) {
        l_pos[i]+= l_speed_prec[i]; //dt=1 
        Imp Fsc {.x= 2*g*(v0-l_speed_prec[i]),.y=0,.z=0};//linear correction
       // Imp Fsc {.x= (8*g/pow(v0,6))*pow((v0*v0-l_speed_prec[i]*l_speed_prec[i]),3),.y=0,.z=0};//marginal speed correction
        Imp Fint {0,0,0};
        Imp Frep {0,0,0};
        for (j=0;j<n;j++) {
       	  Rot angles = l_pos_prec[i] <<l_pos_prec[j];
       	  int M =1;//number of interacting neighbours
            if (t_dist[i][j]<rc && i!=j && angles.phi()<M_PI/2 && angles.phi()>(-M_PI/2)) {
            	 M+=1;
                Fint += -J*Imp{l_speed_prec[i]-l_speed_prec[j]*cos(angles.phi())*sin(angles.theta()),
                -l_speed_prec[j]*sin(angles.theta())*sin(angles.phi()),-l_speed_prec[j]*cos(angles.theta())};
                Frep = g0*(
                			pow(l0/sqrt(t_dist[i][j]), 3)
                		    -l0*l0/t_dist[i][j])
                		*(l_pos_prec[i]-l_pos_prec[j]);
            }
            Fint=1.0/M*Fint;
            Frep=1.0/M*Frep;
        }
        Imp noise = Imp{gauss(),gauss(),gauss()};
        Imp upd_spe = Frep +Fsc+Fint+Imp{l_speed[i],0,0} + 0*noise; //dt =1
        l_speed[i] = !(upd_spe);
        l_pos[i] ^ upd_spe.direction();
        if (l_speed[i]> 0.01) {l_speed[i] = 0.01;}
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));
    }
    for (i=N_birds;i<n;i++) {
        l_pos[i]+= l_speed[i];
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));
    }
    for (i=N_birds;i<n;i++) {
    l_pos[i]+= l_speed[i];
    l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
    l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*1500, l_pos[i].y()*1200));
    }
    update_dist();
}
void Flock::store_data(int iteration,
                int  N_dt,
                int  proj,
                bool tp,
                bool is_drone,
                std::ofstream& file){
    if (iteration==0){
                      file << "time";
                      file << ",boid";
                      file << ",speed";
                      file << ",x";
                      file << ",y";
                      file << ",z";
        if (tp){      file << ",theta";
                      file << ",phi";  }
        if (is_drone){file << ",drone";}
                      file << endl;
    }
    if (iteration% N_dt==0){
        int i;
        for (i=0; i<N_birds+n_drones; i++){
                          file        << iteration;
                          file << "," << i;
                          file << "," << l_speed[i];
                          file << "," << l_pos[i].x(proj);
                          file << "," << l_pos[i].y(proj);
                          file << "," << l_pos[i].z(proj);
            if (tp){      file << "," << l_pos[i].t(proj);
                          file << "," << l_pos[i].p(proj);}
            if (is_drone){file        << (i>= N_birds);}
                          file << endl;
}   }       }

