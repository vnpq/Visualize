#include "Arrow.h"

Arrow::Arrow() {
    // Initialize the texture and sprite arrays
    if (!t[1].loadFromFile("arrow1.png"));
    s[1].setTexture(t[1]);
    if (!t[2].loadFromFile("arrow2.png"));
    s[2].setTexture(t[2]);
}
void Arrow::create(sf::Vector2f pos1, sf::Vector2f pos2, int k) {

    id = k;
    // Calculate the length and angle of the arrow
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx) * 180 / M_PI;

    // Set the position, origin, rotation, and scale of the arrow sprite
    s[id].setPosition(pos1);
    s[id].setOrigin(0, s[id].getLocalBounds().height / 2.0);
    s[id].setRotation(angle);
    s[id].setScale((length-30) / s[k].getLocalBounds().width, 1);
    
    inited = 1;
}

void Arrow::draw(sf::RenderWindow& window) {
    if (!inited) {
        return;
    }
    window.draw(s[id]);
}
