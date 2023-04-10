#pragma once
#include "Style.h"

class Source {
public:
	std::vector<sf::Text> code;
	sf::RectangleShape rect;
	int highlighted = 0;
	void highlight(int row);
	void add(std::vector<std::string> st);
	void draw(sf::RenderWindow& window);
	void clear();
};