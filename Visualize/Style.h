#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Button.h"

namespace Style {
	sf::Color backgroundColor = sf::Color::White;
	sf::Color lightBg = sf::Color(250, 170, 202);
	sf::Color darkText = sf::Color(0,0,0);
	sf::Color darkBg = sf::Color(171, 10, 74);
	sf::Color lightText = sf::Color::White;
	sf::Font font;

	void load() {
		if (!font.loadFromFile("Lexend-Regular.ttf")) {
			//error loadinf font;
		}
	}


}