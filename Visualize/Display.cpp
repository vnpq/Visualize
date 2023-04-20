#include "Display.h"
namespace Display {
	std::vector<Layer> layers;
	float layerStart, temp, layerLength = 0.7f;
	int layerID = -1;
	Source source;
	std::vector<int> sourceOrder;
	bool playing = 1;

	Button2 play;
	Button2 stop;
	Button2	pre;
	Button2 next;
	Button2 begin;
	Button2 end;

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
		play.init({ 1150, 850 }, 0);
		stop.init({ 1150, 850 }, 1);
		begin.init({ 950, 850 }, 2);
		end.init({ 1350, 850 }, 3);
		pre.init({ 1050, 850 }, 4);
		next.init({ 1250, 850 }, 5);

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
		source.draw(window);
		layers[layerID].draw(window);
		if (playing) play.draw(window);
		else stop.draw(window);
		pre.draw(window);
		next.draw(window);
		begin.draw(window);
		end.draw(window);
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