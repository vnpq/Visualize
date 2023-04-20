#include "staticArray.h"

void StaticArray(sf::RenderWindow& window)
{
	SArray a;
	a.setLayout();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (a.initB.handleEvent(window, event))
				a.init(window);

			if (a.updateB.handleEvent(window, event))
				a.update(window);

			if (a.searchB.handleEvent(window, event))
				a.search(window);

			if (a.home.state == 2 || a.home.handleEvent(window, event)) {
				return Display::clear();
			}
			Display::run(window, event);
		}	
		Display::update();
		window.clear(sf::Color::White);
		a.draw(window);
		window.display();
	}
}
void SArray::displayInit() {
	Display::clear();
	Layer layer;
	float x = 1150 - 30 * n;
	layer.addArray({ x, 400 }, values);
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void SArray::init(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	Button random;
	random.init(sf::Vector2f(480.f, 100.f), "Random");
	Button custom;
	custom.init(sf::Vector2f(480.f, 200.f), "Custom");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
			if (custom.handleEvent(window, event)) {
				customInit(window, cancel);
				displayInit();
				return;
			}
			if (random.handleEvent(window, event)) {
				randomInit();
				displayInit();
				return;
			}
		}
		window.clear(sf::Color::White);
		draw(window);
		cancel.draw(window);
		custom.draw(window);
		random.draw(window);
		window.display();
	}
}
void SArray::randomInit() {
	finished = 1;
	srand(time(NULL));
	n = rand() % (18) + 3;
	values.clear();
	for (int i = 0; i < n; ++i) 
		values.push_back(rand() % (101));
}
void SArray::customInit(sf::RenderWindow& window, Button& cancel) {
	
	std::string arr="";
	finished = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
			if (!(finished)) {
				input(window, arr, "arr =", { 310.f, 120.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (arr == "") continue;
				values.clear();
				std::stringstream ss(arr);
				while (ss.good()) {
					std::string substr;
					std::getline(ss, substr, ',');
					int num = std::stoi(substr);
					values.push_back(num);
				}
				n = values.size();
				finished = 1;
			}
			else return;
		}
		window.clear(sf::Color::White);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void SArray::displayUpdate(int idx, int num)
{
	Display::clear();
	Display::addSource({ "arr[idx] = num;" });
	
	Layer layer;
	float x = 1150 - 30 * n;
	layer.addArray({ x, 400 }, values);
	Display::addLayer(layer);

	layer.arrays[idx].hightlight(Style::cyan);
	Display::addLayer(layer);

	layer.arrays[idx].setValue(num);
	values[idx] = num;
	Display::addLayer(layer);

	layer.arrays[idx].hightlight(sf::Color::White);
	Display::addLayer(layer);

	Display::addOrder({ -1, 0, 0, -1 });

	Display::start();

}
void SArray::update(sf::RenderWindow& window)
{
	if (n == 0) return;

	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	std::string index = "";
	std::string number = "";
	finished = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event)) 
				return displayInit();
			
			if (!(finished)) {
				input(window, index, "idx =", { 310.f, 220.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (index == "") continue;
				int idx = std::stoi(index);
				if (idx < 0 || idx >= n) continue;

				input(window, number, "num =", { 310.f, 320.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (number == "") continue;
				int num = std::stoi(number);

				finished = 1;
				cancel.buttonText.setString("   OK");
				displayUpdate(idx, num);
			}
			Display::run(window, event);
		}
		window.clear(sf::Color::White);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void SArray::displaySearch(int num)
{
	Display::clear();
	Display::addSource({ "for (int i = 0; i < n; ++i) {",
						 "   if (arr[i] == num)",
						 "      return i;",
						 "}",
						 "return -1;"});

	std::vector<int> order;
	Layer layer;
	float x = 1150 - 30 * n;
	layer.addArray({ x, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);
	
	finished = 0;
	for (int i = 0; i < n; ++i) {
		if (i > 0) {
			layer.arrays[i - 1].hightlight(sf::Color::White);
			order.push_back(0);
			Display::addLayer(layer);
		}
		layer.arrays[i].hightlight(Style::lightPink);
		order.push_back(1);
		Display::addLayer(layer);
		if (num == values[i]) {
			layer.arrays[i].hightlight(Style::cyan);
			finished = 1;
			order.push_back(2);
			Display::addLayer(layer);
			
			layer.arrays[i].hightlight(sf::Color::White);
			break;
		}
	}

	if (!(finished)) {
		layer.arrays[n - 1].hightlight(sf::Color::White);
		order.push_back(0);
		Display::addLayer(layer);
		order.push_back(4);
		Display::addLayer(layer);
		finished = 1;
	}

	order.push_back(-1);
	Display::addLayer(layer);
	
	Display::addOrder(order);
	Display::start();
}

void SArray::search(sf::RenderWindow& window)
{
	if (n == 0) return;

	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	std::string number = "";
	finished = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event)) 
				return displayInit();
			if (!(finished)) {
				input(window, number, "num =", { 310.f, 320.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (number == "") continue;
				int num = std::stoi(number);

				finished = 1;
				cancel.buttonText.setString("   OK");
				displaySearch(num);
			}
			Display::run(window, event);
		}
		window.clear(sf::Color::White);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}
