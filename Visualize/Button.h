#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Button {
public: 
	const void init(sf::Vector2f pos, const std::string text);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow &window);

	enum ButtonState {
		Normal = 0,
		Hovered = 1,
		Pressed = 2
	};

	int state = Normal;
	sf::Text buttonText;
	sf::Font font;
	sf::RectangleShape normalRect, hoveredRect, pressedRect;
};