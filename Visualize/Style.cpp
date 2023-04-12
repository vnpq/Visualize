#include "Style.h"

namespace Style {
	sf::Color backgroundColor = sf::Color::White;
	sf::Color pink = sf::Color(253, 179, 202);
	sf::Color purple = sf::Color(233, 199, 255);
	sf::Color darkBlue = sf::Color(68, 84, 145);
	sf::Color cyan = sf::Color(182, 239, 242);
	sf::Color lightPink = sf::Color(252, 199, 216);
	sf::Color gray = sf::Color(190, 190, 190);

	sf::Font font;
	sf::Font font2;
	sf::Font cFont;
	sf::Texture t[3];
	void loadFont() {
		font.loadFromFile("Lexend-Regular.ttf");
		font2.loadFromFile("MeowScript-Regular.ttf");
		cFont.loadFromFile("Cascadia.ttf");
		t[1].loadFromFile("arrow1.png");
		t[2].loadFromFile("arrow2.png");
	}
}



