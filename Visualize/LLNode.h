#pragma once
#include "Style.h"

class LinkedListNode {
public:
	LinkedListNode() {};
	LinkedListNode(sf::Vector2f pos, int x);
	void create(sf::Vector2f pos, int x);
	void hightlight(sf::Color color);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::CircleShape circle;
	sf::Text text;
};