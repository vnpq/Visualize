#include "Source.h"

void Source::highlight(int row)
{
	if (code.empty()) return;
	code[highlighted].setStyle(sf::Text::Regular);
	if (row < 0 || row >= code.size()) return;
	code[row].setStyle(sf::Text::Bold);
	highlighted = row;
}

void Source::add(std::vector<std::string> st)
{
	sf::Text text;
	rect.setSize({ 500.f, 330.f });
	rect.setPosition({ 1430.f, 0.f });
	rect.setFillColor(Style::cyan);
	for (int i = 0; i < st.size(); ++i) {
		code.push_back(text);
		code.back().setFont(Style::cFont);
		code.back().setString(st[i]);
		code.back().setCharacterSize(20);
		code.back().setPosition(sf::Vector2f(1470.f, 40.f + 20.f * i));
		code.back().setFillColor(sf::Color::Black);
	}
}

void Source::draw(sf::RenderWindow& window)
{
	if (code.size() != 0) window.draw(rect);
	for (sf::Text & x: code) {
		window.draw(x);
	}
}

void Source::clear()
{
	code.clear();
	highlighted = 0;
}
