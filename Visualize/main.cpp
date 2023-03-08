#include "Style.h"

int main() {

	Style::load();

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualiztion");

	sf::Text text;
	text.setFont(Style::font);
	text.setFillColor(sf::Color::Black);
	text.setString("Testing");
	text.setCharacterSize(20);
	text.setPosition(100.0f, 100.0f);

	Button homeButt("Toi yeu KTLT");
	homeButt.setPosition(100, 200);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					homeButt.onMouseDown();
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					homeButt.onMouseUp();
				}
				break;
			case sf::Event::MouseMoved:
				homeButt.onMouseMove(sf::Vector2f(sf::Mouse::getPosition()));
				break;
			default:
				break;
			}			
		}

		window.clear(Style::backgroundColor);
		window.draw(homeButt);
		window.display();

	}

	return 0;
}