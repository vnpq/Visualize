#include "Textbox.h"
#include <iostream>

void Textbox::init(sf::Vector2f pos)
{
	//setting 
	text.setFont(Style::font);
	text.setFillColor(Style::darkBlue);
	text.setCharacterSize(23);
	text.setPosition(sf::Vector2f(pos.x + 5.f, pos.y + 5.f));

	
	box.setSize(sf::Vector2f(200.f, 68.f));
	box.setOutlineThickness(1.f);
	box.setOutlineColor(sf::Color::Black);
	box.setFillColor(Style::cyan);
	box.setPosition(pos);

}
void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event, std::string& st, Button& OK)
{
    //std::string st = text.getString();
	text.setString(st);
    if (event.type == sf::Event::TextEntered)
    {
        char c = event.text.unicode;
        if (c < 128) // only handle ASCII characters
            switch (c) {
            case '\b':    // handle backspace
                if (!text.getString().isEmpty()) {
                    st = text.getString().substring(0, text.getString().getSize() - 1);
                    text.setString(st);
                }
                break;
            case '\r': //handle enter
                //output = st;
				OK.state = 2;
                break;
            default:
                st = text.getString() + c;
                text.setString(st);
                break;
            }
    }
}

void Textbox::draw(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}


void input(sf::RenderWindow& window, std::string& st, std::string text, sf::Vector2f pos,
	Button& home, Button& cancel) {
	sf::Text ask;
	ask.setString(text);
	ask.setFont(Style::font);
	ask.setFillColor(sf::Color::White);
	ask.setCharacterSize(23);
	ask.setPosition(pos);

	Textbox box;
	box.init(sf::Vector2f(pos.x + 70.f, pos.y - 20.f));

	Button OK;
	OK.init(sf::Vector2f(pos.x + 271.f, pos.y - 21.f), "OK");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			box.handleEvent(window, event, st, OK);
			if (OK.state == 2 || OK.handleEvent(window, event)) {
				OK.state = 0;
				return;
			}
			if (event.type == sf::Event::TextEntered && event.text.unicode == 'r')
				return;
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
		}
		window.draw(ask);
		box.draw(window);
		OK.draw(window);

		window.display();
	}

}