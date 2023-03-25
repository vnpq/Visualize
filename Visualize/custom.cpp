#include "home.h"

void Custom(sf::RenderWindow& window)
{
	//create a button to back to home page
	Button home;
	home.init(sf::Vector2f(1670.f, 800.f), "HOME");

	//create a sidebar
	sf::RectangleShape sidebar;
	sidebar.setFillColor(Style::darkBlue);
	sidebar.setSize(sf::Vector2f(380.f, 1080.f));
	sidebar.setPosition(sf::Vector2f(0.f, 0.f));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (home.handleEvent(window, event)) return;
		}
		window.clear(sf::Color::White);
		window.draw(sidebar);

		home.draw(window);
		window.display();
	}
}