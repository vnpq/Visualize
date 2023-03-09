#include "Textbox.h"

void Textbox::init(sf::Vector2f pos)
{
	//setting 
	font.loadFromFile("Lexend-Regular.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Blue);
	text.setCharacterSize(25);
	text.setPosition(sf::Vector2f(pos.x + 5.f, pos.y + 5.f));

	
	box.setSize(sf::Vector2f(200.f, 70.f));
	box.setOutlineThickness(1.f);
	box.setOutlineColor(sf::Color::Black);
	box.setFillColor(sf::Color::Transparent);
	box.setPosition(pos);

}
void Textbox::handleEvent(sf::RenderWindow& window, sf::Event event)
{
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
        if (event.text.unicode < 128) // only handle ASCII characters
        {
            // handle backspace
            if (event.text.unicode == '\b' && !text.getString().isEmpty())
            {
                text.setString(text.getString().substring(0, text.getString().getSize() - 1));
            }
            // handle newlines
            else if (event.text.unicode == '\n')
            {
                // do nothing
            }
            // handle normal characters
            else
            {
                text.setString(text.getString() + static_cast<char>(event.text.unicode));
            }
        }
    }
}

void Textbox::draw(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(text);
}
