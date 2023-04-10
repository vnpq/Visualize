#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Button.h"
#include "Textbox.h"
#include "Arrow.h"
#include "Layer.h"
#include "Source.h"
#include "Display.h"
//#include "home.h"

#define M_PI 3.14159265358979323846

namespace Style {
	extern sf::Color backgroundColor;
	extern sf::Color pink;
	extern sf::Color purple;
	extern sf::Color darkBlue;
	extern sf::Color cyan;
	extern sf::Color lightPink;
	
	extern sf::Font font;
	extern sf::Font font2;
	extern sf::Font cFont;
	extern void loadFont();
}