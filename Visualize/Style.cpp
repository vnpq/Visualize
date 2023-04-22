#include "Style.h"

namespace Style {
	sf::Color backgroundColor = sf::Color::White;
	sf::Color normalText = sf::Color::Black;
	sf::Color stateText = sf::Color::Red;
	sf::Color pink = sf::Color(253, 179, 202);
	sf::Color purple = sf::Color(233, 199, 255);
	sf::Color darkBlue = sf::Color(68, 84, 145);
	sf::Color cyan = sf::Color(182, 239, 242);
	sf::Color lightPink = sf::Color(252, 199, 216);
	sf::Color gray = sf::Color(190, 190, 190);
	sf::Color sideBar = darkBlue;

	bool dark = 0;

	sf::Font font;
	sf::Font font2;
	sf::Font cFont;
	sf::Texture t, t2, a, a2;
	sf::Texture state[8];
	void loadFont() {
		font.loadFromFile("Lexend-Regular.ttf");
		font2.loadFromFile("MeowScript-Regular.ttf");
		cFont.loadFromFile("Cascadia.ttf");
		t.loadFromFile("arrow.png");
		t2.loadFromFile("self-arrow.png");
		a.loadFromFile("arrow2.png");
		a2.loadFromFile("self-arrow2.png");
		state[0].loadFromFile("play.jpg");
		state[1].loadFromFile("stop.jpg");
		state[2].loadFromFile("start.jpg");
		state[3].loadFromFile("end.jpg");
		state[4].loadFromFile("pre.jpg");
		state[5].loadFromFile("next.jpg");
		state[6].loadFromFile("inc.png");
		state[7].loadFromFile("dec.png");
	}
}



