#include "Style.h"
#include "home.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualization");
	Style::loadFont();
	home(window);
	return 0;
}