#include "Arrow.h"

Arrow::Arrow() {
    
}
void Arrow::create(sf::Vector2f pos1, sf::Vector2f pos2, int k) {
    s[1].setTexture(Style::t[1]);

    s[2].setTexture(Style::t[2]);

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
    s[id].setScale((length) / s[k].getLocalBounds().width, 1.5);
    
    inited = 1;
}

void Arrow::draw(sf::RenderWindow& window) {
    if (!inited) {
        return;
    }
    window.draw(s[id]);
}
