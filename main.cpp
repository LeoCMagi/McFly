#include<iostream>
#include "Boids.h"
using namespace std;
int main (){
	sf::RenderWindow window(sf::VideoMode(1900, 1600), "BOIDS");
	window.setFramerateLimit(30);
	sf::Texture texture;
	texture.loadFromFile("oiseau.png");
	boids piaf = boids(texture);
	boids piaf2 = boids(texture);
	boids piaf3 = boids(texture);
	/*cout<<"x "<<piaf.x<<" "<<piaf.y<<endl;
	cout<<"x "<<piaf2.x<<" "<<piaf2.y<<endl;
	cout<<"x "<<piaf3.x<<" "<<piaf3.y<<endl;*/
	
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
		/*cout<<"pos: "<<piaf.posi().x(1)<<" "<<piaf.posi().y(1)<<"impulse: "<<piaf.impulsi().x<<endl;
		cout<<"pos: "<<piaf2.posi().x(1)<<" "<<piaf2.posi().y(1)<<"impulse: "<<piaf2.impulsi().x<<endl;
		cout<<"pos: "<<piaf3.posi().x(1)<<" "<<piaf3.posi().y(1)<<"impulse: "<<piaf3.impulsi().x<<endl;*/
		piaf2.sprite.rotate(3.f);
		piaf3.sprite.rotate(-3.f);
		
		//piaf.sprite.move(sf::Vector2f(1,1));//translation of the sprite
		//piaf2.sprite.move(sf::Vector2f(3,1));
		//piaf3.sprite.move(sf::Vector2f(3,3));
		




		//cout << piaf.sprite.getRotation()<<endl;
		//cout<<piaf2.sprite.getRotation()<<endl;
		//cout<<piaf3.sprite.getRotation()<<endl;
		piaf.draw(window);
		piaf2.draw(window);
		piaf3.draw(window);
		window.display();
}
		cout<< piaf.posi().p()<<endl;
		cout<< piaf.posi().t()<<endl;
		cout<< piaf2.posi().p()<<endl;
		cout<< piaf3.posi().p()<<endl;
		cout<< " getrot" << endl;
		cout << piaf.sprite.getRotation()<<endl;
		cout<<piaf2.sprite.getRotation()<<endl;
		cout<<piaf3.sprite.getRotation()<<endl;
	return 0;
}
