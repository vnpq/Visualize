#pragma once
#include "Style.h"


void StaticArray(sf::RenderWindow& window);
class SArray {
public:
    void init(sf::RenderWindow& window);
    void add(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    void remove(sf::RenderWindow& window);
    void search(sf::RenderWindow& window);

	//layout include home butt (back to home page), sidebar and name of DS
    Button home;
    sf::RectangleShape sidebar;
    sf::Text name;

	//create a button for each tool
	Button initB;
	Button addB;
	Button updateB;
	Button removeB;
	Button searchB;

    void setLayout() {
		home.init(sf::Vector2f(1670.f, 800.f), "HOME");

		sidebar.setFillColor(Style::darkBlue);
		sidebar.setSize(sf::Vector2f(380.f, 1080.f));
		sidebar.setPosition(sf::Vector2f(0.f, 0.f));

		name.setString("Static Array:");
		name.setFillColor(sf::Color::Black);
		name.setFont(Style::font2);
		name.setCharacterSize(60);
		name.setPosition(sf::Vector2f(400.f, 8.f));

        initB.init(sf::Vector2f(100.f, 100.f), "Initialize");
		addB.init(sf::Vector2f(100.f, 200.f), "Add");
		updateB.init(sf::Vector2f(100.f, 300.f), "Update");
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

	}
};
