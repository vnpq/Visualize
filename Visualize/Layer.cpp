#include "Layer.h"
#include <iostream>

void Layer::addArray(sf::Vector2f pos, std::vector<int> values)
{
	int size = 60;
	for (int i = 0; i < values.size(); ++i) {
		sf::Vector2f posi = pos + sf::Vector2f(size * i, 0);
		arrays.push_back(ArrayNode(posi, values[i]));
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

