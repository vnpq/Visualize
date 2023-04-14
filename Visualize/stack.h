#pragma once

#include "Style.h"
#include "home.h"
class LinkedListNode;

void Stack(sf::RenderWindow& window);

class StackClass {
public:
	void displayInit();
	void init(sf::RenderWindow& window);
	void randomInit();
	void emptyInit();
	void customInit(sf::RenderWindow& window, Button& cancel);

	void displayPush(int num);
	void push(sf::RenderWindow& window);

	void displayTop();
	void top(sf::RenderWindow& window);

	void displayPop();
	void pop(sf::RenderWindow& window);

	//layout include home butt (back to home page), sidebar and name of DS
	Button home;
	sf::RectangleShape sidebar;
	sf::Text name;

	//create a button for each tool
	Button initB;
	Button pushB;
	Button topB;
	Button popB;

	int n = 0;
	bool finished = 1;
	std::vector<int> values;
	float size = 120;

	void setLayout() {
		home.init(sf::Vector2f(1670.f, 800.f), "HOME");

		sidebar.setFillColor(Style::darkBlue);
		sidebar.setSize(sf::Vector2f(380.f, 1080.f));
		sidebar.setPosition(sf::Vector2f(0.f, 0.f));

		name.setString("Stack:");
		name.setFillColor(sf::Color::Black);
		name.setFont(Style::font2);
		name.setCharacterSize(60);
		name.setPosition(sf::Vector2f(400.f, 8.f));

		initB.init(sf::Vector2f(100.f, 100.f), "Initialize");
		pushB.init(sf::Vector2f(100.f, 200.f), "Push");
		topB.init(sf::Vector2f(100.f, 300.f), "Top");
		popB.init(sf::Vector2f(100.f, 400.f), "Pop");
	}

	void draw(sf::RenderWindow& window) {
		window.draw(sidebar);
		window.draw(name);
		home.draw(window);
		initB.draw(window);
		pushB.draw(window);
		topB.draw(window);
		popB.draw(window);
		Display::draw(window);
	}
};