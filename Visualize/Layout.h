#pragma once
#include "Style.h"

class layout {
public:
	//create a button to back to home page
	Button home;


	//create a sidebar
	sf::RectangleShape sidebar;

	//Name of the data structure
	sf::Text name;


	void setLayout() {
		home.init(sf::Vector2f(1670.f, 800.f), "HOME");

		sidebar.setFillColor(Style::darkBlue);
		sidebar.setSize(sf::Vector2f(380.f, 1080.f));
		sidebar.setPosition(sf::Vector2f(0.f, 0.f));

		name.setFillColor(sf::Color::Black);
		name.setFont(Style::font2);
		name.setCharacterSize(60);
		name.setPosition(sf::Vector2f(400.f, 8.f));
	};

	void drawLayout(sf::RenderWindow& window) {
		home.draw(window);
		window.draw(sidebar);
		window.draw(name);
	};
};