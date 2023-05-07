#include "Style.h"
#include "home.h"

int main() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 5.0;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Data Structure Visualization", sf::Style::Default, settings);
	Style::loadFont();
	
	home(window);
	return 0;
}