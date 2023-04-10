#pragma once
#include "Style.h"

class Button;

class Textbox {
public:

	sf::Text text;
	sf::RectangleShape box;


	void init(sf::Vector2f pos);
	void handleEvent(sf::RenderWindow& window, sf::Event event, std::string& output, Button& OK);
	void draw(sf::RenderWindow& window);
	
};

void input(sf::RenderWindow& window, std::string& st, std::string text, sf::Vector2f pos,
	Button& home, Button& cancel);