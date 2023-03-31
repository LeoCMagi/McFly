#include<iostream>
#include "Flock.h"
#include <cmath>
#include<fstream>
using namespace std;

#define WIDTH 1300
#define HEIGHT 700
int main (){
/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                              XXX
    XXX     Constantes Physiques     XXX
    XXX                              XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
	real_t I_all=0.5;
	real_t I_att=0.05;
	real_t I_rep=0.05;
	real_t I_noi=0.;

	real_t v0=0.01;
	real_t r_rep=0.01;
	real_t r_all=0.1;
	real_t r_att=10000;

	int N_Boids = 100;
	int nb_drones = 30;


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                        XXX
    XXX     Initialisation     XXX
    XXX                        XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "BOIDS");
	window.setFramerateLimit(30);
	int etape=0;
	int k;
	ofstream history;
	history.open("Analysis/data.csv", std::ofstream::out);
	std::vector<real_t> speed_drones(nb_drones, v0);
	std::vector<pos> pos_drones (nb_drones, pos(Imp{0.,0.,0}, Rot(M_PI/2,0)));
	for (k=0;k<nb_drones;k++) {
		pos_drones[k] = pos(Imp{1.0*k/nb_drones,0.5,0},Rot(M_PI/2,0));
	}
    Flock flock_piaf (N_Boids, v0, speed_drones, pos_drones);
	
    flock_piaf.set_Intensities (I_rep, I_all, I_att, I_noi);
    flock_piaf.set_Radii       (r_rep, r_all, r_att);
    flock_piaf.set_Speed       (v0);

/*  XXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                   XXX
    XXX     Evolution     XXX
    XXX                   XXX
    XXXXXXXXXXXXXXXXXXXXXXXXX
*/
	while (window.isOpen()){
		flock_piaf.store_data(etape, 30, 0, false, false, history);
		window.clear(sf::Color::Yellow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			}
		window.clear(sf::Color::Yellow);
		etape+=1;
		flock_piaf.update_flock();
		flock_piaf.draw(window);
		window.display();
	}

return 0;
}
