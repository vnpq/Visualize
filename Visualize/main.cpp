#include "Style.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualiztion");

	//Button butt;
	//butt.init(sf::Vector2f(100, 100), "PQ");
	Textbox box1;
	box1.init(sf::Vector2f(200.f, 200.f));
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			
			//butt.handleEvent(window, event);
			box1.handleEvent(window, event);
		}

		window.clear(Style::backgroundColor);

		//butt.draw(window);
		box1.draw(window);

		window.display();

	}

	return 0;
}