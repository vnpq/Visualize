#include "Display.h"
namespace Display {
	std::vector<Layer> layers;
	float layerStart, temp, layerLength = 0.7f;
	int layerID = -1;
	Source source;
	std::vector<int> sourceOrder;

	void addLayer(Layer layer)
	{
		layers.push_back(layer);
	}

	void clear()
	{
		layers.clear();
		layerID = -1;
		source.clear();
		sourceOrder.clear();
	}

	void start()
	{
		layerStart = clock() / CLOCKS_PER_SEC;
		layerID = 0;
	}

	void run(sf::RenderWindow& window, sf::Event event)
	{
		if (layerID < 0) return;
		temp = clock() / CLOCKS_PER_SEC;
		if (temp - layerStart >= layerLength) {
			layerID = std::min(layerID + 1, (int)layers.size() - 1);
			layerStart = temp;
		}
		source.highlight(sourceOrder[layerID]);
	}

	void update()
	{
		if (layerID < 0) return;
		temp = clock() / CLOCKS_PER_SEC;
		if (temp - layerStart >= layerLength) {
			layerID = std::min(layerID + 1, (int)layers.size() - 1);
			layerStart = temp;
		}
		source.highlight(sourceOrder[layerID]);
	}

	void draw(sf::RenderWindow& window)
	{
		if (layerID < 0) return;
		layers[layerID].draw(window);
		source.draw(window);

	}

	void addOrder(std::vector<int> order)
	{
		sourceOrder = order;
	}

	void addSource(std::vector<std::string> st)
	{
		source.add(st);
	}

}