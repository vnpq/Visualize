#include "Button2.h"

void Button2::init(sf::Vector2f pos, int i)
{
    s.setTexture(Style::state[i]);
    s.setPosition(pos);
    s.setOrigin(0, s.getLocalBounds().height / 2.0);
    s.setScale(50 / s.getLocalBounds().width, 50 / s.getLocalBounds().height);
}

bool Button2::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	//get the position of the mouse
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
	//check if the mouse is inside the button
	if (s.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
		//Yeah! mouse is inside the button
		switch (event.type) {
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
				state = Pressed;
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
				if (state == Pressed)  state = Hovered;
			break;
		case sf::Event::MouseMoved:
			if (state != Pressed) state = Hovered;
			break;
		}
	}
	else {
		//Opps! Mouse is outside the button
		state = Normal;
	}
	return (state == Pressed);
}

void Button2::draw(sf::RenderWindow& window)
{
	window.draw(s);
}