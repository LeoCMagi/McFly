#include<iostream>
#include "Flock.h"
#include "SFML/Graphics.hpp"
#include <cmath>
#include<random>
#include<chrono>
using namespace std;

int WIDTH = 1600;
int HEIGHT = 1300;

/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                        XXX
    XXX     Initialisation     XXX
    XXX                        XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator (seed); 
std::uniform_real_distribution<real_t> distribution(2.,360.);
auto dice = std::bind (distribution,generator);
// normal distribution 
std::normal_distribution<real_t> normal(0.,0.1);
auto gauss = std::bind (normal,generator);


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                      XXX
    XXX     Constructors     XXX
    XXX                      XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
void Flock::set_Intensities (real_t I_rep_, real_t I_all_, real_t I_att_, real_t I_noi_){
    I_rep=I_rep_; I_all=I_all_; I_att=I_att_; I_noi=I_noi_;
}

void Flock::set_Radii (real_t r_rep_, real_t r_all_, real_t r_att_){
    r_rep=r_rep_; r_all=r_all_; r_att=r_att_;
}

void Flock::set_Speed (real_t v0_){
    v0=v0_;
}

Flock::Flock (int N_birds_,real_t vi_birds,const std::vector<real_t>& speed_drones,const std::vector<pos>& pos_drones){
    N_birds=N_birds_;
    n_drones= speed_drones.size();
    I_all=0;
    v0=0;
    r_rep=0;
    I_att=0;
    r_all=0;
    I_rep=0;
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
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);//initial angle of the boid
    }
    for (i=N_birds; i<n;i++) {
        l_speed[i] =speed_drones[i-N_birds_];
        l_pos[i] = pos_drones[i-N_birds_];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(118, 56, 159, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.09f,0.09f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));//initial position of the boid} 
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
    I_all=0;
    v0=0;
    r_rep=0;
    I_att=0;
    r_all=0;
    I_rep=0;
    texture.loadFromFile("oiseau.png");
    int i;
    for (i=0;i<N_birds;i++) {
    	   l_pos[i] = pos_birds[i];
        l_speed[i] = speed_birds[i];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(255, 255, 255, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));//initial position of the boid} 
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
    }
        for (i=N_birds;i<n;i++) {
        l_pos[i] = pos_drones[i-N_birds];
        l_speed[i] = speed_drones[i-N_birds];
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(118, 56, 159, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));//initial position of the boid
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


/*XXXXXXXXXXXXXXXXXXXXXXXXXX
  XXX                    XXX
  XXX     Old Update     XXX
  XXX                    XXX
  XXXXXXXXXXXXXXXXXXXXXXXXXX
*/

void Flock::old_update_flock() {
    l_speed_prec = l_speed;
    l_pos_prec = l_pos;
    int i, j;
    int n= N_birds+n_drones;
    for (i=0;i<N_birds;i++) {
        l_pos[i]+= l_speed_prec[i]; //dt=1 
        Imp Fsc {.x= 2*I_att*(v0-l_speed_prec[i]),.y=0,.z=0};//linear speed correction
       // Imp Fsc {.x= (8*I_att/pow(v0,6))*pow((v0*v0-l_speed_prec[i]*l_speed_prec[i]),3),.y=0,.z=0};//marginal speed correction if another model of speed correction is needed
        Imp Fint {0,0,0};
        Imp Frep {0,0,0};
        for (j=0;j<n;j++) {
       	  Rot angles = l_pos_prec[i] <<l_pos_prec[j];
       	  int M =1;//number of interacting neighbours
            if (t_dist[i][j]<r_rep && i!=j ) {//&& angles.phi()<M_PI/2 && angles.phi()>(-M_PI/2) if a view angle is needed
            	 M+=1;
                Fint += -I_all*Imp{l_speed_prec[i]-l_speed_prec[j]*cos(angles.phi())*sin(angles.theta()),
                -l_speed_prec[j]*sin(angles.theta())*sin(angles.phi()),-l_speed_prec[j]*cos(angles.theta())};
                Frep = I_rep*(
                			pow(r_all/sqrt(t_dist[i][j]), 3)
                		    -r_all*r_all/t_dist[i][j])
                		*(l_pos_prec[i]-l_pos_prec[j]);
            }
            Fint=1.0/M*Fint;
            Frep=1.0/M*Frep;
        }
        Imp noise = Imp{gauss(),gauss(),gauss()};
        Imp upd_spe = Frep +Fsc+Fint+Imp{l_speed[i],0,0} + 0*noise; //dt =1, noise shut down right now
        l_speed[i] = !(upd_spe);
        l_pos[i] ^ upd_spe.direction();
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));
    }
    for (i=N_birds;i<n;i++) {
        l_pos[i]+= l_speed[i];
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));
    }
    update_dist();
}

/*  XXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX                    XXX
    XXX     The Forces     XXX
    XXX                    XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXX
*/

Imp Flock::get_F (int i){
    int state = this->boid_state(i);
    Imp F;
    if (state==0) F = F_rep(i);
    if (state==1) F = F_all(i);
    if (state> 1) F = F_att(i);
    // Noise
    F+=(v0*I_noi/sqrt(3))* Imp{gauss(),gauss(),gauss()};
    return F + Imp{v0, 0, 0};
}

Imp Flock::F_rep(int i){
    int j;
    int n= N_birds+n_drones;
    int avg=0;
    Imp F {0,0,0};
    for (j=0; j<n; j++){if (i!=j && t_dist[i][j]<r_rep){//Calcul de la force
        F += (v0/t_dist[i][j])*(l_pos_prec[j] - l_pos_prec[i]);
        avg+=1;
    }}
    return (-I_rep/avg)*F;
}

Imp Flock::F_all(int i){
    int j;
    int n= N_birds+n_drones;
    int avg=0;
    Imp F {0,0,0};
    Imp F_temp;
    for (j=0; j<n; j++){if (i!=j && t_dist[i][j]<r_all){//Calcul de la force
        F_temp = Imp::u_angle(l_pos_prec[i] <<l_pos_prec[j]);
        F     += F_temp;
        avg+=1;
    }}
    return (I_all*v0/avg)*F;
}


Imp Flock::F_att(int i){
    int j,best_j;
    int n= N_birds+n_drones;
    real_t d;

    // Initialisation for the nearest neighbor
    if (n==1) return {0,0,0};
    if (i==0) {d=t_dist[0][1]; best_j=1;}
    if (i!=0) {d=t_dist[0][i]; best_j=0;}

    // searching for the nearest neighbor
    for (j=0; j<n; j++){if(i!=j && t_dist[i][j]<d){
        best_j = j;
        d = t_dist[i][j];
    }}
    return (v0*I_att/d)*(l_pos_prec[best_j]-l_pos_prec[i]);
}


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXX
    XXX                     XXX
    XXX     The Updates     XXX
    XXX                     XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXX
*/

void Flock::update_graphics(){
    int i;
    int n= N_birds+n_drones;
    for (i=0; i<n; i++){
        l_sprites[i].setRotation(l_pos[i].p()*180/M_PI);
        l_sprites[i].setPosition(sf::Vector2f(l_pos[i].x()*0.9*WIDTH, l_pos[i].y()*0.9*HEIGHT));
    }
}

int Flock::boid_state(int i){
    int j;
    bool has_neighbor = false;
    int n= N_birds+n_drones;
    for (j=0;j<n;j++) {
        if (i!=j                      &&
            t_dist[i][j]<r_rep*r_rep) return 0;
        if (i!=j                      &&
            t_dist[i][j]<r_all*r_all  &&
            is_visible(i,j))          has_neighbor = true;
    }
    if (has_neighbor) return 1;
    return 2;
}

void Flock::update_flock() {
    int i;
    int n= N_birds+n_drones;
    Imp F;
    l_pos_prec = l_pos;
    //l_speed_prec = l_speed;    we work at constant speed
    for (i=0; i<N_birds; i++){
        F = get_F (i);
        l_pos[i] ^ F.direction(); // Action of the force
        l_pos[i] += v0;
        }
    for (i= N_birds; i<n; i++) {
        l_pos[i]+= l_speed[i];
    }
    update_dist();

    // And now, the graphic update
    this->update_graphics();
}

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
            if (is_drone){file << "," << (i>= N_birds);}
                          file << endl;
}   }       }

