#include "linkedList.h"


void LinkedL(sf::RenderWindow& window)
{
	LL a;
	a.setLayout();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (a.home.handleEvent(window, event)) return;
		}
		window.clear(sf::Color::White);
		a.draw(window);
		window.display();
	}
}