#include "linkedList.h"

void linkedList(sf::RenderWindow& window)
{
	LinkedList a;
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

void LinkedList::displayInit()
{
	Display::clear();
	Layer layer;
	layer.addList({ 780, 400 }, values);
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void LinkedList::init(sf::RenderWindow& window)
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
		window.clear(Style::backgroundColor);
		draw(window);
		cancel.draw(window);
		custom.draw(window);
		random.draw(window);
		empty.draw(window);
		window.display();
	}
}

void LinkedList::randomInit() {
	finished = 1;
	srand(time(NULL));
	n = rand() % (6) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}
void LinkedList::emptyInit() {
	finished = 1;
	n = 0;
	values.clear();
}
void LinkedList::customInit(sf::RenderWindow& window, Button& cancel) {
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
		window.clear(Style::backgroundColor);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void LinkedList::displayUpdate(int idx, int num)
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "Node* cur = head; ",
						 "for (int i = 0; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "cur->data = num;"});

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	order.push_back(1);
	layer.lists[0].hightlight(Style::lightPink);
	layer.lists[0].setState("head/cur");
	Display::addLayer(layer);

	order.push_back(2);
	Display::addLayer(layer);
	
	for (int i = 0; i < idx; ++i) {
		layer.lists[i].hightlight(sf::Color::White);
		if (i > 0) layer.lists[i].setState("");
		else layer.lists[i].setState("head");
		layer.lists[i + 1].hightlight(Style::lightPink);
		layer.lists[i + 1].setState("cur");
		order.push_back(3);
		Display::addLayer(layer);
		
		order.push_back(2);
		Display::addLayer(layer);
	}

	layer.lists[idx].hightlight(Style::cyan);
	layer.lists[idx].setValue(num);
	values[idx] = num;
	order.push_back(5);
	Display::addLayer(layer);

	layer.lists[idx].hightlight(sf::Color::White);
	if (idx == 0) layer.lists[idx].setState("head");
	else layer.lists[idx].setState("");
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void LinkedList::update(sf::RenderWindow& window)
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

void LinkedList::displayAdd(int idx, int num)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({ "Node* tmp = new Node {num, head};",
							 "head = tmp;"});
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
	}
	else {
		Display::addSource({ "Node* cur = head;",
							 "for (int i = 1; i < idx; ++i)",
							 "   cur = cur->next;",
							 "}",
							 "Node* tmp = new Node{num, cur->next};",
							 "cur->next = tmp;"});
		
		order.push_back(0);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("head/cur");
		Display::addLayer(layer);

		order.push_back(1);
		Display::addLayer(layer);

		for (int i = 1; i < idx; ++i) {
			layer.lists[i - 1].hightlight(sf::Color::White);
			if (i > 1) layer.lists[i - 1].setState("");
			else layer.lists[i - 1].setState("head");
			layer.lists[i].hightlight(Style::lightPink);
			layer.lists[i].setState("cur");
			order.push_back(2);
			Display::addLayer(layer);

			order.push_back(1);
			Display::addLayer(layer);
		}
		if (idx == n) {
			values.push_back(num);
			float x = 500 + n * size;
			layer.lists.push_back(LinkedListNode({ x, 400 }, num));
			layer.lists[n].hightlight(Style::cyan);
			layer.lists[n].setState("tmp");
			++n;
			order.push_back(4);
			Display::addLayer(layer);

			layer.arrows.push_back(Arrow());
			layer.arrows.back().create(layer.lists[n - 2], layer.lists.back());
			order.push_back(5);
			Display::addLayer(layer);

			layer.lists.back().hightlight(sf::Color::White);
			layer.lists[n - 1].setState("");

			layer.lists[n - 2].hightlight(sf::Color::White);
			if (n > 2) layer.lists[n - 2].setState("");
			else layer.lists[n - 2].setState("head");
		}
		else {
			values.insert(values.begin() + idx, num);
			++n;
			float x = 440 + idx * size;
			layer.lists.insert(layer.lists.begin() + idx, LinkedListNode({ x, 510 }, num));
			layer.arrows.insert(layer.arrows.begin() + idx, Arrow());
			layer.arrows[idx].create(layer.lists[idx], layer.lists[idx + 1]);
			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tmp");
			order.push_back(4);
			Display::addLayer(layer);

			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx]);
			order.push_back(5);
			Display::addLayer(layer);

			layer.addList({ 500, 400 }, values);	
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void LinkedList::add(sf::RenderWindow& window)
{
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
				input(window, index, "idx =", { 310.f, 320.f }, home, cancel);
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

void LinkedList::displayRemove(int idx)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({ "if (!(head)) return;",
						 "Node* tmp = head;",
						 "head = head->next;",
						 "delete tmp;"});

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
	else {
		Display::addSource({ "if (!(head)) return;",
						 "Node* cur = head;",
						 "for (int i = 1; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "Node* tmp = cur->next;",
						 "cur->next = tmp->next;",
						 "delete tmp;"});
		
		order.push_back(1);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("head/cur");
		Display::addLayer(layer);

		order.push_back(2);
		Display::addLayer(layer);

		for (int i = 1; i < idx; ++i) {
			layer.lists[i - 1].hightlight(sf::Color::White);
			if (i > 1) layer.lists[i - 1].setState("");
			else layer.lists[i - 1].setState("head");
			layer.lists[i].hightlight(Style::lightPink);
			layer.lists[i].setState("cur");
			order.push_back(3);
			Display::addLayer(layer);

			order.push_back(2);
			Display::addLayer(layer);
		}
		
		if (idx == n - 1) {
			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tmp");
			order.push_back(5);
			Display::addLayer(layer);

			layer.arrows.pop_back();
			order.push_back(6);
			Display::addLayer(layer);

			layer.lists.pop_back();
			order.push_back(7);
			Display::addLayer(layer);

			values.pop_back();
			--n;

			layer.lists.back().hightlight(sf::Color::White);
			if (n > 1) layer.lists[n - 1].setState("");
			else layer.lists[n - 1].setState("head");
		}
		else {
			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tmp");
			order.push_back(5);
			Display::addLayer(layer);

			float x = 500 + idx * size;
			layer.lists[idx].setPosition({x, 510});
			layer.arrows[idx].create(layer.lists[idx], layer.lists[idx + 1]);
			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx + 1]);
			order.push_back(6);
			Display::addLayer(layer);

			layer.lists.erase(layer.lists.begin() + idx);
			layer.arrows.erase(layer.arrows.begin() + idx);
			order.push_back(7);
			Display::addLayer(layer);

			values.erase(values.begin() + idx);
			n--;
			
			layer.addList({ 500, 400 }, values);
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}
void LinkedList::remove(sf::RenderWindow& window)
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
				input(window, index, "idx =", { 310.f, 420.f }, home, cancel);
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

void LinkedList::displaySearch(int num)
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "Node* cur = head; int idx = 0;",
						 "while (cur->data != num) {",
						 "   cur = cur->next; ++idx;",
						 "   if (!(cur)) return -1;",
						 "}",
						 "return idx;" });

	Layer layer;
	std::vector<int> order;
	layer.addList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (n != 0) {
		order.push_back(1);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("head/cur");
		Display::addLayer(layer);

		order.push_back(2);
		Display::addLayer(layer);

		int i = 0;
		while (values[i] != num) {
			if (i > 0) layer.lists[i].setState("");
			else layer.lists[i].setState("head");
			layer.lists[i].hightlight(sf::Color::White);
			++i;
			if (i < n) {
				layer.lists[i].hightlight(Style::lightPink);
				layer.lists[i].setState("cur");
			}
			order.push_back(3);
			Display::addLayer(layer);

			order.push_back(4);
			Display::addLayer(layer);
			if (i == n) break;

			order.push_back(2);
			Display::addLayer(layer);
		}

		if (i < n) {
			layer.lists[i].hightlight(Style::cyan);
			order.push_back(6);
			Display::addLayer(layer);

			layer.lists[i].hightlight(sf::Color::White);
			if (i > 0) layer.lists[i].setState("");
			else layer.lists[i].setState("head");
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void LinkedList::search(sf::RenderWindow& window)
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


