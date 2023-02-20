#include<iostream>
#include "../Boids.h"
#include "Flock.h"
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1600, 1600), "BOIDS");
	window.setFramerateLimit(30);
    Flock flock_piaf (3);
    std::vector<boids> l_piafs = flock_piaf.l_boids();
	cout<<"x "<<l_piafs[0].x<<" "<<l_piafs[0].y<<endl;
	cout<<"x "<<l_piafs[1].x<<" "<<l_piafs[1].y<<endl;
	cout<<"x "<<l_piafs[2].x<<" "<<l_piafs[2].y<<endl;
	
	while (window.isOpen()){
		window.clear(sf::Color::Yellow);
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			}
			/*switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				//default:
				//	break; 
				}}*/
		window.clear(sf::Color::Yellow);





		int k; 
        for (k=0;k<3;k++) {
            window.draw(l_piafs[k].sprite);
        }
        //flock_piaf.draw(window);
		window.display();
}
	return 0;
}
