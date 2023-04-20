#pragma once
#include "Style.h"


class Button {
public: 
	const void init(sf::Vector2f pos, const std::string text);
	bool handleEvent(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow &window);

	enum ButtonState {
		Normal = 0,
		Hovered = 1,
		Pressed = 2
	};

	int state = Normal;
	sf::Font bFont;
	sf::Text buttonText;
	sf::RectangleShape normalRect, hoveredRect, pressedRect;
};

