#include "Style.h"

int main() {

	Style::load();

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualiztion");

	sf::Text text;
	text.setFont(Style::font);
	text.setFillColor(Style::darkText);
	text.setString("Testing");
	text.setCharacterSize(20);
	text.setPosition(100.0f, 100.0f);

	Button homeButt("Home", sf::Vector2f(100, 90), Style::darkBg, Style::lightText);
	homeButt.setPosition(100, 200);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			homeButt.handleEvent(event, window);
		}

		window.clear(Style::backgroundColor);
		window.draw(homeButt);
		window.display();

	}

	return 0;
}