#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Button.h"
#include "Textbox.h"
#include "home.h"

namespace Style {
	extern sf::Color backgroundColor;
	extern sf::Color pink;
	extern sf::Color purple;
	extern sf::Color darkBlue;
	extern sf::Color cyan;
	extern sf::Color lightPink;
	
	extern sf::Font font;
	extern void loadFont();
	extern sf::Font font2;
	extern void loadFont2();
}