#include "Textbox.h"

void Textbox::init(sf::Vector2f pos)
{
	//setting 
	text.setFont(Style::font);
	text.setFillColor(Style::darkBlue);
	text.setCharacterSize(23);
	text.setPosition(sf::Vector2f(pos.x + 5.f, pos.y + 5.f));

	
	box.setSize(sf::Vector2f(200.f, 70.f));
	box.setOutlineThickness(1.f);
	box.setOutlineColor(sf::Color::Black);
	box.setFillColor(Style::cyan);
	box.setPosition(pos);

}
void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event, std::string& output)
{
    std::string st = text.getString();
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
        if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            state = Typable;
        }
        else state = UnTypable;
    }
    
    if (state == Typable && event.type == sf::Event::TextEntered)
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
                output = st;
                state = UnTypable;
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
	ask.setFillColor(Style::darkBlue);
	ask.setCharacterSize(23);
	ask.setPosition(pos);

	Textbox box;
	box.init(sf::Vector2f(pos.x, pos.y + 35.f));

	Button OK;
	OK.init(sf::Vector2f(pos.x + 200.f, pos.y + 35.f), "OK");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			box.handleEvent(window, event, st);
			if (OK.handleEvent(window, event)) {
				OK.state = 0;
				return;
			}
			if (home.handleEvent(window, event) || cancel.handleEvent(window, event))
				return;
		}

		window.draw(ask);
		box.draw(window);
		OK.draw(window);

		window.display();
	}

}