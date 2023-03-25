#include<iostream>
#include "Flock.h"
#include <cmath>
#include<fstream>
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1900, 1600), "BOIDS");
	window.setFramerateLimit(30);
	int nb_drones = 20;
	std::vector<real_t> speed_drones(nb_drones, 0.01);
	std::vector<pos> pos_drones (nb_drones, pos(Imp{0.,0.,0}, Rot(M_PI/2,0)));
	int k;
	for (k=0;k<nb_drones;k++) {
		pos_drones[k] = pos(Imp{1.0*k/nb_drones,0.5,0},Rot(M_PI/2,0));
	}
	pos_drones[1] = pos(Imp{0.4,0.4,0}, Rot(0,0));
    Flock flock_piaf (200, 0.005 ,speed_drones,pos_drones);
	flock_piaf.set_parameters(0.3,0.0521,0.07,0.01,0.05,0.03); // J, v0, rc, g, l0, g0
     //std::vector<real_t> speed_birds (3,0.02);
	//std::vector<pos> pos_birds;
	//pos_birds.push_back(pos(Imp{0,0,0},Rot(0,0)));
	//pos_birds.push_back(pos(Imp{0.5,0.5,0},Rot(0,M_PI/4)));
	//pos_birds.push_back(pos(Imp{0.3,0.3,0},Rot(0,0)));
	//Flock flock_piaf (speed_birds, pos_birds, 0, 0.02, 0,0.02);
	std::vector<pos> l_piafs = flock_piaf.pos_boids();
	int i;
	for (i=0;i<3;i++) {
		cout << "posi.x() " << l_piafs[i].x() << " " << l_piafs[i].y() << endl;
	}
	cout<<"xgen "<<l_piafs[0].x()<<" "<<l_piafs[0].y()<<endl;
	cout<<"xgen "<<l_piafs[1].x()<<" "<<l_piafs[1].y()<<endl;
	cout<<"xgen "<<l_piafs[2].x()<<" "<<l_piafs[2].y()<<endl;
	int j;
	for (i=0;i<3;i++) {
		cout << "d_ijgen ";
		for (j=0;j<i+1;j++) {
			cout << flock_piaf.tab_dist()[i][j] << " ";
		}
		cout << endl;
	}
	int etape=0;
	ofstream history;
	history.open("data.csv", std::ofstream::out);
	while (window.isOpen()){
		flock_piaf.store_data(etape, 30, 0, false, false, history);
		cout << "etape " << etape << endl;
		window.clear(sf::Color::Yellow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			}
		window.clear(sf::Color::Yellow);
		flock_piaf.update_flock();
		for (i=0;i<3;i++) {
		cout << "posi.x() " << l_piafs[i].x() << " " << l_piafs[i].y() << endl;
	}
		cout<<"x "<<l_piafs[0].x()<<" "<<l_piafs[0].y()<<endl;
		cout<<"x "<<l_piafs[1].x()<<" "<<l_piafs[1].y()<<endl;
		cout<<"x "<<l_piafs[2].x()<<" "<<l_piafs[2].y()<<endl;
		for (i=0;i<3;i++) {
			cout << "d_ij ";
			for (j=0;j<i+1;j++) {
				cout << flock_piaf.tab_dist()[i][j] << " ";
			}
			cout << endl;
		}
		etape+=1;
		flock_piaf.draw(window);
		window.display();
}
	return 0;
}
