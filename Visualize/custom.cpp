#include "home.h"

void Custom(sf::RenderWindow& window)
{
	sf::Text dataS;
	dataS.setString("Data Structure");
	dataS.setFillColor(Style::normalText);
	dataS.setFont(Style::font);
	dataS.setCharacterSize(125);
	dataS.setPosition(sf::Vector2f(820.f, 280.f));

	sf::Text visual;
	visual.setString("Visualization");
	visual.setFillColor(Style::darkBlue);
	if (Style::dark)
		visual.setFillColor(Style::cyan);
	visual.setFont(Style::font2);
	visual.setCharacterSize(250);
	visual.setPosition(sf::Vector2f(650.f, 320.f));

	sf::Text au;
	au.setString("MSSV: 22127360");
	au.setFillColor(Style::normalText);
	au.setFont(Style::font);
	au.setStyle(sf::Text::Italic);
	au.setCharacterSize(30);
	au.setPosition(sf::Vector2f(1390.f, 600.f));


	//create the sidebar
	sf::RectangleShape sidebar;
	sidebar.setFillColor(Style::sideBar);
	sidebar.setSize(sf::Vector2f(380.f, 1080.f));
	sidebar.setPosition(sf::Vector2f(0.f, 0.f));
	
	//create a button to back to home page
	Button home;
	home.init(sf::Vector2f(1670.f, 800.f), "HOME");

	Button light;
	light.init({ 100, 100 }, "Light Mode");

	Button dark;
	dark.init({ 100, 200 }, "Dark Mode");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (light.handleEvent(window, event)) {
				Style::backgroundColor = sf::Color::White;
				Style::normalText = sf::Color::Black;
				Style::stateText = sf::Color::Red;
				Style::dark = 0;
			}
			if (dark.handleEvent(window, event)) {
				Style::backgroundColor = sf::Color(30, 38, 66);
				//Style::backgroundColor = sf::Color(40, 40, 40);
				Style::normalText = sf::Color::White;
				Style::stateText = sf::Color::Yellow;
				Style::dark = 1;
			}
			au.setFillColor(Style::normalText);
			dataS.setFillColor(Style::normalText);
			visual.setFillColor(Style::darkBlue);
			if (Style::dark)
				visual.setFillColor(Style::cyan);
			if (home.handleEvent(window, event)) return;
		}
		window.clear(Style::backgroundColor);
		window.draw(sidebar);
		window.draw(dataS);
		window.draw(visual);
		window.draw(au);

		light.draw(window);
		dark.draw(window);
		home.draw(window);
		window.display();
	}
}