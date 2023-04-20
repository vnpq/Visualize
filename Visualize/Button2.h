#pragma once
#include "Style.h"


class Button2 {
public:
	void init(sf::Vector2f pos, int i);
	bool handleEvent(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);

	enum ButtonState {
		Normal = 0,
		Hovered = 1,
		Pressed = 2
	};

	int state = Normal;
	sf::Sprite s;
};

