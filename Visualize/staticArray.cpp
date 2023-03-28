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
			
			if (a.addB.handleEvent(window, event))
				a.add(window);

			if (a.updateB.handleEvent(window, event)) 
				a.update(window);

			if (a.removeB.handleEvent(window, event)) 
				a.remove(window);

			if (a.searchB.handleEvent(window, event)) 
				a.search(window);

			if (a.home.handleEvent(window, event)) {
				//a.working = 0;
				return;
			}
		}	
		window.clear(sf::Color::White);
		a.draw(window);
		window.display();
	}
}


void SArray::init(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");
	
	std::string quantity="";
	int n;
	std::string values="";


	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (quantity == "") {
				input(window, quantity, "Input number of the array", sf::Vector2f(500.f, 200.f), home, cancel);
				n = std::stoi(quantity);
			}
			if (quantity!="" && values == "") {
				input(window, values, "Input the elements", sf::Vector2f(500.f, 200.f), home, cancel);

			}
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event)) 
					return;			
		}
		window.clear(sf::Color::White);

		draw(window);
		cancel.draw(window);

		window.display();
	}
}



void SArray::add(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
		}
		window.clear(sf::Color::White);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void SArray::update(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		//Create a cancel button
		Button cancel;
		cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;

		}
		window.clear(sf::Color::White);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void SArray::remove(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;

		}
		window.clear(sf::Color::White);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}

void SArray::search(sf::RenderWindow& window)
{
	//Create a cancel button
	Button cancel;
	cancel.init(sf::Vector2f(1450.f, 800.f), "Cancel");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;

		}
		window.clear(sf::Color::White);
		cancel.draw(window);
		draw(window);
		window.display();
	}
}