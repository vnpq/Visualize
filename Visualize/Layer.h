#pragma once
#include "Style.h"
#include "Arrow.h"
#include "ArrayNode.h"
#include "LLNode.h"

class ArrayNode;
class Arrow;
class LinkedListNode;

class Layer {
public:
	std::vector<ArrayNode> arrays;
	std::vector<LinkedListNode> lists;
	std::vector<Arrow> arrows;
	std::vector<sf::Text> texts;

	void addArray(sf::Vector2f pos, std::vector<int> values);
	void addList(sf::Vector2f pos, std::vector<int> values);
	void draw(sf::RenderWindow& window);


};

