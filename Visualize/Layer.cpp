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
	int size = 120;
	lists.clear();
	arrows.clear();
	for (int i = 0; i < values.size(); ++i) {
		sf::Vector2f posi = pos + sf::Vector2f(size * i, 0);
		lists.push_back(LinkedListNode(posi, values[i]));
	}
	if (lists.size() != 0) lists[0].setState("head");
	for (int i = 1; i < values.size(); ++i) {
		arrows.push_back(Arrow());
		arrows.back().create(lists[i - 1], lists[i]);
	}
}

void Layer::addDList(sf::Vector2f pos, std::vector<int> values)
{
	int size = 120;
	lists.clear();
	arrows.clear();
	arrow2.clear();
	for (int i = 0; i < values.size(); ++i) {
		sf::Vector2f posi = pos + sf::Vector2f(size * i, 0);
		lists.push_back(LinkedListNode(posi, values[i]));
	}
	if (lists.size() != 0) lists[0].setState("head");
	if (lists.size() > 1) lists.back().setState("tail");
	if (lists.size() == 1) lists[0].setState("head/tail");

	for (int i = 1; i < values.size(); ++i) {
		arrows.push_back(Arrow());
		arrows.back().create(lists[i - 1], lists[i]);
		arrow2.push_back(Arrow());
		arrow2.back().create(lists[i], lists[i - 1]);
	}
}

sf::Vector2f getCNodePos(int n, int i)
{
	sf::Vector2f pos = { 1150, 400 };
	if (n == 1) return pos;

	float r = 200;
	float angle = M_PI / 2 - (M_PI * 2) / n * i;
	float x = 1150 + r * cos(angle);
	float y = 400 - r * sin(angle);

	return {x, y} ;
}

void Layer::addCList(std::vector<int> values)
{
	lists.clear();
	arrows.clear();
	int n = values.size();
	if (n == 0) return;
	for (int i = 0; i < n; ++i) {
		sf::Vector2f posi = getCNodePos(n, i);
		lists.push_back(LinkedListNode(posi, values[i]));
	}
	if (lists.size() != 0) lists[0].setState("first");
	for (int i = 1; i < values.size(); ++i) {
		arrows.push_back(Arrow());
		arrows.back().create(lists[i - 1], lists[i]);
	}
	arrows.push_back(Arrow());
	arrows.back().create(lists[n - 1], lists[0]);
}

void Layer::draw(sf::RenderWindow& window)
{
	for (ArrayNode& x : arrays) {
		x.draw(window);
	}

	for (Arrow& x : arrows) {
		x.draw(window);
	}
	for (Arrow& x : arrow2) {
		x.draw(window);
	}

	for (LinkedListNode& x : lists) {
		x.draw(window);
	}

}



