#include<iostream>
#include "Flock.h"
#include "SFML/Graphics.hpp"
void Flock::update_dist() {
    int i, j;
    for (i=0;i<n;i++) {
        t_dist[i][i]=0;
        for (j=0;j<i;j++) {
            t_dist[i][j] = (l_birds[i].posi() | l_birds[j].posi());
        }
    }
}
Flock::Flock (int n_) {
    n = n_;
    texture.loadFromFile("oiseau.png");
    //l_birds = std::vector<boids>(n_,boids(texture));
    l_birds.reserve(n*sizeof(boids));
    t_dist = std::vector<std::vector<real_t>> (n_,std::vector<real_t> (n_));
    //l_sprites = std::vector<sf::Texture> (n_);
    int i;
    for (i=0;i<n_;i++) {
        l_birds.push_back(boids(texture));

        /*
        l_sprites[i].setTexture(texture);
        l_sprites[i].setColor(sf::Color(255, 255, 255, 128));//color,opacity 
        l_sprites[i].setOrigin(sf::Vector2f(texture.getSize().x/2,texture.getSize().y/2));//to translate and rotate frm the center of the sprite 
        l_sprites[i].setScale(0.02f,0.02f);//scale of the boid; 
        l_sprites[i].setPosition(sf::Vector2f(position.x()*1500, position.y()*1200));//initial position of the boid} 
        l_sprites[i].setRotation(0.f);//initial angle of the boid
        */
    }
    update_dist();
}

void Flock::draw(sf::RenderWindow& window) {
    int i;
    for (i=0;i<n;i++) {
        l_birds[i].draw(window);
    }
}

void store_data(int& iteration,
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
    if (iteration%N_dt==0){
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
    }