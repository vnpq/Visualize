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
		window.clear(Style::backgroundColor);
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
	cancel.init(sf::Vector2f(1450.f, 850.f), "Cancel");
	Button random;
	random.init(sf::Vector2f(480.f, 100.f), "Random");
	Button custom;
	custom.init(sf::Vector2f(480.f, 200.f), "Custom");
	Button empty;
	empty.init(sf::Vector2f(480.f, 300.f), "Empty");
	Button file;
	file.init({ 480, 400 }, "From file");
	fileStatus.setString("");

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
			if (file.handleEvent(window, event)) {
				fileInit();
				if (!finished) {
					fileStatus.setString("Can not open file!");
				}
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
		file.draw(window);
		window.display();
	}
}

void DLL::randomInit()
{
	finished = 1;
	srand(time(NULL));
	n = rand() % (6) + 3;
	values.clear();
	for (int i = 0; i < n; ++i)
		values.push_back(rand() % (101));
}

void DLL::fileInit()
{
	std::string arr = "";
	finished = 0;
	values.clear();
	std::ifstream ifs;
	ifs.open("input.txt");
	if (!(ifs.good())) return;
	while (!(ifs.eof())) {
		std::getline(ifs, arr);
		std::cout << "OK";
		std::cout << arr << "\n";
		std::stringstream ss(arr);
		while (ss.good()) {
			std::string substr;
			std::getline(ss, substr, ',');
			int num = std::stoi(substr);
			values.push_back(num);
		}
	}
	n = values.size();
	finished = 1;
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
		window.clear(Style::backgroundColor);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void DLL::displayUpdate(int idx, int num)
{
	Display::clear();
	Display::addSource({ "if (!(head)) return;",
						 "Node* cur = head; ",
						 "for (int i = 0; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "cur->data = num;" });

	Layer layer;
	std::vector<int> order;
	layer.addDList({ 500, 400 }, values);
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
		if (i == n - 2) layer.lists[i + 1].setState("tail/cur");
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
	layer.lists.back().setState("tail");
	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void DLL::update(sf::RenderWindow& window)
{
	if (n == 0) return;

	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 850.f), "Cancel");
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


void DLL::displayAdd(int idx, int num)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addDList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({ "Node* tmp = new Node {num, head, nullptr};",
							 "if (head) head.pre = tmp",
							 "head = tmp;",
							 "if (!(head.next) tail = head"});
		if (n == 0) {
			layer.lists.push_back(LinkedListNode({ 500,400 }, num));
			order.push_back(0);
			layer.lists[n].setState("tmp");
			Display::addLayer(layer);

			order.push_back(1);
			Display::addLayer(layer);

			layer.lists[0].setState("head/tmp");
			order.push_back(2);
			Display::addLayer(layer);

			layer.lists[0].setState("head/tail/tmp");
			order.push_back(3);
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

			layer.addDList({ 500, 400 }, values);
			layer.lists[0].hightlight(Style::cyan);
			layer.lists[0].setState("tmp");
			layer.lists[1].setState("head");
			order.push_back(1);
			Display::addLayer(layer);

			layer.lists[1].setState("");
			layer.lists.back().setState("tail");
			layer.lists[0].setState("head/tmp");
			order.push_back(2);
			Display::addLayer(layer);

			order.push_back(3);
			Display::addLayer(layer);

			layer.lists[0].hightlight(sf::Color::White);
		}
		layer.lists[0].setState("head");
	}
	else {
		if (idx == n) {
			Display::addSource({ "tail->next = new Node{num, nullptr, tail};",
								 "tail = tail->next;" });
			float x = 500 + n * size;
			layer.lists.push_back(LinkedListNode({ x, 400 }, num));
			layer.lists[n].hightlight(Style::cyan);
			layer.arrows.push_back(Arrow());
			layer.arrow2.push_back(Arrow());
			layer.arrows.back().create(layer.lists[n - 1], layer.lists[n]);
			layer.arrow2.back().create(layer.lists[n], layer.lists[n - 1]);
			order.push_back(0);
			Display::addLayer(layer);

			layer.lists[n - 1].setState("");
			layer.lists[0].setState("head");
			layer.lists.back().setState("tail");
			order.push_back(1);
			Display::addLayer(layer);

			layer.lists[n].hightlight(sf::Color::White);
			values.push_back(num);
			n++;
		}
		else {
			Display::addSource({ "Node* cur = head;",
							 "for (int i = 1; i < idx; ++i)",
							 "   cur = cur->next;",
							 "}",
							 "Node* tmp = new Node{num, cur->next, cur};",
							 "cur->next = tmp;", 
							 "tmp->next->pre = tmp;"});

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

			values.insert(values.begin() + idx, num);
			++n;
			float x = 440 + idx * size;
			layer.lists.insert(layer.lists.begin() + idx, LinkedListNode({ x, 510 }, num));

			layer.arrows.insert(layer.arrows.begin() + idx, Arrow());
			layer.arrows[idx].create(layer.lists[idx], layer.lists[idx + 1]);
			
			layer.arrow2.insert(layer.arrow2.begin() + idx - 1, Arrow());
			layer.arrow2[idx - 1].create(layer.lists[idx], layer.lists[idx - 1]);

			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tmp");
			order.push_back(4);
			Display::addLayer(layer);

			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx]);
			order.push_back(5);
			Display::addLayer(layer);

			layer.arrow2[idx].create(layer.lists[idx + 1], layer.lists[idx]);
			order.push_back(6);
			Display::addLayer(layer);

			layer.addDList({ 500, 400 }, values);
			
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}



void DLL::add(sf::RenderWindow& window)
{
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 850.f), "Cancel");
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


void DLL::displayRemove(int idx)
{
	Display::clear();
	Layer layer;
	std::vector<int> order;
	layer.addDList({ 500, 400 }, values);
	order.push_back(-1);
	Display::addLayer(layer);

	order.push_back(0);
	Display::addLayer(layer);

	if (idx == 0) {
		Display::addSource({ "if (!(head)) return;",
							 "Node* tmp = head;",
							 "head = head->next;",
							 "delete tmp;",
							 "if (head) head->pre = nullptr;"});

		layer.lists[0].hightlight(Style::cyan);
		layer.lists[0].setState("head/tmp");
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

		if (n > 1) layer.arrow2.erase(layer.arrow2.begin());
		order.push_back(4);
		Display::addLayer(layer);

		values.erase(values.begin());
		--n;
	}
	else {
		if (idx == n - 1) {
			Display::addSource({ "if (!(head)) return;",
								 "Node* tmp = tail;",
								 "tail = tail->pre;",
								 "tail->next = nullptr;",
								 "delete tmp;" });
			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tail/tmp");
			order.push_back(1);
			Display::addLayer(layer);

			layer.lists[idx].setState("tmp");
			layer.lists[idx - 1].setState("tail");
			if (idx == 1) layer.lists[0].setState("heal/tail");
			order.push_back(2);
			Display::addLayer(layer);

			layer.arrows.pop_back();
			order.push_back(3);
			Display::addLayer(layer);

			layer.lists.pop_back();
			layer.arrow2.pop_back();
			order.push_back(4);
			Display::addLayer(layer);

			values.pop_back();
			--n; 

			layer.lists.back().hightlight(sf::Color::White);
		}
		else {
			Display::addSource({ "if (!(head)) return;",
						 "Node* cur = head;",
						 "for (int i = 1; i < idx; ++i) {",
						 "   cur = cur->next;",
						 "}",
						 "Node* tmp = cur->next;",
						 "cur->next = tmp->next;",
						 "tmp->next->pre = cur;",
						 "delete tmp;" });

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

			layer.lists[idx].hightlight(Style::cyan);
			layer.lists[idx].setState("tmp");
			order.push_back(5);
			Display::addLayer(layer);

			float x = 500 + idx * size;
			layer.lists[idx].setPosition({ x, 510 });
			layer.arrows[idx].create(layer.lists[idx], layer.lists[idx + 1]);
			layer.arrows[idx - 1].create(layer.lists[idx - 1], layer.lists[idx + 1]);
			layer.arrow2[idx - 1].create(layer.lists[idx], layer.lists[idx - 1]);
			layer.arrow2[idx].create(layer.lists[idx + 1], layer.lists[idx]);
			order.push_back(6);
			Display::addLayer(layer);

			layer.arrow2[idx].create(layer.lists[idx + 1], layer.lists[idx - 1]);
			order.push_back(7);
			Display::addLayer(layer);

			layer.lists.erase(layer.lists.begin() + idx);
			layer.arrows.erase(layer.arrows.begin() + idx);
			layer.arrow2.erase(layer.arrow2.begin() + idx - 1);
			order.push_back(8);
			Display::addLayer(layer);

			values.erase(values.begin() + idx);
			n--;

			layer.addDList({ 500, 400 }, values);
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void DLL::remove(sf::RenderWindow& window)
{
	if (n == 0) return;
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 850.f), "Cancel");
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

void DLL::displaySearch(int num)
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
	layer.addDList({ 500, 400 }, values);
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
			if (i == n - 1) layer.lists[i].setState("tail");
			layer.lists[i].hightlight(sf::Color::White);
			++i;
			if (i < n) {
				layer.lists[i].hightlight(Style::lightPink);
				layer.lists[i].setState("cur");
				if (i == n-1) layer.lists[i].setState("tail/cur");
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
			layer.lists.back().setState("tail");
		}
	}

	order.push_back(-1);
	Display::addLayer(layer);

	Display::addOrder(order);
	Display::start();
}

void DLL::search(sf::RenderWindow& window)
{
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 850.f), "Cancel");
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
