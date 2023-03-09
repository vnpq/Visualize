#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>


class Textbox {
public:

	enum TextboxState {
		Typable = 0,
		UnTypable = 1
	};
	sf::Font font;
	sf::Text text;
	sf::RectangleShape box;
	
	int state = UnTypable;

	void init(sf::Vector2f pos);
	void handleEvent(sf::RenderWindow& window, sf::Event event);
	void draw(sf::RenderWindow& window);

};