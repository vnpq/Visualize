#pragma once
#include "Style.h"

class LinkedListNode {
public:
	LinkedListNode() {};
	LinkedListNode(sf::Vector2f pos, int x);
	void create(sf::Vector2f pos, int x);
	void setPosition(sf::Vector2f pos);
	void setValue(int x);
	void setState(std::string st);
	void hightlight(sf::Color color);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::CircleShape circle;
	sf::Text text;
	sf::Text state;
};