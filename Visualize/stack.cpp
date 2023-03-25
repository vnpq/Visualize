#include "home.h"

void Stack(sf::RenderWindow& window)
{
	//create a button to back to home page
	Button home;
	home.init(sf::Vector2f(1670.f, 800.f), "HOME");

	//create a sidebar
	sf::RectangleShape sidebar;
	sidebar.setFillColor(Style::darkBlue);
	sidebar.setSize(sf::Vector2f(380.f, 1080.f));
	sidebar.setPosition(sf::Vector2f(0.f, 0.f));

	//Print out the name of the data structure
	sf::Text name;
	name.setString("Stack:");
	name.setFillColor(sf::Color::Black);
	name.setFont(Style::font2);
	name.setCharacterSize(60);
	name.setPosition(sf::Vector2f(400.f, 8.f));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (home.handleEvent(window, event)) return;
		}
		window.clear(sf::Color::White);
		window.draw(sidebar);
		window.draw(name);
		
		home.draw(window);
		window.display();
	}
}