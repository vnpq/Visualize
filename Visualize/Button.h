#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Button : public sf::Drawable, public sf::Transformable {
public:
	Button(const std::string& text,
		const sf::Vector2f& size,
		const sf::Color& bgColor,
		const sf::Color& textColor) {

		rect.setSize(size);
		rect.setFillColor(bgColor);
		rect.setOutlineThickness(1.0f);
		rect.setOutlineColor(sf::Color::Black);

		// Create the text for the button
		font.loadFromFile("Lexend-Regular.ttf");
		buttonText.setFont(font);
		buttonText.setCharacterSize(20);
		buttonText.setFillColor(textColor);
		buttonText.setString(text);

		// Position the text in the center of the button
		sf::FloatRect textBounds = buttonText.getLocalBounds();
		buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
		buttonText.setPosition(size / 2.0f);

		// Position the button
		rect.setPosition(getPosition());
	}
		void handleEvent(const sf::Event& event, sf::RenderWindow& window) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (rect.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
                // Button was clicked
                std::cout << "Button clicked!" << std::endl;
            }
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