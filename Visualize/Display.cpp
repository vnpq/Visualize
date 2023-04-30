#include "Display.h"
namespace Display {
	std::vector<Layer> layers;
	//Layer* layers;
	float layerStart, temp, layerLength = 1.f;
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

	float speed = 1.f;
	sf::Text speedText;
	Button2 inc;
	Button2 dec;

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
		stop.init({ 750, 900 }, 0);
		play.init({ 750, 900 }, 1);
		begin.init({ 550, 900 }, 2);
		end.init({ 950, 900 }, 3);
		pre.init({ 650, 900 }, 4);
		next.init({ 850, 900 }, 5);

		inc.init({ 260, 900 }, 6);
		dec.init({ 70, 900 }, 7);

		speedText.setFont(Style::font);
		speedText.setFillColor(sf::Color::White);
		std::string st = std::to_string(speed).substr(0, 4) + "x";
		speedText.setString(st);
		speedText.setCharacterSize(23);
		speedText.setPosition({ 160, 890 });
		playing = 1;

		layerStart = (float)clock() / CLOCKS_PER_SEC;
		layerID = 0;
		//layers = new Layer[10];
	}


	void run(sf::RenderWindow& window, sf::Event event)
	{
		if (layerID < 0) return;

		if (playing) {
			if (stop.handleEvent(window, event) || layerID == layers.size() - 1)
				playing = 0;
		}
		else {
			if (play.handleEvent(window, event)) {
				playing = 1;
				if (layerID == layers.size() - 1) 
					layerID = 0;
			}
		}
		if (next.handleEvent(window, event))
			layerID = std::min(layerID + 1, (int)layers.size() - 1);;
		if (pre.handleEvent(window, event))
			layerID = std::max(layerID - 1, 0);
		if (end.handleEvent(window, event))
			layerID = (int)layers.size() - 1;
		if (begin.handleEvent(window, event))
			layerID = 0;
		if (dec.handleEvent(window, event) && speed > 0.25) {
			speed -= 0.25;
			std::string st = std::to_string(speed).substr(0, 4) + "x";
			speedText.setString(st);
			layerLength = 1.0 / speed;
		}
		if (inc.handleEvent(window, event)) {
			speed += 0.25;
			std::string st = std::to_string(speed).substr(0, 4) + "x";
			speedText.setString(st);
			layerLength = 1.0 / speed;
		}

		temp = (float)clock() / CLOCKS_PER_SEC;
		if (playing) {
			if (temp - layerStart >= layerLength) {
				layerID = std::min(layerID + 1, (int)layers.size() - 1);
				layerStart = temp;
			}
		}
		else layerStart = temp;
		source.highlight(sourceOrder[layerID]);
	}

	void update()
	{
		if (layerID < 0) return;
		temp = (float)clock() / CLOCKS_PER_SEC;
		if (playing) {
			if (temp - layerStart >= layerLength) {
				layerID = std::min(layerID + 1, (int)layers.size() - 1);
				layerStart = temp;
			}
		}
		else layerStart = temp;
		source.highlight(sourceOrder[layerID]);
	}

	void draw(sf::RenderWindow& window)
	{
		if (layerID < 0) return;
		source.draw(window);
		layers[layerID].draw(window);
		if (playing) stop.draw(window);
		else play.draw(window);
		pre.draw(window);
		next.draw(window);
		begin.draw(window);
		end.draw(window);
		dec.draw(window);
		inc.draw(window);
		window.draw(speedText);
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