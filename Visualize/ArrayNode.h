#pragma once
#include "Style.h"

class ArrayNode {
public:
	ArrayNode() {};
	ArrayNode(sf::Vector2f pos, int x);
	void create(sf::Vector2f pos, int x);
	void setValue(int x);
	void hightlight(sf::Color color);
	void draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	sf::RectangleShape rect;
	sf::Text text;
};