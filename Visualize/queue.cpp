#include "home.h"

void Queue(sf::RenderWindow& window)
{
	QueueClass a;
	a.setLayout();
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (a.initB.handleEvent(window, event))
				a.init(window);

			if (a.enqueueB.handleEvent(window, event))
				a.enqueue(window);

			if (a.frontB.handleEvent(window, event))
				a.front(window);

			if (a.dequeueB.handleEvent(window, event))
				a.dequeue(window);

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

void QueueClass::displayInit()
{
	Display::clear();
	Layer layer;
	layer.addList({ 780, 400 }, values);
	if (n > 1) layer.lists[n - 1].setState("tail");
	if (n == 1) layer.lists[0].setState("head/tail");
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void QueueClass::init(sf::RenderWindow& window)
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

void QueueClass::randomInit()
{
	finished = 1;
	srand(time(NULL));
	n = rand() % (6) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}

void QueueClass::emptyInit()
{
	finished = 1;
	n = 0;
	values.clear();
}

void QueueClass::customInit(sf::RenderWindow& window, Button& cancel)
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
				input(window, stack, "queue = ", { 300.f, 120.f }, home, cancel);
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

void QueueClass::displayEnqueue(int num)
{
	Display::clear();
	Display::addSource({ "tail->next = new Node {num, nullptr};",
						 "tail = tail->next;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	if (n > 1) layer.lists.back().setState("tail");
	if (n == 1) layer.lists[0].setState("head/tail");
	order.push_back(-1);
	Display::addLayer(layer);

	values.push_back(num);
	float x = 500 + n * size;
	layer.lists.push_back(LinkedListNode({ x, 400 }, num));
	layer.lists[n].hightlight(Style::cyan);
	if (n > 0) {
		layer.arrows.push_back(Arrow());
		layer.arrows.back().create(layer.lists[n - 1], layer.lists.back());
	}
	++n;
	order.push_back(0);
	Display::addLayer(layer);

	layer.lists.back().hightlight(sf::Color::White);
	layer.lists[n - 1].setState("tail");
	if (n > 2) layer.lists[n - 2].setState("");
	layer.lists[0].setState("head");
	if (n == 1) layer.lists[0].setState("head/tail");
	order.push_back(1);
	Display::addLayer(layer);

	layer.lists[0].setState("head");
	if (n == 1) layer.lists[0].setState("head/tail");
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void QueueClass::enqueue(sf::RenderWindow& window)
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
				displayEnqueue(num);
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

void QueueClass::displayFront()
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "return head->data;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	if (n > 1) layer.lists.back().setState("tail");
	if (n == 1) layer.lists[0].setState("head/tail");
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

void QueueClass::front(sf::RenderWindow& window)
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
				displayFront();
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

void QueueClass::displayDequeue()
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "Node* tmp = head;",
						 "head = head->next;",
						 "delete tmp;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	if (n > 1) layer.lists.back().setState("tail");
	if (n == 1) layer.lists[0].setState("head/tail");
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (n != 0) {
		layer.lists[0].hightlight(Style::cyan);
		layer.lists[0].setState("head/tmp");
		if (n == 1) layer.lists[0].setState("head/tail/tmp");
		order.push_back(1);
		Display::addLayer(layer);

		layer.lists[0].setState("tmp");
		if (n > 1) layer.lists[1].setState("head");
		if (n == 2) layer.lists[1].setState("head/tail");
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

void QueueClass::dequeue(sf::RenderWindow& window)
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
				displayDequeue();
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
