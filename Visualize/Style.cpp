#include "Style.h"

namespace Style {
	sf::Color backgroundColor = sf::Color::White;
	sf::Color pink = sf::Color(253, 179, 202);
	sf::Color purple = sf::Color(233, 199, 255);
	sf::Color darkBlue = sf::Color(68, 84, 145);
	sf::Color cyan = sf::Color(182, 239, 242);
	sf::Color lightPink = sf::Color(252, 199, 216);

	sf::Font font;
	void loadFont() {
		font.loadFromFile("Lexend-Regular.ttf");
	}
	sf::Font font2;
	void loadFont2() {
		font2.loadFromFile("MeowScript-Regular.ttf");
	}
}



