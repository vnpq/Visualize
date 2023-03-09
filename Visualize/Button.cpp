#include "Button.h"


const void Button::init(sf::Vector2f pos, const std::string text) {
	//setting for the text
	font.loadFromFile("Lexend-Regular.ttf");
	buttonText.setFont(font);
	buttonText.setString(text);
	buttonText.setCharacterSize(25);
	buttonText.setFillColor(sf::Color::Black);
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	buttonText.setPosition(sf::Vector2f(pos.x + 90, pos.y + 35));

	//setting for the rectangle with a rect for each state
	normalRect.setSize(sf::Vector2f(180.f, 70.f));
	normalRect.setFillColor(sf::Color::Cyan);
	normalRect.setPosition(pos);
	
	hoveredRect.setSize(sf::Vector2f(180.f, 70.f));
	hoveredRect.setFillColor(sf::Color::Cyan);
	hoveredRect.setOutlineThickness(1.f);
	hoveredRect.setOutlineColor(sf::Color::Blue);
	hoveredRect.setPosition(pos);

	pressedRect.setSize(sf::Vector2f(180.f, 70.f));
	pressedRect.setFillColor(sf::Color::Blue);
	pressedRect.setPosition(pos);

}

void Button::handleEvent(sf::RenderWindow& window, sf::Event event)
{
	//get the position of the mouse
	sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
	//check if the mouse is inside the button
	if (normalRect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
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
	//Draw the button using the current state
	draw(window);
}

void Button::draw(sf::RenderWindow& window)
{
	if (state == Normal) window.draw(normalRect);
	if (state == Hovered) window.draw(hoveredRect);
	if (state == Pressed) window.draw(pressedRect);
	window.draw(buttonText);
}
