#include "Style.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualiztion");

	//Button butt;
	//butt.init(sf::Vector2f(100, 100), "PQ");
	Textbox box1;
	box1.init(sf::Vector2f(200.f, 200.f));
	Button home;
	home.init(sf::Vector2f(100.f, 100.f), "Home");

	sf::Font font;
	font.loadFromFile("Lexend-Regular.ttf");
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Black);
	std::string st;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			box1.handleEvent(window, event, st);
			text.setString(st);
			home.handleEvent(window, event);
		}

		window.clear(Style::backgroundColor);

		home.draw(window);
		box1.draw(window);
		window.draw(text);
		window.display();

	}

	return 0;
}