#include<iostream>
#include "Boids.h"
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1500, 1200), "BOIDS");
	window.setFramerateLimit(30);
	boids piaf = boids();
	boids piaf2 = boids();
	boids piaf3 = boids();
	
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
		piaf.sprite.rotate(0.f);//rotation of the sprite
		cout<<"pos: "<<piaf.posi().x(1)<<"impulse: "<<piaf.impulsi().x<<endl;
		cout<<"pos: "<<piaf2.posi().x(1)<<"impulse: "<<piaf2.impulsi().x<<endl;
		cout<<"pos: "<<piaf3.posi().y(1)<<"impulse: "<<piaf3.impulsi().x<<endl;
		piaf2.sprite.rotate(3.f);
		piaf3.sprite.rotate(40.f);
		piaf.sprite.move(sf::Vector2f(1,1));//translation of the sprite
		piaf2.sprite.move(sf::Vector2f(3,1));
		piaf3.sprite.move(sf::Vector2f(3,3));
		





		piaf.draw(window);
		piaf2.draw(window);
		piaf3.draw(window);
		window.display();
}
	return 0;
}
