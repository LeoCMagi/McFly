#include<iostream>
#include "Flock.h"
#include <cmath>
#include<fstream>
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1900, 1600), "BOIDS");
	window.setFramerateLimit(30);
	/*int N=30;
	std::vector<real_t> speed_birds= std::vector<real_t> (N,0.005);;
	std::vector<pos> pos_birds=std::vector<pos> (N,pos(Imp{0,0,0}, Rot(0,0)));
	int p=0;
	for(int k=0;k<N;k++){
		if(p==N){p=0;}
		p+=1;
		pos_birds[k]=pos(Imp {k*10.0/N*1.0,p*10.0/N*1.0,k/N*1.0}, Rot (0.5*M_PI,M_PI));
		}
	Flock flock_piaf (speed_birds,pos_birds,0.0001,0.0551,0.007,0.00001);*/
	
	
	
	
	int nb_drones = 3;
	std::vector<real_t> speed_drones(nb_drones, 0.01);
	std::vector<pos> pos_drones (nb_drones, pos(Imp{0.,0.,0}, Rot(M_PI/2,0)));
	int k;
	for (k=0;k<nb_drones;k++) {
		pos_drones[k] = pos(Imp{1.0*k/nb_drones,0.5,0},Rot(M_PI/2,0));
	}
	//pos_drones[0] = pos(Imp{0.4,0.4,0}, Rot(0,0));
	
     Flock flock_piaf (400,0.005,speed_drones,pos_drones);//int n_,real_t J_, real_t v0_, real_t rc_, real_t g_
     flock_piaf.set_parameters (1.1,1.551,0.007,0.00001,0.0007,0.002);//real_t J_, real_t v0_, real_t rc_,real_t g_,l0,g0)
     
     flock_piaf.set_parameters (0.06,1.551,0.007,0.00001,0.0002,0.02);
     //flock_piaf.set_parameters (1.0,0.005,0.1,0.01,0.01,1.0);
     
     //std::vector<real_t> speed_birds (3,0.02);
	//std::vector<pos>pos_birds;
	//pos_birds.push_back(pos(Imp{0,0,0},Rot(0,0)));
	//pos_birds.push_back(pos(Imp{0.5,0.5,0},Rot(0,M_PI/4)));
	//pos_birds.push_back(pos(Imp{0.3,0.3,0},Rot(0,0)));
	//Flock flock_piaf (speed_birds, pos_birds, 0, 0.02, 0,0.02);
	//std::vector<pos> l_piafs = flock_piaf.pos_boids();
	int i;
	int j;
	/*for (i=0;i<3;i++) {
		cout << "posi.x() " << l_piafs[i].x() << " " << l_piafs[i].y() << endl;
	}
	cout<<"xgen "<<l_piafs[0].x()<<" "<<l_piafs[0].y()<<endl;
	cout<<"xgen "<<l_piafs[1].x()<<" "<<l_piafs[1].y()<<endl;
	cout<<"xgen "<<l_piafs[2].x()<<" "<<l_piafs[2].y()<<endl;
	for (i=0;i<3;i++) {
		cout << "d_ijgen ";
		for (j=0;j<i+1;j++) {
			cout << flock_piaf.tab_dist()[i][j] << " ";
		}
		cout << endl;
	}*/
	int etape=0;
	ofstream history;
	history.open("Analysis/data.csv", std::ofstream::out);
	while (window.isOpen()){
		if (history.is_open()) {
    std::cout << "Successfully opened data file" << std::endl;
} else {
    std::cout << "Failed to open data file" << std::endl;
}
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
		/*for (i=0;i<3;i++) {
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
		}*/
		
		flock_piaf.draw(window);
		window.display();
}
	return 0;
}
