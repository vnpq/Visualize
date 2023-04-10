#pragma once
#include "Style.h"

class Layer;
class Source;

namespace Display {
	extern std::vector<Layer> layers;
	extern float layerStart, temp, layerLength;
	extern int layerID;
	extern Source source;
	extern std::vector<int> sourceOrder;
	extern void addLayer(Layer layer);
	extern void clear();
	extern void start();
	extern void run(sf::RenderWindow& window, sf::Event event);
	extern void update();
	extern void draw(sf::RenderWindow& window);
	extern void addOrder(std::vector<int> order);
	extern void addSource(std::vector<std::string> st);

}