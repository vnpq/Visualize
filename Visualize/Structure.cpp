#include "ArrayNode.h"
#include "LinkedListNode.h"


//ARRAY NODE
ArrayNode::ArrayNode(sf::Vector2f pos, int x)
{
	create(pos, x);
}
void ArrayNode::create(sf::Vector2f pos, int x)
{
	// Create rectangle shape for the node
	rect.setSize(sf::Vector2f(60.f, 60.f));
	rect.setFillColor(sf::Color::White);
	rect.setOutlineThickness(2.f);
	rect.setOutlineColor(sf::Color::Black);
	rect.setPosition(pos);

	// Create text object to display the value of the node
	text.setFont(Style::font);
	text.setString(std::to_string(x));
	text.setCharacterSize(23);
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2.0f),
		text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(pos.x + 30.f, pos.y + 30.f);
}
void ArrayNode::setPosition(sf::Vector2f pos) {
	rect.setPosition(pos);
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2.0f),
		text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(pos.x + 30.f, pos.y + 30.f);
}
void ArrayNode::setValue(int x)
{
	text.setString(std::to_string(x));
	sf::Vector2f pos = getPosition();
	text.setOrigin(text.getLocalBounds().left + (text.getLocalBounds().width / 2.0f),
		text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setPosition(pos.x + 30.f, pos.y + 30.f);
}
void ArrayNode::draw(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}
void ArrayNode::hightlight(sf::Color color)
{
	rect.setFillColor(color);
}

sf::Vector2f ArrayNode::getPosition()
{
	return rect.getPosition();
}


//LINKED LIST NODE
LinkedListNode::LinkedListNode(sf::Vector2f pos, int x) {
	create(pos, x);
}
void LinkedListNode::create(sf::Vector2f pos, int x) {
	circle.setRadius(25.f);
	circle.setFillColor(sf::Color::White);
	circle.setOutlineThickness(2.5f);
	circle.setOutlineColor(sf::Color::Black);
	circle.setPosition(pos);
	text.setFont(Style::font);
	text.setCharacterSize(24);
	text.setString(std::to_string(x));
	text.setFillColor(sf::Color::Black);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos.x + circle.getRadius(), pos.y + circle.getRadius() - 6.f);
}
void LinkedListNode::setPosition(sf::Vector2f pos)
{
	circle.setPosition(pos);
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos.x + circle.getRadius(), pos.y + circle.getRadius() - 6.f);
	state.setOrigin(state.getGlobalBounds().width / 2, state.getGlobalBounds().height / 2);
	state.setPosition(pos.x + circle.getRadius(), pos.y - circle.getRadius());
}
void LinkedListNode::setValue(int x)
{
	text.setString(std::to_string(x));
	sf::Vector2f pos = getPosition();
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(pos.x + circle.getRadius(), pos.y + circle.getRadius() - 6.f);
}
void LinkedListNode::setState(std::string st)
{
	state.setFont(Style::font);
	state.setCharacterSize(23);
	state.setString(st);
	state.setFillColor(sf::Color::Red);
	sf::Vector2f pos = getPosition();
	state.setOrigin(state.getGlobalBounds().width / 2, state.getGlobalBounds().height / 2);
	state.setPosition(pos.x + circle.getRadius(), pos.y - circle.getRadius());
}



void LinkedListNode::hightlight(sf::Color color) {
	circle.setFillColor(color);
}
void LinkedListNode::draw(sf::RenderWindow& window) {
	window.draw(circle);
	window.draw(text);
	window.draw(state);
}

sf::Vector2f LinkedListNode::getPosition() {
	return circle.getPosition();
}

sf::Vector2f LinkedListNode::getSize() {
	return sf::Vector2f(50.f, 50.f);
}