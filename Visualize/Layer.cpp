#include "Layer.h"
#include <iostream>

void Layer::addArray(sf::Vector2f pos, std::vector<int> values)
{
	int size = 60;
	arrays.clear();
	for (int i = 0; i < values.size(); ++i) {
		sf::Vector2f posi = pos + sf::Vector2f(size * i, 0);
		arrays.push_back(ArrayNode(posi, values[i]));
	}
}

void Layer::addList(sf::Vector2f pos, std::vector<int> values)
{
	int size = 100;
	for (int i = 0; i < values.size(); ++i) {
		sf::Vector2f posi = pos + sf::Vector2f(size * i, 0);
		lists.push_back(LinkedListNode(posi, values[i]));
	}
	if (lists.size() != 0) lists[0].setHead();
	for (int i = 1; i < values.size(); ++i) {
		arrows.push_back(Arrow());
		arrows.back().create(lists[i - 1], lists[i], 1);
	}
}

void Layer::draw(sf::RenderWindow& window)
{
	for (ArrayNode& x : arrays) {
		x.draw(window);
	}


	for (LinkedListNode& x : lists) {
		x.draw(window);
	}

	for (Arrow& x : arrows) {
		x.draw(window);
	}


	for (sf::Text & x : texts) {	
		window.draw(x);
	}
}

