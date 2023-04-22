#pragma once
#include "Style.h"

class Layer;
class Source;
class Button2;

namespace Display {
	extern std::vector<Layer> layers;
	extern float layerStart, temp, layerLength;
	extern int layerID;
	extern Source source;
	extern std::vector<int> sourceOrder;
	extern bool playing;

	extern Button2 play;
	extern Button2 stop;
	extern Button2 pre;
	extern Button2 next;
	extern Button2 begin;
	extern Button2 end;
	
	extern float speed;
	extern sf::Text speedText;
	extern Button2 inc;
	extern Button2 dec;

	extern void addLayer(Layer layer);
	extern void clear();
	extern void start();
	//extern void handleButtonEvents(sf::RenderWindow& window, sf::Event event);
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void update();
	extern void draw(sf::RenderWindow& window);
	extern void addOrder(std::vector<int> order);
	extern void addSource(std::vector<std::string> st);
}