#include<iostream>
#include "Flock.h"
#include <cmath>
#include<fstream>
using namespace std;
int main (){
/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                              XXX
    XXX     Constantes Physiques     XXX
    XXX                              XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
	real_t J=0.005;
	real_t v0=0.01;
	real_t rc=0.01;
	real_t g=0.005;
	real_t l0=0.1;
	real_t g0=g;

	int N_Boids = 30;
	int nb_drones = 0;


/*  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	XXX                        XXX
    XXX     Initialisation     XXX
    XXX                        XXX
    XXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
*/
	sf::RenderWindow window(sf::VideoMode(1900, 1600), "BOIDS");
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
    Flock flock_piaf (N_Boids, J, speed_drones, pos_drones);
    flock_piaf.set_parameters (J,v0,rc,g,l0,g0);
	


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
