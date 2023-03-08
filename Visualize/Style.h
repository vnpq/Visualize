#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Button.h"
#include "Button.cpp"

namespace Style {
	sf::Color backgroundColor = sf::Color::White;
	sf::Color pink = sf::Color(253, 179, 202);
	sf::Color bluePastel = sf::Color(210, 209, 250);
	sf::Color darkBlue = sf::Color(68, 84, 145);
	sf::Color cyan = sf::Color(182, 239, 242);

	sf::Font font;

	void load() {
		if (!font.loadFromFile("Lexend-Regular.ttf")) {
			//error loadinf font;
		}
	}


}