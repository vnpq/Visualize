#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

enum class ButtonState {
	Normal,
	Pressed,
	Hovered,
	Disabled
};


class Button : public sf::Drawable, public sf::Transformable {
public: 
	ButtonState state;
	
	Button(const std::string& text) {
		
		rect.setSize(sf::Vector2f(200.f, 70.f));
		rect.setFillColor(sf::Color(182, 239, 242));

		// Create the text for the button
		font.loadFromFile("Lexend-Regular.ttf");
		buttonText.setFont(font);
		buttonText.setCharacterSize(25);
		buttonText.setFillColor(sf::Color::Black);
		buttonText.setString(text);

		// Position the text in the center of the button
		sf::FloatRect textBounds = buttonText.getLocalBounds();
		buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		buttonText.setPosition(100.f, 38.f);

		// Position the button
		rect.setPosition(getPosition());

		state = ButtonState::Normal;
	}
	
	void setNormal() {
		rect.setFillColor(sf::Color(182, 239, 242));
	}

	void setPressedColor() {
		rect.setFillColor(sf::Color(68, 84, 145));
	}

	void setHovered() {
		rect.setOutlineThickness(1.f);
		rect.setOutlineColor(sf::Color(68, 84, 145));
	}

	void setDisabledColor() {
		rect.setFillColor(sf::Color::Green);
		rect.setOutlineColor(sf::Color::Black);
	}

	void onMouseDown() {
		state = ButtonState::Pressed;
		setPressedColor();
	}

	void onMouseUp() {
		state = ButtonState::Normal;
		setNormal();
	}

	void onMouseMove(sf::Vector2f mousePos) {
		if (rect.getGlobalBounds().contains(mousePos)) {
			if (state != ButtonState::Pressed) {
				state = ButtonState::Hovered;
				setHovered();
			}
		}
		else {
			state = ButtonState::Normal;
			setNormal();
		}
	}



private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		target.draw(rect, states);
		target.draw(buttonText, states);
	}

	sf::RectangleShape rect;
	sf::Text buttonText;
	sf::Font font;
};