#include "home.h"

void Stack(sf::RenderWindow& window)
{
	StackClass a;
	a.setLayout();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (a.initB.handleEvent(window, event))
				a.init(window);

			if (a.pushB.handleEvent(window, event))
				a.push(window);

			if (a.topB.handleEvent(window, event))
				a.top(window);

			if (a.popB.handleEvent(window, event))
				a.pop(window);

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

void StackClass::displayInit()
{
	Display::clear();
	Layer layer;
	layer.addList({ 780, 400 }, values);
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void StackClass::init(sf::RenderWindow& window)
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

void StackClass::randomInit()
{
	finished = 1;
	srand(time(NULL));
	n = rand() % (6) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}

void StackClass::emptyInit()
{
	finished = 1;
	n = 0;
	values.clear();
}

void StackClass::customInit(sf::RenderWindow& window, Button& cancel)
{
	std::string stack = "";
	finished = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
			if (!(finished)) {
				input(window, stack, "stack = ", { 300.f, 120.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (stack == "") continue;
				values.clear();
				std::stringstream ss(stack);
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

void StackClass::displayPush(int num)
{
	Display::clear();
	Display::addSource({ "Node* tmp = new Node {num, head};",
						 "head = tmp;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	if (n == 0) {
		layer.lists.push_back(LinkedListNode({ 500,400 }, num));
		order.push_back(0);
		layer.lists[n].setState("tmp");
		Display::addLayer(layer);

		layer.lists[0].setState("head/tmp");
		order.push_back(1);
		Display::addLayer(layer);
		values.push_back(num);
		++n;
	}
	else {
		layer.lists.insert(layer.lists.begin(), LinkedListNode({ 500, 510 }, num));
		layer.arrows.insert(layer.arrows.begin(), Arrow());
		layer.arrows[0].create(layer.lists[0], layer.lists[1]);

		layer.lists[0].hightlight(Style::cyan);
		layer.lists[0].setState("tmp");
		order.push_back(0);
		Display::addLayer(layer);

		values.insert(values.begin(), num);
		++n;

		layer.addList({ 500, 400 }, values);
		layer.lists[0].hightlight(Style::cyan);
		layer.lists[0].setState("tmp");
		layer.lists[1].setState("head");
		order.push_back(1);
		Display::addLayer(layer);

		layer.lists[1].setState("");
		layer.lists[0].setState("head/tmp");
		order.push_back(1);
		Display::addLayer(layer);

		layer.lists[0].hightlight(sf::Color::White);
	}

	layer.lists[0].setState("head");
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void StackClass::push(sf::RenderWindow& window)
{
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
				input(window, number, "num =", { 310.f, 220.f }, home, cancel);
				if (home.state == 2 || cancel.state == 2) return;
				if (number == "") continue;
				int num = std::stoi(number);

				finished = 1;
				cancel.buttonText.setString("   OK");
				displayPush(num);
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

void StackClass::displayTop()
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "return head->data;"});

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (n != 0) {
		layer.lists[0].hightlight(Style::cyan);
		order.push_back(1);
		Display::addLayer(layer);
		layer.lists[0].hightlight(sf::Color::White);
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void StackClass::top(sf::RenderWindow& window)
{
	Button OK;
	OK.init(sf::Vector2f(1450.f, 800.f), "OK");
	finished = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || OK.handleEvent(window, event))
				return displayInit();
			if (!(finished)) {
				finished = 1;
				displayTop();
			}		
			Display::run(window, event);
		}
		window.clear(sf::Color::White);
		Display::update();
		OK.draw(window);
		draw(window);
		window.display();
	}
}

void StackClass::displayPop()
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "Node* tmp = head;",
						 "head = head->next;",
						 "delete tmp;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (n != 0) {
		layer.lists[0].hightlight(Style::cyan);
		layer.lists[0].setState("head/tmp");
		order.push_back(1);
		Display::addLayer(layer);

		layer.lists[0].setState("tmp");
		if (n > 1) layer.lists[1].setState("head");
		order.push_back(2);
		Display::addLayer(layer);

		layer.lists.erase(layer.lists.begin());
		if (n > 1) layer.arrows.erase(layer.arrows.begin());
		order.push_back(3);
		Display::addLayer(layer);

		values.erase(values.begin());
		--n;
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void StackClass::pop(sf::RenderWindow& window)
{
	Button OK;
	OK.init(sf::Vector2f(1450.f, 800.f), "OK");
	finished = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || OK.handleEvent(window, event))
				return displayInit();
			if (!(finished)) {
				finished = 1;
				displayPop();
			}
			Display::run(window, event);
		}
		window.clear(sf::Color::White);
		Display::update();
		OK.draw(window);
		draw(window);
		window.display();
	}
}
