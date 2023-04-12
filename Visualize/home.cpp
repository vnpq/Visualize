#include "home.h"


void home(sf::RenderWindow& window)
{
	//create the name of the app
	sf::Text dataS;
	dataS.setString("Data Structure");
	dataS.setFillColor(sf::Color::Black);
	dataS.setFont(Style::font);
	dataS.setCharacterSize(125);
	dataS.setPosition(sf::Vector2f(820.f, 280.f));

	sf::Text visual;
	visual.setString("Visualization");
	visual.setFillColor(Style::darkBlue);
	visual.setFont(Style::font2);
	visual.setCharacterSize(250);
	visual.setPosition(sf::Vector2f(650.f, 320.f));

	sf::Text au;
	au.setString("MSSV: 22127360");
	au.setFillColor(sf::Color::Black);
	au.setFont(Style::font);
	au.setStyle(sf::Text::Italic);
	au.setCharacterSize(30);
	au.setPosition(sf::Vector2f(1390.f, 600.f));
	
	
	//create the sidebar
	sf::RectangleShape sidebar;
	sidebar.setFillColor(Style::darkBlue);
	sidebar.setSize(sf::Vector2f(380.f, 1080.f));
	sidebar.setPosition(sf::Vector2f(0.f, 0.f));

	//create button for each data structure and custom
	Button staticA;
	staticA.init(sf::Vector2f(100.f, 100.f), "Static Array");
	Button dynaA;
	dynaA.init(sf::Vector2f(100.f, 200.f), "Dynamic Array");
	Button LL;
	LL.init(sf::Vector2f(100.f, 300.f), "Linked List");
	Button DLL;
	DLL.init(sf::Vector2f(100.f, 400.f), "Doubly LL");
	Button CLL;
	CLL.init(sf::Vector2f(100.f, 500.f), "Circular LL");
	Button stack;
	stack.init(sf::Vector2f(100.f, 600.f), "Stack");
	Button queue;
	queue.init(sf::Vector2f(100.f, 700.f), "Queue");
	Button custom;
	custom.init(sf::Vector2f(100.f, 800.f), "Custom");

	Button exit;
	exit.init(sf::Vector2f(1670.f, 800.f), "EXIT");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || exit.handleEvent(window, event)) 
				window.close();

			if (staticA.handleEvent(window, event)) {
				StaticArray(window);
				staticA.state = 0;
			}
			if (dynaA.handleEvent(window, event)) {
				DynamicArray(window);
				dynaA.state = 0;
			}
			if (LL.handleEvent(window, event)) {
				LinkedL(window);
				LL.state = 0;
			}
			if (DLL.handleEvent(window, event)) {
				DoublyLL(window);
				DLL.state = 0;
			}
			if (CLL.handleEvent(window, event)) {
				CircularLL(window);
				CLL.state = 0;
			}
			if (stack.handleEvent(window, event)) {
				Stack(window);
				stack.state = 0;
			}
			if (queue.handleEvent(window, event)) {
				Queue(window);
				queue.state = 0;
			}
			if (custom.handleEvent(window, event)) {
				Custom(window);
				custom.state = 0;
			}
				
		}
		window.clear(sf::Color::White);
		window.draw(sidebar);
		window.draw(dataS);
		window.draw(visual);
		window.draw(au);

		staticA.draw(window);
		dynaA.draw(window);
		LL.draw(window);
		DLL.draw(window);
		CLL.draw(window);
		stack.draw(window);
		queue.draw(window);
		custom.draw(window);
		exit.draw(window);
		window.display();
	}
}



