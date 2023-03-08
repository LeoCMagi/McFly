#include<iostream>
#include "Flock.h"
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1900, 1600), "BOIDS");
	window.setFramerateLimit(30);
    Flock flock_piaf (100,0,1,0,0);
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
	while (window.isOpen()){
		etape+=1;
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
		
		flock_piaf.draw(window);
        //flock_piaf.draw(window);
		window.display();
}
	return 0;
}
