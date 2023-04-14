#include "doublyLL.h"

void DoublyLL(sf::RenderWindow& window)
{
	DLL a;
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
		window.clear(sf::Color::White);
		a.draw(window);
		window.display();
	}
}

void DLL::displayInit()
{
	Display::clear();
	Layer layer;
	layer.addDList({ 780, 400 }, values);
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void DLL::init(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	Button random;
	random.init(sf::Vector2f(480.f, 100.f), "Random");
	Button custom;
	custom.init(sf::Vector2f(480.f, 200.f), "Custom");
	Button empty;
	empty.init(sf::Vector2f(480.f, 300.f), "Empty");

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
			if (empty.handleEvent(window, event)) {
				emptyInit();
				displayInit();
				return;
			}
		}
		window.clear(sf::Color::White);
		draw(window);
		cancel.draw(window);
		custom.draw(window);
		random.draw(window);
		empty.draw(window);
		window.display();
	}
}

void DLL::randomInit()
{
	finished = 1;
	srand(time(NULL));
	n = rand() % (8) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}

void DLL::emptyInit()
{
	finished = 1;
	n = 0;
	values.clear();
}

void DLL::customInit(sf::RenderWindow& window, Button& cancel)
{
	std::string list = "";
	finished = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
			if (!(finished)) {
				input(window, list, "list =", { 310.f, 120.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (list == "") continue;
				values.clear();
				std::stringstream ss(list);
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

void DLL::update(sf::RenderWindow& window)
{
}

void DLL::add(sf::RenderWindow& window)
{
}

void DLL::remove(sf::RenderWindow& window)
{
}

void DLL::search(sf::RenderWindow& window)
{
}
