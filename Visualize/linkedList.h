#pragma once

#include "Style.h"
#include "home.h"
class LinkedListNode;

void LinkedL(sf::RenderWindow& window);

class LinkedList {
public:
	void displayInit();
	void init(sf::RenderWindow& window);
	void randomInit();
	void emptyInit();
	void customInit(sf::RenderWindow& window, Button& cancel);

	void displayUpdate(int idx, int num);
	void update(sf::RenderWindow& window);

	void displayAdd(int idx, int num);
	void add(sf::RenderWindow& window);

	void displayRemove(int idx);
	void remove(sf::RenderWindow& window);

	void displaySearch(int num);
	void search(sf::RenderWindow& window);

	//layout include home butt (back to home page), sidebar and name of DS
	Button home;
	sf::RectangleShape sidebar;
	sf::Text name;

	//create a button for each tool
	Button initB;
	Button updateB;
	Button addB;
	Button removeB;
	Button searchB;

	int n = 0;
	bool finished = 0;
	std::vector<int> values;

	void setLayout() {
		home.init(sf::Vector2f(1670.f, 800.f), "HOME");

		sidebar.setFillColor(Style::darkBlue);
		sidebar.setSize(sf::Vector2f(380.f, 1080.f));
		sidebar.setPosition(sf::Vector2f(0.f, 0.f));

		name.setString("Linked List:");
		name.setFillColor(sf::Color::Black);
		name.setFont(Style::font2);
		name.setCharacterSize(60);
		name.setPosition(sf::Vector2f(400.f, 8.f));

		initB.init(sf::Vector2f(100.f, 100.f), "Initialize");
		updateB.init(sf::Vector2f(100.f, 200.f), "Update");
		addB.init(sf::Vector2f(100.f, 300.f), "Add");
		removeB.init(sf::Vector2f(100.f, 400.f), "Remove");
		searchB.init(sf::Vector2f(100.f, 500.f), "Search");
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sidebar);
		window.draw(name);
		home.draw(window);
		initB.draw(window);
		addB.draw(window);
		updateB.draw(window);
		removeB.draw(window);
		searchB.draw(window);
		Display::draw(window);
	}
};