#include "home.h"
#include "circularLL.h"

void CircularLL(sf::RenderWindow& window)
{
	CLL a;
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

void CLL::displayInit()
{
	Display::clear();
	Layer layer;
	layer.addCList(values);
	Display::addLayer(layer);
	Display::addOrder({ -1, -1 });
	Display::start();
}

void CLL::init(sf::RenderWindow& window)
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

void CLL::randomInit()
{
	finished = 1;
	srand(time(NULL));
	n = rand() % (8) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}

void CLL::customInit(sf::RenderWindow& window, Button& cancel)
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

void CLL::displayUpdate(int idx, int num)
{
	Display::clear();
	Display::addSource({ "if (!(first)) return;",
						 "Node* cur = first; ",
						 "for (int i = 0; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "cur->data = num;" });

	Layer layer;
	std::vector<int> order;
	layer.addCList(values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	order.push_back(1);
	layer.lists[0].hightlight(Style::lightPink);
	layer.lists[0].setState("first/cur");
	Display::addLayer(layer);

	order.push_back(2);
	Display::addLayer(layer);

	for (int i = 0; i < idx; ++i) {
		layer.lists[i].hightlight(sf::Color::White);
		if (i > 0) layer.lists[i].setState("");
		else layer.lists[i].setState("first");
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
	if (idx == 0) layer.lists[idx].setState("first");
	else layer.lists[idx].setState("");
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void CLL::update(sf::RenderWindow& window)
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

void CLL::displayAdd(int idx, int num)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addCList(values);
	order.push_back(-1);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({"if (!(first)) {",
							"   first = new Node {nume, first};",
							"   return;",
							"}",
							"Node *tmp = new Node {num, first};",
							"Node cur = first;",
							"while (cur->next != first) {",
							"   cur = cur->next;",
							"}",
							"cur->next = tmp;",
							"first = tmp;" });

		order.push_back(0);
		Display::addLayer(layer);

		if (n == 0) {
			layer.lists.push_back(LinkedListNode(pos, num));
			order.push_back(1);
			layer.lists[n].setState("first");
			Display::addLayer(layer);

			order.push_back(2);
			Display::addLayer(layer);

			values.push_back(num);
			++n;
		}
		else { 
			sf::Vector2f pos0 = pos;
			if (n == 1) {
				pos0.y -= 200;
			}
			if (n == 2) {
				pos0.x -= 200;
			}

			layer.lists.insert(layer.lists.begin(), LinkedListNode(pos0, num));
			layer.arrows.insert(layer.arrows.begin(), Arrow());
			layer.arrows[0].create(layer.lists[0], layer.lists[1]);

			layer.lists[0].hightlight(Style::cyan);
			layer.lists[0].setState("tmp");
			order.push_back(4);
			Display::addLayer(layer);

			values.insert(values.begin(), num);
			++n;

			layer.lists[1].hightlight(Style::lightPink);
			layer.lists[1].setState("first/cur");
			order.push_back(5);
			Display::addLayer(layer);

			order.push_back(6);
			Display::addLayer(layer);

			for (int i = 2; i < n; ++i) {
				layer.lists[i - 1].hightlight(sf::Color::White);
				if (i > 2) layer.lists[i - 1].setState("");
				else layer.lists[i - 1].setState("first");
				layer.lists[i].hightlight(Style::lightPink);
				layer.lists[i].setState("cur");
				order.push_back(7);
				Display::addLayer(layer);

				order.push_back(6);
				Display::addLayer(layer);
			}
			
			layer.arrows.back().create(layer.lists[n - 1], layer.lists[0]);
			order.push_back(9);
			Display::addLayer(layer);

			layer.lists[0].setState("first/tmp");
			layer.lists[1].setState("");
			order.push_back(10);
			Display::addLayer(layer);

			layer.addCList(values);
			layer.lists[0].setState("first/tmp");
		}
	}
	else {
		Display::addSource({ "Node* cur = first;",
							 "for (int i = 1; i < idx; ++i) {",
							 "   cur = cur->next;",
							 "}",
							 "Node* tmp = new Node{num, cur->next};",
							 "cur->next = tmp;"});

		order.push_back(0);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("first/cur");
		Display::addLayer(layer);

		order.push_back(1);
		Display::addLayer(layer);

		for (int i = 1; i < idx; ++i) {
			layer.lists[i - 1].hightlight(sf::Color::White);
			if (i > 1) layer.lists[i - 1].setState("");
			else layer.lists[i - 1].setState("first");
			layer.lists[i].hightlight(Style::lightPink);
			layer.lists[i].setState("cur");
			order.push_back(2);
			Display::addLayer(layer);

			order.push_back(1);
			Display::addLayer(layer);
		}

		values.insert(values.begin() + idx, num);
		++n;

		sf::Vector2f posi = pos;
		if (n == 2) {
			posi.y += 200;
		}
		if (n == 3) {
			if (idx == 1) posi.x += 200;
			if (idx == 2) posi.x -= 200;
		}
		layer.lists.insert(layer.lists.begin() + idx, LinkedListNode(posi, num));
		layer.arrows.insert(layer.arrows.begin() + idx, Arrow());
		if (idx == n - 1)
			layer.arrows[idx].create(layer.lists[idx], layer.lists[0]);
		else layer.arrows[idx].create(layer.lists[idx], layer.lists[idx + 1]);
		layer.lists[idx].hightlight(Style::cyan);
		order.push_back(4);
		Display::addLayer(layer);

		layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx]);
		order.push_back(5);
		Display::addLayer(layer);

		layer.addCList(values);
	}
	
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void CLL::add(sf::RenderWindow& window)
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
		window.clear(sf::Color::White);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void CLL::displayRemove(int idx)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addCList(values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({"if (!(first)) return;",
							"if (first->next == first) {",
							"   delete first;",
							"   return;",
							"}",
							"Node* cur = first->next;",
						   	"while (cur->next != first)",
							"   cur = cur->next;",
							"Node* tmp = first;",
							"first = first->next;",
							"cur->next = first;",
							"delete tmp;" });

		order.push_back(1);
		Display::addLayer(layer);
		if (n == 1) {
			values.pop_back();
			n--;
			layer.lists.clear();
			layer.arrows.clear();
			order.push_back(2);
			Display::addLayer(layer);

			order.push_back(3);
			Display::addLayer(layer);
		}
		else {
			layer.lists[1].setState("cur");
			layer.lists[1].hightlight(Style::lightPink);
			order.push_back(5);
			Display::addLayer(layer);

			order.push_back(6);
			Display::addLayer(layer);

			for (int i = 2; i < n; ++i) {
				layer.lists[i - 1].hightlight(sf::Color::White);
				layer.lists[i - 1].setState("");
				layer.lists[i].hightlight(Style::lightPink);
				layer.lists[i].setState("cur");
				order.push_back(7);
				Display::addLayer(layer);

				order.push_back(6);
				Display::addLayer(layer);
			}

			layer.lists[0].setState("first/tmp");
			layer.lists[0].hightlight(Style::cyan);
			order.push_back(8);
			Display::addLayer(layer);

			layer.lists[0].setState("tmp");
			layer.lists[1].setState("first");
			order.push_back(9);
			Display::addLayer(layer);

			layer.arrows.back().create(layer.lists.back(), layer.lists[1]);
			order.push_back(10);
			Display::addLayer(layer);

			layer.lists.erase(layer.lists.begin());
			layer.arrows.erase(layer.arrows.begin());
			order.push_back(11);
			Display::addLayer(layer);
			
			values.erase(values.begin());
			n--;
			layer.addCList(values);
		}
	}
	else {
		Display::addSource({ "if (!(first)) return;",
						 "Node* cur = first;",
						 "for (int i = 1; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "Node* tmp = cur->next;",
						 "cur->next = tmp->next;",
						 "delete tmp;" });

		order.push_back(1);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("first/cur");
		Display::addLayer(layer);

		order.push_back(2);
		Display::addLayer(layer);

		for (int i = 1; i < idx; ++i) {
			layer.lists[i - 1].hightlight(sf::Color::White);
			if (i > 1) layer.lists[i - 1].setState("");
			else layer.lists[i - 1].setState("first");
			layer.lists[i].hightlight(Style::lightPink);
			layer.lists[i].setState("cur");
			order.push_back(3);
			Display::addLayer(layer);

			order.push_back(2);
			Display::addLayer(layer);
		}

		layer.lists[idx].hightlight(Style::cyan);
		layer.lists[idx].setState("tmp");
		order.push_back(5);
		Display::addLayer(layer);
		if (idx < n - 1)
			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx + 1]);
		else 
			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[0]);
		order.push_back(6);
		Display::addLayer(layer);

		layer.lists.erase(layer.lists.begin() + idx);
		layer.arrows.erase(layer.arrows.begin() + idx);
		order.push_back(7);
		Display::addLayer(layer);

		values.erase(values.begin() + idx);
		n--;

		layer.addCList(values);
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void CLL::remove(sf::RenderWindow& window)
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
		window.clear(sf::Color::White);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void CLL::displaySearch(int num)
{
	Display::clear();
	Display::addSource({ "if (!(first)) return;",
						 "Node* cur = first; int idx = 0;",
						 "while (cur->data != num) {",
						 "   cur = cur->next; ++idx;",
						 "   if (cur == first) return -1;",
						 "}",
						 "return idx;" });

	Layer layer;
	std::vector<int> order;
	layer.addCList(values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (n != 0) {
		order.push_back(1);
		layer.lists[0].hightlight(Style::lightPink);
		layer.lists[0].setState("first/cur");
		Display::addLayer(layer);

		order.push_back(2);
		Display::addLayer(layer);

		int i = 0;
		while (values[i] != num) {
			if (i > 0) layer.lists[i].setState("");
			else layer.lists[i].setState("first");
			layer.lists[i].hightlight(sf::Color::White);
			++i;
			if (i < n) {
				layer.lists[i].hightlight(Style::lightPink);
				layer.lists[i].setState("cur");
			}
			else {
				layer.lists[0].hightlight(Style::lightPink);
				layer.lists[0].setState("first/cur");
			}
			order.push_back(3);
			Display::addLayer(layer);

			order.push_back(4);
			Display::addLayer(layer);
			if (i == n) {
				layer.lists[0].hightlight(sf::Color::White);
				layer.lists[0].setState("first");
				break;
			}
			order.push_back(2);
			Display::addLayer(layer);
		}

		if (i < n) {
			layer.lists[i].hightlight(Style::cyan);
			order.push_back(6);
			Display::addLayer(layer);

			layer.lists[i].hightlight(sf::Color::White);
			if (i > 0) layer.lists[i].setState("");
			else layer.lists[i].setState("first");
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void CLL::search(sf::RenderWindow& window)
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
		window.clear(sf::Color::White);
		Display::update();
		cancel.draw(window);
		draw(window);
		window.display();
	}
}
