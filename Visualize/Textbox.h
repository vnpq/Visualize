#pragma once
#include "Style.h"


class Textbox {
public:

	enum TextboxState {
		Typable = 0,
		UnTypable = 1
	};
	sf::Text text;
	sf::RectangleShape box;
	
	int state = UnTypable;

	void init(sf::Vector2f pos);
	void handleEvent(sf::RenderWindow& window, sf::Event event, std::string& output);
	void draw(sf::RenderWindow& window);

};