#include "dynaArray.h"

void DynamicArray(sf::RenderWindow& window)
{
	DynaArray a;
	a.setLayout();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (a.initB.handleEvent(window, event))
				a.init(window);

			if (a.updateB.handleEvent(window, event))
				a.update(window);

			if (a.addB.handleEvent(window, event))
				a.add(window);

			if (a.removeB.handleEvent(window, event))
				a.remove(window);

			if (a.searchB.handleEvent(window, event))
				a.search(window);

			if (a.home.state == 2 || a.home.handleEvent(window, event)) {
				return Display::clear();
			}

			Display::run(window, event);
		}
		window.clear(Style::backgroundColor);
		a.draw(window);
		window.display();
	}
}

void DynaArray::displayInit()
{
	Display::clear();
	Layer layer;
	float x = 1150 - 30 * n;
	layer.addArray({ x, 400 }, values);
	for (int i = n; i < size; ++i)
		layer.arrays[i].hightlight(Style::gray);

	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void DynaArray::init(sf::RenderWindow& window)
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
		window.clear(Style::backgroundColor);
		draw(window);
		cancel.draw(window);
		custom.draw(window);
		random.draw(window);
		window.display();
	}
}
void DynaArray::randomInit() {
	finished = 1;
	srand(time(NULL));
	n = rand() % (8) + 3;
	size = n;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}
void DynaArray::customInit(sf::RenderWindow& window, Button& cancel) {

	std::string arr = "";
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
				size = n;
				finished = 1;
			}
			else return;
		}
		window.clear(Style::backgroundColor);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void DynaArray::displayUpdate(int idx, int num)
{
	Display::clear();
	Display::addSource({ "arr[idx] = num" });

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
void DynaArray::update(sf::RenderWindow& window)
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
		window.clear(Style::backgroundColor);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}
void DynaArray::displayGrow(Layer& layer)
{
	for (int i = 0; i < n; ++i) values.push_back(0);
	size *= 2;
	float x = 1150 - 30 * size;
	layer.addArray({ x, 400 }, values);
	for (int i = n; i < size; ++i) 
		layer.arrays[i].hightlight(Style::gray);
}

void DynaArray::displayAdd(int idx, int num)
{
	Display::clear();
	Display::addSource({ "for (int i = n - 1; i > idx; --i) {",
						 "   arr[i + 1] = arr[i];",
						 "}",
						 "arr[idx] = num;", 
						 "++n;"});

	std::vector<int> order;
	Layer layer;
	float x = 1150 - 30 * size;
	layer.addArray({ x, 400 }, values);
	for (int i = n; i < size; ++i)
		layer.arrays[i].hightlight(Style::gray);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	for (int i = n - 1; i >= idx; --i) {
		if (i < n - 1) {
			layer.arrays[i + 1].hightlight(sf::Color::White);
			order.push_back(0);
			Display::addLayer(layer);
		}
		if (i + 1 >= size) {
			displayGrow(layer);
			order.push_back(1);
			layer.arrays[i].hightlight(Style::lightPink);
			layer.arrays[i + 1].hightlight(sf::Color::White);
			Display::addLayer(layer);
		}
		layer.arrays[i].hightlight(Style::lightPink);
		layer.arrays[i + 1].hightlight(sf::Color::White);
		values[i + 1] = values[i];
		layer.arrays[i + 1].setValue(values[i]);
		order.push_back(1);
		Display::addLayer(layer);
	}
	if (idx == n) {
		if (n>=size) displayGrow(layer);
		order.push_back(3);
		Display::addLayer(layer);		
	}
	else {
		layer.arrays[idx].hightlight(sf::Color::White);
		order.push_back(0);
		Display::addLayer(layer);
	}

	layer.arrays[idx].hightlight(Style::cyan);
	values[idx] = num;
	++n;
	layer.arrays[idx].setValue(num);
	order.push_back(3);
	Display::addLayer(layer);

	layer.arrays[idx].hightlight(sf::Color::White);
	order.push_back(4);
	Display::addLayer(layer);

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void DynaArray::add(sf::RenderWindow& window)
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
				input(window, index, "idx =", {310.f, 320.f}, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (index == "") continue;
				int idx = std::stoi(index);
				if (idx < 0 || idx > n) continue;

				input(window, number, "num =", { 310.f, 420.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (number == "") continue;
				int num = std::stoi(number);

				finished = 1;
				cancel.buttonText.setString("   OK");
				displayAdd(idx, num);
			}
			Display::run(window, event);
		}
		window.clear(Style::backgroundColor);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}


void DynaArray::displayRemove(int idx)
{
	Display::clear();
	Display::addSource({ "for (int i = idx; i < n - 1; ++i) {",
						 "   arr[i] = arr[i + 1];",
						 "}",
						 "arr[n - 1] = 0",
						 "--n;" });

	std::vector<int> order;
	Layer layer;
	float x = 1150 - 30 * size;
	layer.addArray({ x, 400 }, values);
	for (int i = n; i < size; ++i)
		layer.arrays[i].hightlight(Style::gray);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);
	
	for (int i = idx; i < n - 1; ++i) {
		if (i > idx) {
			layer.arrays[i - 1].hightlight(sf::Color::White);
			order.push_back(0);
			Display::addLayer(layer);
		}
		layer.arrays[i].hightlight(Style::lightPink);
		values[i] = values[i + 1];
		layer.arrays[i].setValue(values[i]);
		order.push_back(1);
		Display::addLayer(layer);
	}
	
	layer.arrays[n - 2].hightlight(sf::Color::White);
	order.push_back(0);
	Display::addLayer(layer);

	layer.arrays[n - 1].hightlight(Style::cyan);
	values[n - 1] = 0;
	layer.arrays[n - 1].setValue(0);
	order.push_back(3);
	Display::addLayer(layer);

	layer.arrays[n - 1].hightlight(Style::gray);
	n--;
	order.push_back(4);
	Display::addLayer(layer);

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void DynaArray::remove(sf::RenderWindow& window)
{
	if (n == 0) return;
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	std::string index = "";
	finished = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return displayInit();
			if (!(finished)) {
				input(window, index, "idx =", { 310.f, 320.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (index == "") continue;
				int idx = std::stoi(index);
				if (idx < 0 || idx >= n) continue;

				finished = 1;
				cancel.buttonText.setString("   OK");
				displayRemove(idx);
			}
			Display::run(window, event);
		}
		window.clear(Style::backgroundColor);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}


void DynaArray::displaySearch(int num)
{
	Display::clear();
	Display::addSource({ "for (int i = 0; i < n; ++i) {",
						 "   if (arr[i] == num)",
						 "      return i;",
						 "}",
						 "return -1;" });

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

void DynaArray::search(sf::RenderWindow& window)
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
				input(window, number, "num =", { 310.f, 520.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (number == "") continue;
				int num = std::stoi(number);

				finished = 1;
				cancel.buttonText.setString("   OK");
				displaySearch(num);
			}
			Display::run(window, event);
		}
		window.clear(Style::backgroundColor);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}
